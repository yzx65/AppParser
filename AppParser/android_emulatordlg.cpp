#include "StdAfx.h"
#include "android_emulatordlg.h"
#include "utils.h"

#include "processproxy.h"
#include "AdbController.h"
#include "datamanager.h"

#include "msgbox.h"
#include "selectemulatordlg.h"


ExportWorker::ExportWorker(const ExportTaskList& taskList)
	: m_taskList(taskList)
	, m_quit(false)
{
	m_adb = new AdbController(Utils::GetExePath() + L"\\tools\\adb.exe");
}

ExportWorker::~ExportWorker()
{
	m_adb->CloseAdb();
	delete m_adb;
}

void ExportWorker::CheckEmulatorReady()
{
	bool notify = false;

	while ( !m_quit )
	{
		Sleep(100);

		if ( m_adb->InitAdb() > 1 )
		{
			emit EmulatorReady();
			break;
		}
	}
}

void ExportWorker::ProcessExportTask()
{
	DataManager& dm = DataManager::GetInstance();
	APP_InfoMap* appMap = dm.GetAppInfoMap(dm.GetCurrentForensicsDir());

	if ( NULL == appMap )
		return;

	for ( ExportTaskList::const_iterator it = m_taskList.begin();
		  it != m_taskList.end();
		  ++it )
	{
		APP_Info& info = (*appMap)[*it];

		std::wstring dataDir = dm.GetDirPath() + L"\\" + dm.GetCurrentForensicsDir() + L"\\" + info.className;

		if ( ! Utils::FileExist(dataDir) )
		{
			Utils::ExtractPackage(dataDir + L".tar.gz");
			//Utils::ExtractPackage(dataDir + L".cpio.gz");
		}

		m_adb->ExecuteShellCmd(L"su -c \"pm set-install-location 1\"");

		emit ProcessTaskStatus(Utils::wtoq(info.name + L" : 正在删除残留数据  ... "));
		m_adb->UnInstallApk(info.className);

		emit ProcessTaskStatus(Utils::wtoq(info.name + L" : 正在安装 apk ... "));
		m_adb->InstallApk(dm.GetDirPath() + L"\\" + dm.GetCurrentForensicsDir() + L"\\Bin\\" + info.apk);

		emit ProcessTaskStatus(Utils::wtoq(info.name + L" : 正在启动服务 ... "));
		wchar_t cmd[1024] = {0};
		wsprintfW(cmd, L"am start -n %s/%s", info.className.c_str(), info.activity.c_str());
		m_adb->ExecuteShellCmd(cmd);

		Sleep(1000 * 10);

		emit ProcessTaskStatus(Utils::wtoq(info.name + L" : 正在导入数据 ... "));
		//m_adb->DeleteDir(std::wstring(L"/data/data/") + info.className);
		m_adb->CopyFile(
			dataDir, 
			std::wstring(L"/data/data/") + info.className);
	}

	emit ProcessTaskStatus(Utils::wtoq(L"正在重启模拟器 ... "));
	m_adb->ExecuteCommand(L"reboot");
	
	emit ProcessTaskDone();
}

void ExportWorker::ProcessUninstallTask()
{
	DataManager& dm = DataManager::GetInstance();
	APP_InfoMap* appMap = dm.GetAppInfoMap(dm.GetCurrentForensicsDir());

	if ( NULL == appMap )
		return;

	for ( ExportTaskList::const_iterator it = m_taskList.begin();
		it != m_taskList.end();
		++it )
	{
		APP_Info& info = (*appMap)[*it];

		emit ProcessTaskStatus(Utils::wtoq(info.name + L" : 正在卸载  ... "));
		m_adb->UnInstallApk(info.className);
	}

	emit ProcessTaskDone();
}

