#include "StdAfx.h"
#include "selectemulatordlg.h"

#include "utils.h"
#include "framelessdlg.h"

#include "VirtualMachine.h"
#include <ShlObj.h>
#include "nofocusstyle.h"
#include "processproxy.h"

#include "RemoteInjecter.h"

#pragma comment(lib, "shell32.lib")

int SelectEmulatorDlg::Invoke()
{
	FramelessDlg container(0, 0);
	SelectEmulatorDlg* dlg = new SelectEmulatorDlg(&container);

	connect(dlg, SIGNAL(OK()), &container, SLOT(accept()));

	container.SetDlg(dlg);
	container.SetTitle(Utils::stoq("请双击选择要启动的模拟器"));
	container.setFixedSize(400, 300);
	container.CenterWindow();

	return container.exec();	
}

SelectEmulatorDlg::SelectEmulatorDlg(QWidget *parent)
	: QFrame(parent)
{
	ui.setupUi(this);
	Utils::InitStyle(this);
	NoFocusStyle* style = new NoFocusStyle(this);
	ui.lstEmulators->setStyle(style);

	InitVirtualMachine();

	connect(ui.lstEmulators, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(OnLstEmulatorsItemDoubleClicked(QListWidgetItem*)));
}

SelectEmulatorDlg::~SelectEmulatorDlg()
{

}

void SelectEmulatorDlg::OnLstEmulatorsItemDoubleClicked( QListWidgetItem* item )
{
	const wchar_t* genymotionPath = NULL;
	const wchar_t* x86Path = L"C:\\Program Files\\Genymobile\\Genymotion";
	const wchar_t* x64Path = L"C:\\Program Files (x86)\\Genymobile\\Genymotion";

	if ( Utils::FileExist(x86Path) )
		genymotionPath = x86Path;

	if ( Utils::FileExist(x64Path) )
		genymotionPath = x64Path;

	if ( NULL == genymotionPath )
		return;

	WCHAR cmd[1024] = {0};
	wsprintfW(cmd, L"%s\\player.exe --vm-name \"%s\"", genymotionPath, Utils::qtow(item->text()).c_str());
	
	PROCESS_INFORMATION procInfo = ProcessProxy::CreateProcess(cmd);

	/*RemoteThreadInjecter inject;
	inject.InjectDll(procInfo.hProcess, (Utils::GetExePath() + L"\\GenymotionHook.dll").c_str());

	ResumeThread(procInfo.hThread);*/

	emit OK();
}

void SelectEmulatorDlg::InitVirtualMachine()
{
	WCHAR configFile[1024] = {0};
	SHGetFolderPathW(NULL, CSIDL_PROFILE, NULL, NULL, configFile);
	wcscat(configFile, L"\\.VirtualBox\\VirtualBox.xml");

	if ( !Utils::FileExist(configFile) )
		return;

	VirtualMachine::Node* nodes = VirtualMachine::GetMachineList(configFile);

	ui.lstEmulators->clear();
	VirtualMachine::Node* it = nodes;

	while ( it )
	{
		ui.lstEmulators->addItem(Utils::wtoq(it->machineName+wcslen(L"Genymotion - ")));
		it = it->next;
	}

	VirtualMachine::DeleteList(nodes);
}
