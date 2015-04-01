#include "StdAfx.h"
#include "smsinfodlg.h"
#include "chatcontainer.h"
#include "utils.h"
#include "datamanager.h"

SmsInfoDlg::SmsInfoDlg(QWidget *parent)
	: QFrame(parent)
{
	ui.setupUi(this);
	Utils::InitStyle(this);

	ui.btnBack->hide();
	ui.btnFront->hide();

	InitListView();
	InitConnections();
}

SmsInfoDlg::~SmsInfoDlg()
{

}

void SmsInfoDlg::InitConnections()
{
	connect(ui.btnBack, SIGNAL(clicked()), ui.edtSmsRecord, SLOT(Back()));
	connect(ui.btnFront, SIGNAL(clicked()), ui.edtSmsRecord, SLOT(Front()));

	connect(ui.edtSmsRecord, SIGNAL(FrontShow()), this, SLOT(FrontShow()));
	connect(ui.edtSmsRecord, SIGNAL(BackShow()), this, SLOT(BackShow()));
	connect(ui.edtSmsRecord, SIGNAL(FrontHide()), this, SLOT(FrontHide()));
	connect(ui.edtSmsRecord, SIGNAL(BackHide()), this, SLOT(BackHide()));

	connect(ui.lstSmsFriends, SIGNAL(clicked(const QModelIndex&)), this, SLOT(OnLstSmsFriendsClicked(const QModelIndex&)));
}

void SmsInfoDlg::InitListView()
{
	m_filter = new QSortFilterProxyModel(this);
	m_model = new QStandardItemModel(this);
	m_filter->setSourceModel(m_model);
	ui.lstSmsFriends->setModel(m_filter);
}

void SmsInfoDlg::FrontShow()
{
	ui.btnFront->show();
}

void SmsInfoDlg::BackShow()
{
	ui.btnBack->show();
}

void SmsInfoDlg::FrontHide()
{
	ui.btnFront->hide();
}

void SmsInfoDlg::BackHide()
{
	ui.btnBack->hide();
}

void SmsInfoDlg::Update()
{
	ui.edtSmsRecord->ClearText();
	m_model->clear();

	DataManager& dm = DataManager::GetInstance();
	SMS_InfoMap* sms = dm.GetSmsInfoMap(dm.GetCurrentForensicsDir());

	if ( NULL == sms )
		return;

	for ( SMS_InfoMap::iterator it = sms->begin();
		  it != sms->end();
		  it = sms->upper_bound(it->first) )
	{
		//Utils::__TRACE(L"number : %s name : %s\n", (*it).first.c_str(), (*it).second.name.c_str());

		QStandardItem* item;

		if ( !(*it).second.name.empty() )
			item = new QStandardItem(Utils::wtoq((*it).second.name + L" " + (*it).first));
		else
			item = new QStandardItem(Utils::wtoq((*it).first));

		item->setData(Utils::wtoq((*it).first), Qt::UserRole);
		m_model->appendRow(item);
	}
}

void SmsInfoDlg::OnLstSmsFriendsClicked( const QModelIndex& index )
{
	QString number = index.data(Qt::UserRole).toString();

	DataManager& dm = DataManager::GetInstance();
	SMS_InfoMap* sms = dm.GetSmsInfoMap(dm.GetCurrentForensicsDir());

	if ( NULL == sms )
		return;

	std::wstring smsNumber = Utils::qtow(number);
	SMS_InfoMap::iterator it = sms->find(smsNumber);
	int count = sms->count(smsNumber);

	ui.edtSmsRecord->ClearText();

	for ( int i = 0 ; i < count; ++i, ++it )
	{
		Utils::__TRACE(L"Number %s, Message : %s, Time : %s\r\n", 
			(*it).first.c_str(), (*it).second.message.c_str(), (*it).second.time.c_str());

		if ( (*it).second.isSend )
			ui.edtSmsRecord->AddChatText(
				Utils::stoq("½ÓÊÕ"), Utils::wtoq((*it).second.time), Utils::wtoq((*it).second.message));
		else
			ui.edtSmsRecord->AddChatText(
				Utils::stoq("·¢ËÍ"), Utils::wtoq((*it).second.time), Utils::wtoq((*it).second.message));
	}

	ui.edtSmsRecord->UpdateTextBrowser();
}

void SmsInfoDlg::OnEdtFilterTextChanged(QString key)
{
	QRegExp reg(key, Qt::CaseInsensitive, QRegExp::FixedString);
	m_filter->setFilterRegExp(reg);
}