#include "StdAfx.h"
#include "parsedlg.h"
#include "utils.h"
#include "framelessdlg.h"
#include "datamanager.h"
#include "parsethread.h"

#include "backuppassworddlg.h"

void ParseDlg::Invoke(std::wstring deviceName, bool clear)
{
	FramelessDlg container(0, 0);
	ParseDlg* dlg = new ParseDlg(&container, deviceName, clear);

	connect(dlg, SIGNAL(OK()), &container, SLOT(accept()));

	container.SetDlg(dlg);
	WCHAR title[1024] = {0};
	wsprintfW(title, L"解析设备 %s ", deviceName.substr(0, deviceName.find(L'\\')).c_str());
	container.SetTitle(Utils::wtoq(title));
	container.setFixedSize(400, 120);
	container.CenterWindow();

	dlg->StartParse();
	container.exec();	
}

ParseDlg::ParseDlg(QWidget *parent, std::wstring key, bool clear)
	: QFrame(parent)
	, m_key(key)
	, m_clear(clear)
{
	ui.setupUi(this);
	Utils::InitStyle(this);

	InitConnections();
}

ParseDlg::~ParseDlg()
{
	if ( m_parse->isRunning() )
	{
		m_parse->terminate();
		m_parse->wait();
	}

	delete m_parse;
}

void ParseDlg::InitConnections()
{
	m_parse = new ParseThread(0);
	connect(m_parse, SIGNAL(CurrentProcess(int)),this, SLOT(CurrentProcess(int)));
	connect(m_parse, SIGNAL(CurrentStatus(QString)),this, SLOT(CurrentStatus(QString)));
	connect(m_parse, SIGNAL(TotalProcess(int)),this, SLOT(TotalProcess(int)));
	connect(m_parse, SIGNAL(ParseDone()),this, SLOT(ParseDone()));
	connect(m_parse, SIGNAL(ParseFailed()),this, SLOT(ParseFailed()));

	connect(m_parse, SIGNAL(QueryIosBackupPassword()), this, SLOT(OnQueryIosBackupPassword()));
}


void ParseDlg::StartParse()
{
	m_parse->SetKey(m_key);
	m_parse->SetClear(m_clear);
	m_parse->start();
}

void ParseDlg::ParseDone()
{
	DataManager& dm = DataManager::GetInstance();

	std::wstring keychainFile = dm.GetDirPath() + L"\\" + dm.GetCurrentForensicsDir() + L"\\keychain\\keychain.csv";

	if ( Utils::FileExist(keychainFile) )
	{
		QString csvName = QFileDialog::getSaveFileName(this, Utils::stoq("请选择保存 Keychain 密码信息的路径"), Utils::stoq("密码信息.csv"));

		if ( !csvName.isEmpty() )
		{
			csvName.replace("/", "\\");
			CopyFile(keychainFile.c_str(), Utils::qtow(csvName).c_str(), FALSE);
		}
	}

	emit OK();
}

void ParseDlg::ParseFailed()
{

}

void ParseDlg::CurrentStatus( QString status )
{
	ui.lbStatus->setText(status);
}

void ParseDlg::CurrentProcess( int value )
{
	ui.progress->setValue(value);
}

void ParseDlg::TotalProcess( int value )
{
	ui.progress->setMaximum(value);
}

void ParseDlg::OnQueryIosBackupPassword()
{
	char password[1024] = {0};

	if ( QDialog::Accepted == BackupPasswordDlg::Invoke(Utils::stoq("备份密码破解失败，请手动输入密码"), password) )
		m_parse->SetExtractPassword(password);
	else
		m_parse->CancleExtract();
	
	m_parse->InputFinished();
	Sleep(0);
}