#include "StdAfx.h"
#include "appdlg.h"

#include "navmodel.h"
#include "navdelegate.h"
#include "utils.h"

#include <QFileDialog>

#include "msgbox.h"
#include "qqinfodlg.h"
#include "weixininfodlg.h"
#include "lineinfodlg.h"
#include "browserinfodlg.h"
#include "smsinfodlg.h"
#include "callinfodlg.h"
#include "selectdirdlg.h"
#include "basicinfodlg.h"
#include "contactinfodlg.h"
#include "emulatordlg.h"
#include "analyzeimagedlg.h"
#include "parsedlg.h"
#include "keychaininfodlg.h"
#include "delinfodlg.h"

#include "mapinfodlg.h"

#include "waitdlg.h"

AppDlg::AppDlg(QWidget *parent)
	: QFrame(parent)
	, m_deviceMenu(NULL)
{
	ui.setupUi(this);

	m_save = new SaveDataThread(this);
	m_wait = new WaitDlg(this);
	m_wait->hide();

	InitNavBar();
	InitAppStack();
	InitConnection();
	InitDragAndDrop();
}

AppDlg::~AppDlg()
{
	delete m_save;
}

void AppDlg::InitNavBar()
{
	m_navModel = new NavModel(this);
	m_navModel->ReadDataFromConfig(Utils::wtoq(Utils::GetExePath() + L"\\config.xml"));
	m_navDelegate = new NavDelegate(this);
	ui.lstNav->setModel(m_navModel);
	ui.lstNav->setItemDelegate(m_navDelegate);
	connect(ui.lstNav, SIGNAL(doubleClicked(const QModelIndex &)), m_navModel, SLOT(Collapse(const QModelIndex&)));

	ui.lstNav->installEventFilter(this);

	m_btnCollapseNavBar = new QPushButton(this);
	connect(m_btnCollapseNavBar, SIGNAL(clicked()), this, SLOT(OnBtnCollapseNavBarClicked()));
}

