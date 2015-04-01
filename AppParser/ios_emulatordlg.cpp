#include "StdAfx.h"
#include "ios_emulatordlg.h"

#include "utils.h"
#include "datamanager.h"
#include "imobileinfo.h"

#include "backuppassworddlg.h"

#include "msgbox.h"

#include <Dbt.h>
#include <SetupAPI.h>

#pragma comment(lib, "Setupapi.lib")
#pragma comment(lib, "imobileinfo.lib")

void WINAPI NotifyBackupProcess(double dRate)
{
	Emulator::GetInstance()->DoNotify((int)dRate);
}

Emulator* Emulator::m_instance = NULL;

void Emulator::SetInstance(Emulator* instance)
{
	m_instance = instance;
}

Emulator* Emulator::GetInstance()
{
	return m_instance;
}

Emulator::Emulator(TaskList& taskList, char** deviceList)
	: m_taskList(taskList)
	, m_deviceList(deviceList)
{

}

Emulator::~Emulator()
{

}

void Emulator::ProcessExportTask()
{
	for ( TaskList::iterator it = m_taskList.begin(); 
		  it != m_taskList.end(); 
		  ++it )
	{
		DataManager& dm = DataManager::GetInstance();
		std::wstring rootPath = dm.GetCurrentDevicePath() + L"\\Backup";

		emit ProcessTaskStatus(Utils::wtoq(it->appName) + Utils::stoq(" : 正在导入数据 ... ") );

		if ( !ImportAppData(it->deviceId, it->appId, it->appDataPath) )
			emit ProcessTaskFailed();
	}

	emit ProcessTaskDone();
}

void Emulator::ProcessInstallTask()
{
	for ( TaskList::iterator it = m_taskList.begin(); 
		it != m_taskList.end(); 
		++it )
	{
		DataManager& dm = DataManager::GetInstance();
		std::wstring rootPath = dm.GetCurrentDevicePath() + L"\\Backup";

		emit ProcessTaskStatus(Utils::wtoq(it->appName) + Utils::stoq(" : 正在安装应用 ... ") );

		if ( !InstallApp(it->deviceId, it->appFilePath) )
			emit ProcessTaskFailed();
	}

	emit ProcessTaskDone();
}

void Emulator::RefreshDeviceList()
{
	for ( int i = 0; i < 24; ++i )
		memset(m_deviceList[i], 0, 1024);

	ListIosDevice(m_deviceList, 24);

	emit DeviceListDone();
}

void Emulator::RecoveryBackup()
{
	TaskList::iterator it = m_taskList.begin();
	char* password = NULL;

	if ( 0 != strlen(it->password) )
		password = it->password;

	if ( RestoreFromBackup(it->srcId, it->deviceId, it->rootPath, password, NotifyBackupProcess) )
		emit RecoveryBackupDone();
	else
		emit RecoveryBackupFailed();
}

IOS_EmulatorDlg::IOS_EmulatorDlg(QWidget *parent)
	: QFrame(parent)
	, m_hUsbNotify(NULL)
	, m_connected(false)
{
	ui.setupUi(this);
	Utils::InitStyle(this);

	m_deviceList = new char*[24];

	for ( int i = 0; i < 24; ++i )
	{
		m_deviceList[i] = new char[1024];
		memset(m_deviceList[i], 0, 1024);
	}

	ui.btnExportAll->hide();
	ui.btnInstallAll->hide();
	ui.btnRecoveryBackup->setEnabled(false);

	m_emulator = new Emulator(m_tasks, m_deviceList);
	Emulator::SetInstance(m_emulator);
	m_emulatorThd = new QThread;

	InitConnection();
	InitTreeView();

	SetExportEnable(false);
}

IOS_EmulatorDlg::~IOS_EmulatorDlg()
{
	for ( int i = 0; i < 24; ++i )
		delete [] m_deviceList[i];

	delete [] m_deviceList;

	if ( m_emulatorThd->isRunning() )
	{
		m_emulatorThd->terminate();
		m_emulatorThd->wait();
	}

	delete m_emulatorThd;
	delete m_emulator;
}

void IOS_EmulatorDlg::RegisterUsbNotify()
{
	DEV_BROADCAST_DEVICEINTERFACE	NotificationFilter	= {0};
	GUID							guidUsb = GUID_USB;

	NotificationFilter.dbcc_size	   = sizeof(DEV_BROADCAST_DEVICEINTERFACE);  
	NotificationFilter.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;  
	NotificationFilter.dbcc_classguid  = guidUsb;  

	m_hUsbNotify = RegisterDeviceNotification(this->winId(), &NotificationFilter, DEVICE_NOTIFY_WINDOW_HANDLE); 
}

