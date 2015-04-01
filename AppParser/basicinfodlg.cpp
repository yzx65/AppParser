#include "StdAfx.h"
#include "basicinfodlg.h"
#include "utils.h"
#include "datamanager.h"

BasicInfoDlg::BasicInfoDlg(QWidget *parent)
	: QFrame(parent)
{
	ui.setupUi(this);
	Utils::InitStyle(this);
}

BasicInfoDlg::~BasicInfoDlg()
{

}

void BasicInfoDlg::Update()
{
	DataManager& dm = DataManager::GetInstance();
	std::wstring curDev = dm.GetCurrentDevice();

	std::map<std::wstring, DEV_INFO>& devMap = dm.GetDeviceMap();

	if ( devMap.find(curDev) == devMap.end() )
		return;

	DEV_INFO& info = devMap[curDev];

	if ( info.baseDevInfo.devType == DEV_TYPE_ANDROID )
		ui.picture->setPixmap(QPixmap(":/Image/android.png"));
	else
		ui.picture->setPixmap(QPixmap(":/Image/iphone_5s_gold.png"));

	ui.lbDevType->setText(info.baseDevInfo.devType == DEV_TYPE_IOS ? "iOS" : "Android");
	ui.lbDevName->setText(Utils::wtoq(Utils::Utf8ToWide(info.baseDevInfo.szDevName)));
	ui.lbDevModel->setText(Utils::stoq(info.baseDevInfo.szDevModel));
	ui.lbDevNumber->setText(Utils::stoq(info.baseDevInfo.szNumber));
	ui.lbOsVersion->setText(Utils::stoq(info.baseDevInfo.szOSVersion));
	ui.lbSerialNum->setText(Utils::stoq(info.baseDevInfo.szSerialNum));
	ui.lbCpuArc->setText(Utils::stoq(info.baseDevInfo.szCpuArc));

	char usage[1024] = {0};
	double sysUsed = ((double)info.baseDevInfo.diskUsage.ui64SysUsed) / 1024 / 1024 / 1024;
	double sysTotal = ((double)info.baseDevInfo.diskUsage.ui64SysTtl) / 1024 / 1024 / 1024;
	double userUsed = ((double)info.baseDevInfo.diskUsage.ui64UserUsed) / 1024 / 1024 / 1024;
	double userTotal = ((double)info.baseDevInfo.diskUsage.ui64UserTtl) / 1024 / 1024 / 1024;

	sprintf(usage, "%.2fG / %.2fG", sysUsed, sysTotal);
	ui.lbSysUsage->setText(Utils::stoq(usage));

	sprintf(usage, "%.2fG / %.2fG", userUsed, userTotal);
	ui.lbUserUsage->setText(Utils::stoq(usage));

	ui.prgSystemUsage->setMaximum((int)(sysTotal*100)+1);
	ui.prgSystemUsage->setValue((int)(sysUsed*100)+1);

	ui.prgUserUsage->setMaximum((int)(userTotal*100)+1);
	ui.prgUserUsage->setValue((int)(userUsed*100)+1);

	if ( info.baseDevInfo.devType == DEV_TYPE_IOS )
	{
		ui.info_7->setText(Utils::stoq("是否越狱"));

		if ( info.baseDevInfo.bJailBroken )
			ui.lbRoot->setText(Utils::stoq("已越狱"));
		else
			ui.lbRoot->setText(Utils::stoq("未越狱"));

		ui.info_11->setText(Utils::stoq("设备颜色"));
		ui.lbExtraInfo->setText(Utils::stoq(info.unDevInfo.iosDevInfo.szColor));
	}
	else
	{
		ui.info_7->setText(Utils::stoq("是否 root"));

		if ( info.baseDevInfo.bJailBroken )
			ui.lbRoot->setText(Utils::stoq("已 root"));
		else
			ui.lbRoot->setText(Utils::stoq("未 root"));

		ui.info_11->setText(Utils::stoq("制造厂商"));
		ui.lbExtraInfo->setText(Utils::stoq(info.unDevInfo.androidDevInfo.szManu));
	}
}