void AppDlg::InitAppStack()
{
	int i = 0;

	m_basicInfo = new BasicInfoDlg(this);
	ui.stkApp->addWidget(m_basicInfo);
	m_appMap[L"基本信息"] = i++;

	m_keyChain = new KeyChainInfoDlg(this);
	ui.stkApp->addWidget(m_keyChain);
	m_appMap[L"密码信息"] = i++;
	connect(ui.edtFilter, SIGNAL(textChanged(QString)), m_keyChain, SLOT(OnEdtFilterTextChanged(QString)));

	m_sms = new SmsInfoDlg(this);
	ui.stkApp->addWidget(m_sms);
	m_appMap[L"短信"] = i++;
	connect(ui.edtFilter, SIGNAL(textChanged(QString)), m_sms, SLOT(OnEdtFilterTextChanged(QString)));

	m_call = new CallInfoDlg(this);
	ui.stkApp->addWidget(m_call);
	m_appMap[L"通话记录"] = i++;
	connect(ui.edtFilter, SIGNAL(textChanged(QString)), m_call, SLOT(OnEdtFilterTextChanged(QString)));

	m_contactInfo = new ContactInfoDlg(this);
	ui.stkApp->addWidget(m_contactInfo);
	m_appMap[L"通讯录"] = i++;
	connect(ui.edtFilter, SIGNAL(textChanged(QString)), m_contactInfo, SLOT(OnEdtFilterTextChanged(QString)));

	m_smsDel = new DelInfoDlg(this, DelInfoDlg::SMS);
	ui.stkApp->addWidget(m_smsDel);
	m_appMap[L"已删除短信"] = i++;

	m_callDel = new DelInfoDlg(this, DelInfoDlg::RECORD);
	ui.stkApp->addWidget(m_callDel);
	m_appMap[L"已删除通话记录"] = i++;

	m_contactDel = new DelInfoDlg(this, DelInfoDlg::CONTACT);
	ui.stkApp->addWidget(m_contactDel);
	m_appMap[L"已删除通讯录"] = i++;

	m_weixin = new WeixinInfoDlg(this);
	ui.stkApp->addWidget(m_weixin);
	m_appMap[L"微信"] = i++;
	connect(ui.edtFilter, SIGNAL(textChanged(QString)), m_weixin, SLOT(OnEdtFilterTextChanged(QString)));

	m_qq = new QQInfoDlg(this);
	ui.stkApp->addWidget(m_qq);
	m_appMap[L"QQ"] = i++;
	connect(ui.edtFilter, SIGNAL(textChanged(QString)), m_qq, SLOT(OnEdtFilterTextChanged(QString)));

	m_line = new LineInfoDlg(this);
	ui.stkApp->addWidget(m_line);
	m_appMap[L"Line"] = i++;
	connect(ui.edtFilter, SIGNAL(textChanged(QString)), m_line, SLOT(OnEdtFilterTextChanged(QString)));

	m_defaultBrowser = new BrowserInfoDlg(this, BrowserInfoDlg::BROWSER_DEFAULT);
	ui.stkApp->addWidget(m_defaultBrowser);
	m_appMap[L"系统浏览器"] = i++;
	connect(ui.edtFilter, SIGNAL(textChanged(QString)), m_defaultBrowser, SLOT(OnEdtFilterTextChanged(QString)));

	m_ucBrowser = new BrowserInfoDlg(this, BrowserInfoDlg::BROWSER_UC);
	ui.stkApp->addWidget(m_ucBrowser);
	m_appMap[L"UC浏览器"] = i++;
	connect(ui.edtFilter, SIGNAL(textChanged(QString)), m_ucBrowser, SLOT(OnEdtFilterTextChanged(QString)));

	m_qqBrowser = new BrowserInfoDlg(this, BrowserInfoDlg::BROWSER_QQ);
	ui.stkApp->addWidget(m_qqBrowser);
	m_appMap[L"QQ浏览器"] = i++;
	connect(ui.edtFilter, SIGNAL(textChanged(QString)), m_qqBrowser, SLOT(OnEdtFilterTextChanged(QString)));

	m_baiduBrowser = new BrowserInfoDlg(this, BrowserInfoDlg::BROWSER_BAIDU);
	ui.stkApp->addWidget(m_baiduBrowser);
	m_appMap[L"百度浏览器"] = i++;
	connect(ui.edtFilter, SIGNAL(textChanged(QString)), m_baiduBrowser, SLOT(OnEdtFilterTextChanged(QString)));

	m_jinshanBrowser = new BrowserInfoDlg(this, BrowserInfoDlg::BROWSER_JINSHAN);
	ui.stkApp->addWidget(m_jinshanBrowser);
	m_appMap[L"猎豹浏览器"] = i++;
	connect(ui.edtFilter, SIGNAL(textChanged(QString)), m_jinshanBrowser, SLOT(OnEdtFilterTextChanged(QString)));

	m_safariBrowser = new BrowserInfoDlg(this, BrowserInfoDlg::BROWSER_SAFARI);
	ui.stkApp->addWidget(m_safariBrowser);
	m_appMap[L"Safari浏览器"] = i++;
	connect(ui.edtFilter, SIGNAL(textChanged(QString)), m_safariBrowser, SLOT(OnEdtFilterTextChanged(QString)));

	m_baiduMapInfo = new MapInfoDlg(this, MapInfoDlg::MAP_BAIDU);
	ui.stkApp->addWidget(m_baiduMapInfo);
	m_appMap[L"百度地图"] = i++;
	connect(ui.edtFilter, SIGNAL(textChanged(QString)), m_baiduMapInfo, SLOT(OnEdtFilterTextChanged(QString)));

	m_gaodeMapInfo = new MapInfoDlg(this, MapInfoDlg::MAP_GAODE);
	ui.stkApp->addWidget(m_gaodeMapInfo);
	m_appMap[L"高德地图"] = i++;
	connect(ui.edtFilter, SIGNAL(textChanged(QString)), m_gaodeMapInfo, SLOT(OnEdtFilterTextChanged(QString)));

	m_emulator = new EmulatorDlg(this);
	ui.stkApp->addWidget(m_emulator);
	m_appMap[L"模拟仿真"] = i++;

	m_analyzeImage = new AnalyzeImageDlg(this);
	ui.stkApp->addWidget(m_analyzeImage);
	m_appMap[L"镜像分析"] = i++;

	ui.lstNav->setCurrentIndex(ui.lstNav->model()->index(0, 0));
	OnListViewClicked(ui.lstNav->model()->index(0, 0));

}