Android_EmulatorDlg::Android_EmulatorDlg(QWidget *parent)
	: QFrame(parent)
{
	ui.setupUi(this);
	Utils::InitStyle(this);
	
	m_emulator = new ProcessProxy("player.exe");
	m_exportWorker = new ExportWorker(m_exportTask);
	m_exportThread = new QThread;
	m_exportWorker->moveToThread(m_exportThread);
	m_waitDlg = new WaitDlg(this);
	m_waitDlg->hide();
	ui.btnExportAll->hide();
	ui.btnUninstallAll->hide();
	ui.lbEmulatorStatus->setText(Utils::stoq("模拟器未启动"));

	InitConnection();
	InitTreeView();

	SetExportEnable(false);
}

Android_EmulatorDlg::~Android_EmulatorDlg()
{
	if ( m_exportThread->isRunning() )
	{
		m_exportThread->quit();
		Sleep(200);
		m_exportThread->terminate();
		m_exportThread->wait();
	}

	delete m_emulator;
	delete m_exportWorker;
	delete m_exportThread;
}

void Android_EmulatorDlg::Update()
{
	ui.trEmulatorApps->clear();

	DataManager& dm = DataManager::GetInstance();
	APP_InfoMap* appInfo = dm.GetAppInfoMap(dm.GetCurrentForensicsDir());
	ui.btnExportAll->hide();

	if ( NULL == appInfo )
		return;

	int i = 0;

	for ( APP_InfoMap::iterator it = appInfo->begin();
		  it != appInfo->end();
		  ++it )
	{
		AddAppItem(
			Utils::wtoq((*it).second.name), 
			Utils::wtoq((*it).second.className), 
			Utils::wtoq(dm.GetDirPath() + L"\\" + dm.GetCurrentForensicsDir() + L"\\Bin\\" + (*it).second.icon),
			Utils::wtoq((*it).second.version));

		//ui.btnExportAll->show();
	}

}

void Android_EmulatorDlg::InitConnection()
{
	connect(ui.btnExportAll, SIGNAL(clicked()), this, SLOT(OnBtnExportAllClicked()));
	connect(ui.btnUninstallAll, SIGNAL(clicked()), this, SLOT(OnBtnUninstallAllClicked()));
	connect(m_emulator, SIGNAL(Finished()), this, SLOT(EmulatorFinished()));
	connect(m_emulator, SIGNAL(Attached()), this, SLOT(EmulatorAttached()));
	connect(ui.btnEmulator, SIGNAL(clicked()), this, SLOT(OnBtnEmulatorClicked()));
	connect(ui.btnToggleNetwork, SIGNAL(clicked()), this, SLOT(OnBtnToggleNetworkClicked()));

	connect(m_exportWorker, SIGNAL(ProcessTaskStatus(QString)), this, SLOT(ProcessTaskStatus(QString)));
	connect(m_exportWorker, SIGNAL(ProcessTaskDone()), this, SLOT(ProcessTaskDone()));
	connect(m_exportWorker, SIGNAL(EmulatorReady()), this, SLOT(EmulatorReady()));
	connect(this, SIGNAL(ProcessExportTask()), m_exportWorker, SLOT(ProcessExportTask()));
	connect(this, SIGNAL(ProcessUninstallTask()), m_exportWorker, SLOT(ProcessUninstallTask()));
	connect(this, SIGNAL(CheckEmulatorReady()), m_exportWorker, SLOT(CheckEmulatorReady()));

	m_exportThread->start();
}

void Android_EmulatorDlg::InitTreeView()
{
	ui.trEmulatorApps->clear();
	ui.trEmulatorApps->header()->resizeSection(0, 175);
	ui.trEmulatorApps->header()->resizeSection(1, 175);
	ui.trEmulatorApps->header()->resizeSection(2, 125);
	ui.trEmulatorApps->header()->resizeSection(3, 145);
}

