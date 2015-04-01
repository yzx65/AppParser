#include "StdAfx.h"
#include "weixininfodlg.h"
#include "utils.h"
#include "nofocusstyle.h"
#include "datamanager.h"

#include <QtGui>

WeixinInfoDlg::WeixinInfoDlg(QWidget *parent)
	: QFrame(parent)
{
	ui.setupUi(this);

	NoFocusStyle* style = new NoFocusStyle(this);
	ui.cmbWeixinFriends->setStyle(style);
	QStyledItemDelegate* itemDelegate = new QStyledItemDelegate();
	ui.cmbWeixinFriends->setItemDelegate(itemDelegate);
	Utils::InitStyle(this);

	ui.btnBack->hide();
	ui.btnFront->hide();

	m_filter = new QSortFilterProxyModel(this);
	m_model = new QStandardItemModel(this);
	m_filter->setSourceModel(m_model);
	ui.lstWeixinFriends->setModel(m_filter);

	InitConnections();
}

WeixinInfoDlg::~WeixinInfoDlg()
{

}

void WeixinInfoDlg::InitConnections()
{
	connect(ui.btnBack, SIGNAL(clicked()), ui.edtWeixinChat, SLOT(Back()));
	connect(ui.btnFront, SIGNAL(clicked()), ui.edtWeixinChat, SLOT(Front()));

	connect(ui.edtWeixinChat, SIGNAL(FrontShow()), this, SLOT(FrontShow()));
	connect(ui.edtWeixinChat, SIGNAL(BackShow()), this, SLOT(BackShow()));
	connect(ui.edtWeixinChat, SIGNAL(FrontHide()), this, SLOT(FrontHide()));
	connect(ui.edtWeixinChat, SIGNAL(BackHide()), this, SLOT(BackHide()));

	connect(ui.cmbWeixinFriends, SIGNAL(currentIndexChanged(int)), this, SLOT(OnCurrentAccountChanged(int)));
	connect(ui.lstWeixinFriends, SIGNAL(clicked(const QModelIndex&)), this, SLOT(OnLstWeixinFriendsClicked(const QModelIndex&)));
}

void WeixinInfoDlg::FrontShow()
{
	ui.btnFront->show();
}

void WeixinInfoDlg::BackShow()
{
	ui.btnBack->show();
}

void WeixinInfoDlg::FrontHide()
{
	ui.btnFront->hide();
}

void WeixinInfoDlg::BackHide()
{
	ui.btnBack->hide();
}

void WeixinInfoDlg::Update()
{
	ui.cmbWeixinFriends->clear();
	ui.edtWeixinChat->ClearText();
	DataManager& dm = DataManager::GetInstance();
	AccountInfoMap* accounts = dm.GetWeixinInfoMap(dm.GetCurrentForensicsDir());

	if ( NULL == accounts )
		return;

	for ( AccountInfoMap::iterator it = accounts->begin();
		it != accounts->end();
		++it )
	{
		ui.cmbWeixinFriends->addItem(Utils::stoq((*it).first));
	}

	OnCurrentAccountChanged(0);
}

void WeixinInfoDlg::OnCurrentAccountChanged( int index )
{
	m_model->clear();

	if ( ui.cmbWeixinFriends->currentText().isEmpty() )
		return;

	std::string account = Utils::qtos(ui.cmbWeixinFriends->currentText());

	DataManager& dm = DataManager::GetInstance();
	AccountInfoMap* accountMap = dm.GetWeixinInfoMap(dm.GetCurrentForensicsDir());

	if ( NULL == accountMap )
		return;

	AccountInfo& accountInfo = (*accountMap)[account];

	AddWeixinFriends(accountInfo);
}

void WeixinInfoDlg::AddWeixinFriends(AccountInfo& accountInfo)
{
	for ( std::map<std::string, FriendInfo>::iterator it = accountInfo.friends.begin();
		it != accountInfo.friends.end();
		++it)
	{
		QStandardItem* item;

		item = new QStandardItem(Utils::utoq((*it).second.nickName + "(" + (*it).second.account + ")"));

		item->setData(Utils::utoq((*it).second.account), Qt::UserRole);

		if ( accountInfo.chatMap.find((*it).second.account) != accountInfo.chatMap.end() )
			item->setData(QBrush(QColor(255, 100, 100)), Qt::ForegroundRole);

		m_model->appendRow(item);
	}
}

void WeixinInfoDlg::OnLstWeixinFriendsClicked( const QModelIndex& index )
{
	ui.edtWeixinChat->ClearText();

	std::string account = Utils::qtos(ui.cmbWeixinFriends->currentText());

	DataManager& dm = DataManager::GetInstance();
	AccountInfoMap* accountMap = dm.GetWeixinInfoMap(dm.GetCurrentForensicsDir());

	if ( NULL == accountMap )
		return;

	AccountInfo& accountInfo = (*accountMap)[account];

	std::string friendAccount = Utils::qtos(index.data(Qt::UserRole).toString());

	if ( account.empty() )
		return;

	if ( accountInfo.chatMap.end() == accountInfo.chatMap.find(friendAccount) )
		return;

	ChatHistoryList& history = accountInfo.chatMap[friendAccount];

	for ( ChatHistoryList::iterator it = history.begin(); it != history.end(); ++it )
	{
		QString message = Utils::utoq(it->message);

		if ( message.startsWith("<msg>") )
			continue;

		ui.edtWeixinChat->AddChatText(
			Utils::utoq(it->senderName.empty() ? it->senderUin : it->senderName), 
			Utils::utoq(it->time), 
			message);
	}

	ui.edtWeixinChat->UpdateTextBrowser();
}

void WeixinInfoDlg::OnEdtFilterTextChanged(QString key)
{
	QRegExp reg(key, Qt::CaseInsensitive, QRegExp::FixedString);
	m_filter->setFilterRegExp(reg);
}

