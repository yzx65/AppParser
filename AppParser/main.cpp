#include "stdafx.h"
#include "appdlg.h"
#include "FramelessDlg.h"
#include <QtGui>
#include "utils.h"
#include <time.h>
#include <QFileInfo>

#include <AdkLicense.h>
#include "datamanager.h"
#include "DbgHelper.h"
#include "processproxy.h"

#include "RemoteInjecter.h"

//#define CHECK_LICENSE

void Test()
{
	//SQLiteHelper sqlite;
	//std::wstring db = Utils::GetExePath() + L"\\app_info.db";
	//sqlite.ConnectToDatabase(db);
	//sqlite.Exec(L"create table app_info (app_name TEXT, app_class_name TEXT, app_network_status TEXT)");
	//sqlite.Step();
	//sqlite.Finalize();
	//sqlite.CloseDatabase();
}

void InitStyle(QApplication& a)
{
	QFile qss(Utils::wtoq(Utils::GetExePath() + L"\\common_style.qss"));

	if ( !qss.open(QIODevice::ReadOnly | QIODevice::Text) )
		return;

	QTextStream ts(&qss);
	a.setStyleSheet(ts.readAll());
}

QString GetDefaultForensicsDir()
{
	QFileInfo info;
	QString file = "C:\\PhoneForensics";

	for ( char driver = 'C'; driver <= 'Z'; ++driver )
	{
		file[0] = driver;
		info.setFile(file);

		if ( info.exists() )
			return file;
	}

	return "";
}

BOOL WINAPI AdkGrandDogCheck(char *szProductName, char* szPassword);

BOOL WINAPI CheckLicense()
{
	WCHAR	wzLicence[MAX_PATH] = {0};

	GetModuleFileNameW(NULL, wzLicence, MAX_PATH);
	*wcsrchr(wzLicence, L'\\') = L'\0';
	lstrcatW(wzLicence, L"\\License.dat");

	TUOJIE_LICENSE	tjLicence = {0};

	if (!AdkGetLicenseInfo(wzLicence, &tjLicence))
	{
		MessageBoxW(NULL, L"未找到Licence.dat文件", L"警告", MB_OK);
		return FALSE;
	}

	if ( !AdkGrandDogCheck(tjLicence.szDogName, tjLicence.szDogPass) )
	{
		MessageBoxW(NULL, L"对应的硬件狗不存在", L"警告", MB_OK);
		return FALSE;
	}

	return true;
}

int main(int argc, char *argv[])
{

#ifdef CHECK_LICENSE
	if ( !CheckLicense() )
		return -1;
#endif

	DbgHelper::InstallDbgHelper();

	Test();

	PROCESS_INFORMATION procInfo = ProcessProxy::CreateProcess((Utils::GetExePath() + L"\\GenymotionMonitor.exe").c_str());
	CloseHandle(procInfo.hThread);
	CloseHandle(procInfo.hProcess);

	QApplication a(argc, argv);
	a.setWindowIcon(QIcon(QPixmap(":/Image/icon.png")));

	QTranslator* ts = new QTranslator;
	ts->load(":/qt_zh_CN.qm");
	a.installTranslator(ts);

	FramelessDlg dlg(0);
	AppDlg* app = new AppDlg(&dlg);

	dlg.SetDlg(app);
	dlg.SetTitle(Utils::GetConfigValue("title", "value"));
	dlg.SetSubTitle(Utils::stoq("未选择要分析的设备"));
	dlg.setMinimumSize(1020, 600);

	QObject::connect(app, SIGNAL(AddMenuAction(QAction*)), &dlg, SLOT(AddMenuAction(QAction*)));
	QObject::connect(app, SIGNAL(AddSubMenu(QMenu*)), &dlg, SLOT(AddSubMenu(QMenu*)));
	QObject::connect(app, SIGNAL(RemoveMenuAction(QAction*)), &dlg, SLOT(RemoveMenuAction(QAction*)));
	QObject::connect(app, SIGNAL(SetSubTitle(QString)), &dlg, SLOT(SetSubTitle(QString)));

	app->InitAction();
	InitStyle(a);

	dlg.show();
	dlg.CenterWindow();

	app->AnalyzeDir(GetDefaultForensicsDir());

	a.exec();

	ProcessProxy::KillProcess(L"GenymotionMonitor.exe");

	return 0;
}