void Android_EmulatorDlg::AddAppItem(QString name, QString domain, QString icon, QString version)
{
	QTreeWidgetItem* item = new QTreeWidgetItem;

	item->setIcon(0, QIcon(QPixmap(icon)));
	item->setText(0, name);
	item->setText(1, domain);
	item->setText(2, version);

	SQLiteHelper sqlite;
	sqlite.ConnectToDatabase(Utils::GetExePath() + L"\\android_appinfo.db");

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

	QPushButton* uninstallBtn = new QPushButton(this);
	connect(uninstallBtn, SIGNAL(clicked()), this, SLOT(OnBtnUninstallClicked()));
	uninstallBtn->setObjectName(QString("emulator_uninstall_%1").arg(row));
	uninstallBtn->setFixedSize(75, 25);
	uninstallBtn->setText(Utils::stoq("卸载"));

	layout->setContentsMargins(0, 0, 29, 0);

	QSpacerItem* spaceItem = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);
	layout->addSpacerItem(spaceItem);
	layout->addWidget(exportBtn);
	layout->addWidget(uninstallBtn);

	item->setData(0, Qt::UserRole, (unsigned int)exportBtn);
	item->setData(1, Qt::UserRole, (unsigned int)uninstallBtn);

	ui.trEmulatorApps->addTopLevelItem(item);
	ui.trEmulatorApps->setItemWidget(item, 4, btnContainer);
}

void Android_EmulatorDlg::SetExportEnable(bool enable)
{
	ui.btnExportAll->setEnabled(enable);
	ui.btnUninstallAll->setEnabled(enable);

	for ( int i = 0; i < ui.trEmulatorApps->topLevelItemCount(); ++i )
	{
		QTreeWidgetItem* item = ui.trEmulatorApps->topLevelItem(i);
		QPushButton* exportBtn = (QPushButton*)(item->data(0, Qt::UserRole).toUInt());
		exportBtn->setEnabled(enable);
		
		QPushButton* uninstallBtn = (QPushButton*)(item->data(1, Qt::UserRole).toUInt());
		uninstallBtn->setEnabled(enable);
	}

	ui.trEmulatorApps->setEnabled(enable);

	ui.btnToggleNetwork->setEnabled(enable);
}

void Android_EmulatorDlg::OnBtnExportClicked()
{
	QString senderBtn = sender()->objectName();

	QRegExp rx("emulator_export_(\\d+)");

	if ( rx.indexIn(senderBtn, 0) == -1 )
		return;

	int row = rx.cap(1).toInt();
	QTreeWidgetItem* item = ui.trEmulatorApps->topLevelItem(row);

	if ( !item )
		return;

	AdbController adb(Utils::GetExePath() + L"\\tools\\adb.exe");

	if ( adb.InitAdb() > 2 )
	{
		MsgBox::Information(0, Utils::stoq("提示"), Utils::stoq("不支持 Android 实机仿真\r\n请拔除 Android 设备"));
		return;
	}

	DataManager& dm = DataManager::GetInstance();
	APP_InfoMap* appMap = dm.GetAppInfoMap(dm.GetCurrentForensicsDir());
	APP_Info& info = (*appMap)[Utils::qtow(item->text(0))];
	std::wstring apkName = dm.GetDirPath() + L"\\" + dm.GetCurrentForensicsDir() + L"\\Bin\\" + info.apk;

	if ( !Utils::FileExist(apkName) )
	{
		MsgBox::Information(0, Utils::stoq("提示"), Utils::stoq("未拷贝应用程序\n请手动安装对应版本的应用程序"));
		return;
	}

	m_exportTask.clear();
	m_exportTask.push_back(Utils::qtow(item->text(0)));

	ui.progress->setMaximum(5);

	emit ProcessExportTask();
	
	SetExportEnable(false);
	ui.progress->setValue(0);
	ui.lbEmulatorStatus->setText(Utils::stoq("正在导入应用数据 ..."));
}