void IOS_EmulatorDlg::InitConnection()
{
	connect(ui.btnExportAll, SIGNAL(clicked()), this, SLOT(OnBtnExportAllClicked()));
	connect(ui.btnInstallAll, SIGNAL(clicked()), this, SLOT(OnBtnInstallAllClicked()));

	connect(m_emulator, SIGNAL(ProcessTaskStatus(QString)), this, SLOT(ProcessTaskStatus(QString)));
	connect(m_emulator, SIGNAL(ProcessTaskDone()), this, SLOT(ProcessTaskDone()));
	connect(m_emulator, SIGNAL(ProcessTaskFailed()), this, SLOT(ProcessTaskFailed()));
	connect(this, SIGNAL(ProcessInstallTask()), m_emulator, SLOT(ProcessInstallTask()));
	connect(this, SIGNAL(ProcessExportTask()), m_emulator, SLOT(ProcessExportTask()));

	connect(m_emulator, SIGNAL(DeviceListDone()), this, SLOT(RefreshDeviceListDone()));
	connect(this, SIGNAL(RefreshDeviceList()), m_emulator, SLOT(RefreshDeviceList()));

	connect(ui.btnRecoveryBackup, SIGNAL(clicked()), this, SLOT(OnBtnRecoveryBackupClicked()));

	connect(this, SIGNAL(RecoveryBackup()), m_emulator, SLOT(RecoveryBackup()));
	connect(m_emulator, SIGNAL(RecoveryBackupDone()), this, SLOT(RecoveryBackupDone()));
	connect(m_emulator, SIGNAL(RecoveryBackupFailed()), this, SLOT(RecoveryBackupFailed()));
	connect(m_emulator, SIGNAL(RecoveryBackupProcess(int)), this, SLOT(RecoveryBackupProcess(int)));

	m_emulator->moveToThread(m_emulatorThd);
	m_emulatorThd->start();
}

void IOS_EmulatorDlg::InitTreeView()
{
	ui.trEmulatorApps->clear();
	ui.trEmulatorApps->header()->resizeSection(0, 175);
	ui.trEmulatorApps->header()->resizeSection(1, 175);
	ui.trEmulatorApps->header()->resizeSection(2, 175);
	ui.trEmulatorApps->header()->resizeSection(3, 170);
}

void IOS_EmulatorDlg::AddAppItem(QString name, QString domain, QString icon, QString version)
{
	QTreeWidgetItem* item = new QTreeWidgetItem;

	item->setIcon(0, QIcon(QPixmap(icon)));
	item->setText(0, name);
	item->setText(1, domain);
	item->setText(2, version);

	SQLiteHelper sqlite;
	sqlite.ConnectToDatabase(Utils::GetExePath() + L"\\ios_appinfo.db");

	WCHAR cmd[1024] = {0};
	wsprintfW(cmd, L"select app_network_status from app_info where app_class_name = '%s'", Utils::qtow(domain).c_str());
	sqlite.Exec(cmd);

	std::wstring networkStatus = L"未知";

	if ( sqlite.Step() )
		networkStatus = sqlite.GetText(0);

	sqlite.Finalize();
	sqlite.CloseDatabase();

	item->setText(3, Utils::wtoq(networkStatus));

	QFrame* btnContainer =new QFrame(this);
	btnContainer->setStyleSheet("QFrame{background-color:transparent;}");
	QHBoxLayout* layout = new QHBoxLayout;
	btnContainer->setLayout(layout);

	QPushButton* exportBtn = new QPushButton(this);
	int row = ui.trEmulatorApps->topLevelItemCount();
	connect(exportBtn, SIGNAL(clicked()), this, SLOT(OnBtnExportClicked()));
	exportBtn->setObjectName(QString("emulator_export_%1").arg(row));
	exportBtn->setFixedSize(75, 25);
	exportBtn->setText(Utils::stoq("导入"));

	/*QPushButton* installBtn = new QPushButton(this);
	connect(installBtn, SIGNAL(clicked()), this, SLOT(OnBtnInstallClicked()));
	installBtn->setObjectName(QString("emulator_install_%1").arg(row));
	installBtn->setFixedSize(75, 25);
	installBtn->setText(Utils::stoq("安装"));*/

	layout->setContentsMargins(0, 0, 29, 0);

	QSpacerItem* spaceItem = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);
	layout->addSpacerItem(spaceItem);
	//layout->addWidget(installBtn);
	layout->addWidget(exportBtn);

	item->setData(0, Qt::UserRole, (unsigned int)exportBtn);
	//item->setData(1, Qt::UserRole, (unsigned int)installBtn);

	ui.trEmulatorApps->addTopLevelItem(item);
	ui.trEmulatorApps->setItemWidget(item, 4, btnContainer);
}

