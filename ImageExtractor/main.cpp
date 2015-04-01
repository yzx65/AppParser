#include <QtGui>

#include "imageextractor.h"
#include "framelessdlg.h"
#include "utils.h"
#include "SQLiteHelper.h"

#include <Windows.h>
#include <AdkLicense.h>

#include "msgbox.h"

void InitStyle(QApplication& a)
{
	QFile qss(Utils::wtoq(Utils::GetExePath() + L"\\common_style.qss"));

	if ( !qss.open(QIODevice::ReadOnly | QIODevice::Text) )
		return;

	QTextStream ts(&qss);
	a.setStyleSheet(ts.readAll());
}

void Test()
{

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

	QApplication a(argc, argv);
	a.setWindowIcon(QIcon(QPixmap(":/Image/icon.png")));

	std::wstring dump;

	if ( !Utils::HaveFlashDisk(dump) )
	{
		MsgBox::Information(0, Utils::stoq("提示"), Utils::stoq("未检测到可用的 U 盘设备"));
		return -1;
	}

	Test();

	QTranslator* ts = new QTranslator;
	ts->load(":/qt_zh_CN.qm");
	a.installTranslator(ts);

	FramelessDlg dlg(0, MIN_BUTTON | CLOSE_BUTTON);
	dlg.SetTitle(Utils::GetConfigValue("image_tool_title", "value"));
	ImageExtractor* extractor = new ImageExtractor(&dlg);

	dlg.SetDlg(extractor);
	dlg.setMinimumSize(500, 293);

	InitStyle(a);

	dlg.show();
	dlg.CenterWindow();
	return a.exec();
}