void AppDlg::InitConnection()
{
	connect(ui.lstNav, SIGNAL(clicked(const QModelIndex &)), this, SLOT(OnListViewClicked(const QModelIndex &)));
	connect(m_save, SIGNAL(finished()), this, SLOT(SaveDataFinished()));
}

void AppDlg::InitDragAndDrop()
{
	setAcceptDrops(true);
}

void AppDlg::InitAction()
{
	QAction* selectDataDir = new QAction(Utils::wtoq(L"选择案例目录"), this);
	QAction* saveData = new QAction(Utils::wtoq(L"保存存档"), this);
	QAction* help = new QAction(Utils::wtoq(L"使用帮助"), this);
	QAction* about = new QAction(Utils::wtoq(L"关于"), this);

	connect(selectDataDir, SIGNAL(triggered()), this, SLOT(SelectDataDir()));
	connect(saveData, SIGNAL(triggered()), this, SLOT(SaveData()));

	emit AddMenuAction(selectDataDir);
	//emit AddMenuAction(saveData);
	//emit AddMenuAction(help);
	//emit AddMenuAction(about);
}

void AppDlg::OnListViewClicked(const QModelIndex &index)
{
	std::wstring app = Utils::qtow(index.data(Qt::DisplayRole).toString());

	if ( m_appMap.find(app) == m_appMap.end() )
		return;

	if ( SearchBarCanShow(app) )
		ui.frame_header_bar->show();
	else
		ui.frame_header_bar->hide();

	ui.stkApp->setCurrentIndex(m_appMap[app]);
}

bool AppDlg::SearchBarCanShow(const std::wstring& content)
{
	if ( content == L"基本信息"
	  || content == L"模拟仿真"
	  || content == L"镜像分析"
	  || content == L"已删除短信" 
	  || content == L"已删除通讯录" 
	  || content == L"已删除通话记录" )
		return false;

	return true;
}

void AppDlg::SelectDataDir()
{
	if ( QDialog::Accepted == SelectDirDlg::Invoke() )
	{
		QString key = Utils::wtoq(DataManager::GetInstance().GetCurrentForensicsDir());
		SetCurrentDevice(key, true);
		UpdateCase();
	}
	else
		UpdateCase();
}

void AppDlg::SaveData()
{
	m_save->start();
	m_wait->SetSize(this->size());
	m_wait->show();
}

void AppDlg::SaveDataFinished()
{
	m_wait->hide();
	MsgBox::Information(0, Utils::stoq("提示"), Utils::stoq("成功保存存档"));
}

void AppDlg::UpdateCase()
{
	DataManager& dm = DataManager::GetInstance();
	const std::list<CASE_INFO>& cases = dm.GetCaseList();

	if ( NULL == m_deviceMenu )
		m_deviceMenu = new QMenu(Utils::stoq("设备列表"), this);

	emit RemoveMenuAction(m_deviceMenu->menuAction());

	m_deviceMenu->clear();

	if ( cases.empty() )
		return;

	for ( std::list<CASE_INFO>::const_iterator it = cases.begin();
		  it != cases.end();
		  ++it )
	{
		std::wstring device = (*it).wzDirPath;

		DeviceDataDirMap& dirs = dm.GetDeviceDataDirMap();
		ForensicsTypeMap& types = dm.GetForensicsTypeMap();

		int count = dirs.count(device);
		DeviceDataDirMap::iterator im = dirs.find(device);

		for ( int i = 0; i < count; ++i, ++im )
		{
			std::wstring path = (*im).second;
			std::wstring name = types[path].name;

			QAction* action = new QAction(Utils::wtoq(device + L" ( " + name + L" )"), this);
			action->setData(Utils::wtoq(device + path));
			connect(action, SIGNAL(triggered()), this, SLOT(CurrentDeviceChanged()));
			m_deviceMenu->addAction(action);
		}

		m_deviceMenu->addSeparator();
	}

	emit AddSubMenu(m_deviceMenu);
}