void IOS_EmulatorDlg::SetExportEnable(bool enable)
{
	ui.btnExportAll->setEnabled(enable);
	ui.btnInstallAll->setEnabled(enable);

	for ( int i = 0; i < ui.trEmulatorApps->topLevelItemCount(); ++i )
	{
		QTreeWidgetItem* item = ui.trEmulatorApps->topLevelItem(i);
		QPushButton* exportBtn = (QPushButton*)(item->data(0, Qt::UserRole).toUInt());
		QPushButton* installBtn = (QPushButton*)(item->data(1, Qt::UserRole).toUInt());
		exportBtn->setEnabled(enable);
		//installBtn->setEnabled(enable);
	}

	ui.trEmulatorApps->setEnabled(enable);
}

void IOS_EmulatorDlg::Update()
{
	DataManager& dm = DataManager::GetInstance();
	std::wstring rootPath = dm.GetCurrentDevicePath() + L"\\Backup";

	if ( Utils::FileExist(rootPath) )
		ui.btnRecoveryBackup->show();
	else
		ui.btnRecoveryBackup->hide();

	if ( 0 == m_hUsbNotify )
		RegisterUsbNotify();

	emit RefreshDeviceList();

	ui.trEmulatorApps->clear();

	APP_InfoMap* appInfo = dm.GetAppInfoMap(dm.GetCurrentForensicsDir());
	ui.btnExportAll->hide();
	ui.btnInstallAll->hide();

	if ( NULL == appInfo )
		return;

	for ( APP_InfoMap::iterator it = appInfo->begin();
		it != appInfo->end();
		++it )
	{
		AddAppItem(
			Utils::wtoq((*it).second.name), 
			Utils::wtoq((*it).second.className), 
			Utils::wtoq(dm.GetCurrentDevicePath() + L"\\App\\Bin\\" + (*it).second.icon),
			Utils::wtoq((*it).second.version));

		//ui.btnExportAll->show();
		//ui.btnInstallAll->show();
	}
}

void IOS_EmulatorDlg::OnBtnExportClicked()
{
	QString senderBtn = sender()->objectName();

	QRegExp rx("emulator_export_(\\d+)");

	if ( rx.indexIn(senderBtn, 0) == -1 )
		return;

	int row = rx.cap(1).toInt();
	QTreeWidgetItem* item = ui.trEmulatorApps->topLevelItem(row);

	std::string className = Utils::qtos(item->text(1));
	char ansiClassname[1024] = {0};
	wsprintfA(ansiClassname, "%s", className.c_str());

	if ( !IsAppInstalled(m_deviceList[0], ansiClassname) )
	{
		MsgBox::Information(0, Utils::stoq("提示"), Utils::stoq("未安装应用程序\n请手动安装对应版本的应用程序"));
		return;
	}

	if ( !item )
		return;

	if ( *(m_deviceList[1]) != NULL )
	{
		MsgBox::Information(0, Utils::stoq("提示"), Utils::stoq("暂不支持处理多个 iOS 设备进行仿真\r\n请只连接 iOS 仿真机"));
		return;
	}

	m_tasks.clear();
	AddAppTask(item);

	ui.progress->setMaximum(2);

	emit ProcessExportTask();

	SetExportEnable(false);
	ui.progress->setValue(0);
	ui.lbEmulatorStatus->setText(Utils::stoq("正在导入应用数据 ..."));
}

void IOS_EmulatorDlg::OnBtnInstallClicked()
{
	QString senderBtn = sender()->objectName();

	QRegExp rx("emulator_install_(\\d+)");

	if ( rx.indexIn(senderBtn, 0) == -1 )
		return;

	int row = rx.cap(1).toInt();
	QTreeWidgetItem* item = ui.trEmulatorApps->topLevelItem(row);
	
	if ( !item )
		return;

	m_tasks.clear();
	AddAppTask(item);

	ui.progress->setMaximum(2);

	emit ProcessInstallTask();

	SetExportEnable(false);
	ui.progress->setValue(0);
	ui.lbEmulatorStatus->setText(Utils::stoq("正在安装 ..."));
}