void Android_EmulatorDlg::OnBtnExportAllClicked()
{
	m_exportTask.clear();

	for ( int i = 0; i < ui.trEmulatorApps->topLevelItemCount(); ++i )
		m_exportTask.push_back(Utils::qtow(ui.trEmulatorApps->topLevelItem(i)->text(0)));

	ui.progress->setMaximum(m_exportTask.size()*4+1);

	emit ProcessExportTask();

	SetExportEnable(false);
	ui.progress->setValue(0);
	ui.lbEmulatorStatus->setText(Utils::stoq("正在导入应用数据 ..."));
}

void Android_EmulatorDlg::OnBtnUninstallClicked()
{
	QString senderBtn = sender()->objectName();

	QRegExp rx("emulator_uninstall_(\\d+)");

	if ( rx.indexIn(senderBtn, 0) == -1 )
		return;

	int row = rx.cap(1).toInt();
	QTreeWidgetItem* item = ui.trEmulatorApps->topLevelItem(row);

	if ( !item )
		return;

	m_exportTask.clear();
	m_exportTask.push_back(Utils::qtow(item->text(0)));

	ui.progress->setMaximum(1);

	emit ProcessUninstallTask();

	SetExportEnable(false);
	ui.progress->setValue(0);
	ui.lbEmulatorStatus->setText(Utils::stoq("正在卸载应用 ..."));
}

void Android_EmulatorDlg::OnBtnUninstallAllClicked()
{
	m_exportTask.clear();

	for ( int i = 0; i < ui.trEmulatorApps->topLevelItemCount(); ++i )
		m_exportTask.push_back(Utils::qtow(ui.trEmulatorApps->topLevelItem(i)->text(0)));

	ui.progress->setMaximum(m_exportTask.size());

	emit ProcessUninstallTask();

	SetExportEnable(false);
	ui.progress->setValue(0);
	ui.lbEmulatorStatus->setText(Utils::stoq("正在卸载应用 ..."));
}

void Android_EmulatorDlg::OnBtnEmulatorClicked()
{
	if ( QDialog::Accepted == SelectEmulatorDlg::Invoke() )
		ui.btnEmulator->setEnabled(false);
}

void Android_EmulatorDlg::OnBtnToggleNetworkClicked()
{
	AdbController adb(Utils::GetExePath() + L"\\tools\\adb.exe");

	if ( ui.btnToggleNetwork->text() == Utils::stoq("关闭网络") )
	{
		adb.ExecuteShellCmd(L"svc wifi disable");
		ui.btnToggleNetwork->setText(Utils::stoq("开启网络"));
		ui.lbEmulatorStatus->setText(Utils::stoq("模拟器 Wi-Fi 已关闭"));
	}
	else
	{
		adb.ExecuteShellCmd(L"svc wifi enable");
		ui.btnToggleNetwork->setText(Utils::stoq("关闭网络"));
		ui.lbEmulatorStatus->setText(Utils::stoq("模拟器 Wi-Fi 已开启"));
	}
}

void Android_EmulatorDlg::EmulatorFinished()
{
	SetExportEnable(false);
	ui.lbEmulatorStatus->setText(Utils::stoq("模拟器已关闭"));
	ui.btnEmulator->setEnabled(true);
}

void Android_EmulatorDlg::EmulatorAttached()
{
	emit CheckEmulatorReady();
	ui.lbEmulatorStatus->setText(Utils::stoq("正在启动模拟器 ..."));
}

void Android_EmulatorDlg::ProcessTaskStatus(QString status)
{
	ui.lbEmulatorStatus->setText(status);
	ui.progress->setValue(ui.progress->value() + 1);
}

void Android_EmulatorDlg::ProcessTaskDone()
{
	SetExportEnable(true);
	ui.lbEmulatorStatus->setText(Utils::stoq("操作完成"));
}

void Android_EmulatorDlg::EmulatorReady()
{
	SetExportEnable(true);
	ui.lbEmulatorStatus->setText(Utils::stoq("模拟器已启动"));

	AdbController adb(Utils::GetExePath() + L"\\tools\\adb.exe");
	adb.ExecuteShellCmd(L"svc wifi enable");
}