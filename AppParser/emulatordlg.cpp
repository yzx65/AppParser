#include "StdAfx.h"
#include "emulatordlg.h"

#include "datamanager.h"
#include <string>

#include "android_emulatordlg.h"
#include "ios_emulatordlg.h"

EmulatorDlg::EmulatorDlg(QWidget *parent)
	: QFrame(parent)
{
	ui.setupUi(this);

	m_ios = new IOS_EmulatorDlg(this);
	ui.stack->addWidget(m_ios);

	m_android = new Android_EmulatorDlg(this);
	ui.stack->addWidget(m_android);
}

EmulatorDlg::~EmulatorDlg()
{

}

void EmulatorDlg::Update()
{
	DataManager& dm = DataManager::GetInstance();
	std::map<std::wstring, DEV_INFO>& infoMap = dm.GetDeviceMap();
	DEV_INFO info = infoMap[dm.GetCurrentDevice()];

	if ( info.baseDevInfo.devType == DEV_TYPE_ANDROID )
		m_android->Update();
	else
		m_ios->Update();

	ui.stack->setCurrentIndex(info.baseDevInfo.devType != DEV_TYPE_IOS);
}