void IOS_EmulatorDlg::AddAppTask(QTreeWidgetItem* item)
{	
	DataManager& dm = DataManager::GetInstance();
	std::wstring appPath = dm.GetCurrentDevicePath();

	std::wstring className = Utils::qtow(item->text(1));

	Task task;
	task.deviceId = m_deviceList[0];
	wsprintfW(task.appFilePath, L"%s\\App\\Bin\\%s.zip", appPath.c_str(), className.c_str());
	wsprintfA(task.appId, "%s", Utils::WideToAnsi(className).c_str());
	wsprintfW(task.appDataPath, L"%s\\App\\%s", appPath.c_str(), className.c_str());

	if ( !Utils::FileExist(task.appDataPath) )
	{
		wchar_t cmd[1024] = {0};
		std::wstring lzma = Utils::GetExePath() + L"\\7z.exe";
		wsprintfW(cmd, L"\"%s\" x \"%s.zip\" -o\"%s\"", lzma.c_str(), task.appDataPath, task.appDataPath);
		Utils::ExecuteProcessSync(cmd);
	}

	task.appName = Utils::qtow(item->text(0));

	m_tasks.push_back(task);
}

void IOS_EmulatorDlg::OnBtnExportAllClicked()
{
	m_tasks.clear();

	for ( int i = 0; i < ui.trEmulatorApps->topLevelItemCount(); ++i )
		AddAppTask(ui.trEmulatorApps->topLevelItem(i));

	ui.progress->setMaximum(m_tasks.size());

	emit ProcessExportTask();

	SetExportEnable(false);
	ui.progress->setValue(0);
	ui.lbEmulatorStatus->setText(Utils::stoq("正在导入应用数据 ..."));
}

void IOS_EmulatorDlg::OnBtnInstallAllClicked()
{
	m_tasks.clear();

	for ( int i = 0; i < ui.trEmulatorApps->topLevelItemCount(); ++i )
		AddAppTask(ui.trEmulatorApps->topLevelItem(i));

	ui.progress->setMaximum(m_tasks.size());

	emit ProcessInstallTask();

	SetExportEnable(false);
	ui.progress->setValue(0);
	ui.lbEmulatorStatus->setText(Utils::stoq("正在安装应用 ..."));
}

bool IOS_EmulatorDlg::winEvent( MSG * msg, long * result )
{
	if ( msg->message == WM_DEVICECHANGE )
	{
		switch(msg->wParam)
		{
		case DBT_DEVICEARRIVAL:
			
			if ( IsIOSDevice(msg) )
				DeviceConnected();

			break;

		case DBT_DEVICEREMOVECOMPLETE:

			if ( IsIOSDevice(msg) )
				DeviceRemoved();

			break;
		}
	}

	return false;
}

bool IOS_EmulatorDlg::IsIOSDevice(MSG* msg)
{
	DWORD							dwSize;
	HDEVINFO						hDevInfo = INVALID_HANDLE_VALUE;
	SP_DEVINFO_DATA					devInfo	 = {sizeof(SP_DEVINFO_DATA)};
	PDEV_BROADCAST_DEVICEINTERFACE  pDevInterface = NULL;
	WCHAR							wzFriendlyName[1024] = {0};

	pDevInterface = (PDEV_BROADCAST_DEVICEINTERFACE)msg->lParam;

	if ( DBT_DEVTYP_DEVICEINTERFACE != pDevInterface->dbcc_devicetype )
		return false;

	hDevInfo = SetupDiCreateDeviceInfoList(NULL, NULL);

	if ( INVALID_HANDLE_VALUE == hDevInfo )
		return false;

	SetupDiOpenDeviceInterface(hDevInfo, pDevInterface->dbcc_name, 0, NULL);
	SetupDiEnumDeviceInfo(hDevInfo, 0, &devInfo);
	SetupDiGetDeviceRegistryProperty(hDevInfo, &devInfo, SPDRP_FRIENDLYNAME, NULL, (LPBYTE)wzFriendlyName, sizeof(wzFriendlyName), &dwSize);

	bool ret = false;

	if ( 0 == lstrcmpiW(wzFriendlyName, L"Apple Mobile Device USB Driver") )
		ret = true;

	SetupDiDestroyDeviceInfoList(hDevInfo);

	return ret;
}