void AppDlg::CurrentDeviceChanged()
{
	QString key = ( qobject_cast<QAction*>(sender()) )->data().toString();
	SetCurrentDevice(key);
}

void AppDlg::OnBtnCollapseNavBarClicked()
{
	ui.lstNav->setVisible(!ui.lstNav->isVisible());
}

void AppDlg::SetCurrentDevice(QString key, bool clear)
{
	QString device = key.section('\\', 0, 0);
	QString dir = key.section('\\', 1, 1, QString::SectionIncludeLeadingSep);

	ForensicsTypeMap& nameMap = (DataManager::GetInstance().GetForensicsTypeMap());
	std::wstring forensicsName = nameMap[Utils::qtow(dir)].name;

	emit SetSubTitle(device + " ( " + Utils::wtoq(forensicsName) + " )");
	DataManager::GetInstance().SetCurrentDevice(Utils::qtow(device));
	DataManager::GetInstance().SetCurrentForensicsDir(Utils::qtow(dir));

	m_navDelegate->SetPending(true);
	ParseDlg::Invoke(Utils::qtow(key), clear);
	m_navDelegate->SetPending(false);

	DWORD cost = GetTickCount();

	m_basicInfo->Update();
	m_sms->Update();
	m_contactInfo->Update();
	m_call->Update();

	m_smsDel->Update();
	m_contactDel->Update();
	m_callDel->Update();

	m_emulator->Update();

	m_qq->Update();
	m_weixin->Update();
	m_line->Update();
	m_analyzeImage->Update();

	m_defaultBrowser->Update();
	m_ucBrowser->Update();
	m_qqBrowser->Update();
	m_baiduBrowser->Update();
	m_jinshanBrowser->Update();
	m_safariBrowser->Update();

	m_baiduMapInfo->Update();
	m_gaodeMapInfo->Update();

	m_keyChain->Update();

	cost = GetTickCount()-cost;

	Utils::__TRACE(L"[Time Cost] Data Update : %d ms\r\n", cost);

	m_navModel->Refresh();
}

void AppDlg::dragMoveEvent(QDragMoveEvent *e)
{
	e->acceptProposedAction();
}

void AppDlg::dragEnterEvent(QDragEnterEvent* e)
{
	e->acceptProposedAction();
}

bool AppDlg::eventFilter(QObject *obj, QEvent *event)
{
	if ( event->type() == QEvent::Resize 
		|| event->type() == QEvent::Show 
		|| event->type() == QEvent::Hide )
	{
		UpdateBtnCollapseNavBar();
		return true;
	}
	else
	{
		return QObject::eventFilter(obj, event);
	}
}

void AppDlg::UpdateBtnCollapseNavBar()
{
	m_btnCollapseNavBar->resize(13, this->height()-100);

	if ( ui.lstNav->isVisible() )
	{
		m_btnCollapseNavBar->move(ui.lstNav->width(), 0);
		m_btnCollapseNavBar->setStyleSheet(
			"QPushButton{image:none;border-width:0px;background-color:transparent;}"
			"QPushButton:hover{image:url(:/Image/splliteLeft.png);border-width:0px;background-color:transparent;}");
	}
	else
	{
		m_btnCollapseNavBar->move(0, 0);
		m_btnCollapseNavBar->setStyleSheet(
			"QPushButton{image:none;border-width:0px;background-color:transparent;}"
			"QPushButton:hover{image:url(:/Image/splliteRight.png);border-width:0px;background-color:transparent;}");
	}
}

void AppDlg::dropEvent(QDropEvent *e)
{
	const QMimeData *mimeData = e->mimeData();
	QList<QUrl> url = mimeData->urls();

	if ( url.count() == 0 )
		return;

	QString dir =  url[0].toLocalFile();

	QFileInfo info(dir);

	if ( !info.isDir() )
		return;

	dir = dir.replace("/", "\\");
	AnalyzeDir(dir);
}

void AppDlg::AnalyzeDir( QString dir )
{
	if ( QDialog::Accepted == SelectDirDlg::Invoke( dir ) )
	{
		QString key = Utils::wtoq(DataManager::GetInstance().GetCurrentForensicsDir());
		SetCurrentDevice(key, true);
		UpdateCase();
	}
	else
		UpdateCase();
}