void IOS_EmulatorDlg::DeviceConnected()
{
	emit RefreshDeviceList();

	ui.btnRecoveryBackup->setEnabled(true);
	ui.lbEmulatorStatus->setText(Utils::stoq("设备已连接"));
}

void IOS_EmulatorDlg::DeviceRemoved()
{
	m_connected = false;

	for ( int i = 0; i < 24; ++i )
		memset(m_deviceList[i], 0, 1024);

	SetExportEnable(false);
	ui.btnRecoveryBackup->setEnabled(false);

	ui.lbEmulatorStatus->setText(Utils::stoq("设备已移除"));
}

void IOS_EmulatorDlg::ProcessTaskStatus( QString status )
{
	ui.lbEmulatorStatus->setText(status);
	ui.progress->setValue(ui.progress->value()+1);
}

void IOS_EmulatorDlg::ProcessTaskDone()
{
	ui.progress->setValue(ui.progress->maximum());
	ui.lbEmulatorStatus->setText(Utils::stoq("操作成功"));
	SetExportEnable(true);
}

void IOS_EmulatorDlg::ProcessTaskFailed()
{
	ui.progress->setValue(ui.progress->maximum());
	ui.lbEmulatorStatus->setText(Utils::stoq("操作失败"));
	SetExportEnable(true);
}

void IOS_EmulatorDlg::RefreshDeviceListDone()
{
	if ( m_deviceList[0][0] )
		m_connected = true;
	else
		m_connected = false;

	if ( m_connected )
		ui.lbEmulatorStatus->setText(Utils::stoq("已接入仿真机"));

	SetExportEnable(m_connected);
	ui.btnRecoveryBackup->setEnabled(m_connected);
}

void IOS_EmulatorDlg::OnBtnRecoveryBackupClicked()
{
	ui.btnRecoveryBackup->setEnabled(false);
	ui.progress->setValue(0);
	ui.progress->setMaximum(100);
	AddRecoveryBackupTask("");
	ui.lbEmulatorStatus->setText(Utils::stoq("正在进行备份恢复 ..."));

	emit RecoveryBackup();
}

void IOS_EmulatorDlg::RecoveryBackupDone()
{
	ui.btnRecoveryBackup->setEnabled(true);
	ui.progress->setValue(100);
	ui.lbEmulatorStatus->setText(Utils::stoq("备份恢复完成"));
}

void IOS_EmulatorDlg::RecoveryBackupFailed()
{
	Task& task = (* m_tasks.begin() );

	if ( 0 == strcmp(task.password, "") )
	{
		AddRecoveryBackupTask("1");
		emit RecoveryBackup();
	}
	else
	{
		RecoveryBackupTaskWithUserInput();
	}
}

void IOS_EmulatorDlg::RecoveryBackupTaskWithUserInput()
{
	char password[1024] = {0};

	if ( QDialog::Accepted == BackupPasswordDlg::Invoke(Utils::stoq("备份密码破解失败，请手动输入密码"), password) )
	{
		AddRecoveryBackupTask(password);
		emit RecoveryBackup();
	}
	else
	{
		ui.btnRecoveryBackup->setEnabled(true);
		ui.progress->setValue(100);
		ui.lbEmulatorStatus->setText(Utils::stoq("已取消备份恢复"));
	}
}

void IOS_EmulatorDlg::RecoveryBackupProcess(int value)
{
	ui.progress->setValue(value);
}

void IOS_EmulatorDlg::AddRecoveryBackupTask(const char* password)
{
	m_tasks.clear();

	DataManager& dm = DataManager::GetInstance();
	std::wstring appPath = dm.GetCurrentDevicePath();
	DEV_INFO& info = ( dm.GetDeviceMap() )[dm.GetCurrentDevice()];

	Task task;
	task.deviceId = m_deviceList[0];
	wsprintfA(task.srcId, "%s", info.baseDevInfo.szDevId);

	std::wstring dir = dm.GetCurrentForensicsDir();
	std::wstring rootPath = dm.GetCurrentDevicePath() + L"\\Backup";

	wsprintfW(task.rootPath, L"%s", rootPath.c_str());
	wsprintfA(task.password, "%s", password);

	m_tasks.push_back(task);
}