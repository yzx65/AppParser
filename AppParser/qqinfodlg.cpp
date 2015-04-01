#include "StdAfx.h"
#include "qqinfodlg.h"
#include "utils.h"
#include "nofocusstyle.h"
#include "datamanager.h"

bool ChildrenFilter::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
	// custom behaviour :
	if(filterRegExp().isEmpty()==false)
	{
		// get source-model index for current row
		QModelIndex source_index = sourceModel()->index(source_row, this->filterKeyColumn(), source_parent) ;
		if(source_index.isValid())
		{
			// if any of children matches the filter, then current index matches the filter as well
			int i, nb = sourceModel()->rowCount(source_index) ;
			for(i=0; i<nb; ++i)
			{
				if(filterAcceptsRow(i, source_index))
				{
					return true ;
				}
			}
			// check current index itself :
			QString key = sourceModel()->data(source_index, filterRole()).toString();
			return key.contains(filterRegExp()) ;
		}
	}
	// parent call for initial behaviour
	return QSortFilterProxyModel::filterAcceptsRow(source_row, source_parent) ;
}

QQInfoDlg::QQInfoDlg(QWidget *parent)
	: QFrame(parent)
{
	ui.setupUi(this);

	QStyledItemDelegate* itemDelegate = new QStyledItemDelegate();
	ui.cmbQQAccount->setItemDelegate(itemDelegate);
	NoFocusStyle* style = new NoFocusStyle(this);
	ui.cmbQQAccount->setStyle(style);
	Utils::InitStyle(this);

	ui.btnBack->hide();
	ui.btnFront->hide();

	m_filter = new ChildrenFilter(this);
	m_model = new QStandardItemModel(this);
	m_filter->setSourceModel(m_model);
	ui.trQQAccounts->setModel(m_filter);

	InitConnections();
}

QQInfoDlg::~QQInfoDlg()
{

}

void QQInfoDlg::InitConnections()
{
	connect(ui.btnBack, SIGNAL(clicked()), ui.edtQQChat, SLOT(Back()));
	connect(ui.btnFront, SIGNAL(clicked()), ui.edtQQChat, SLOT(Front()));

	connect(ui.edtQQChat, SIGNAL(FrontShow()), this, SLOT(FrontShow()));
	connect(ui.edtQQChat, SIGNAL(BackShow()), this, SLOT(BackShow()));
	connect(ui.edtQQChat, SIGNAL(FrontHide()), this, SLOT(FrontHide()));
	connect(ui.edtQQChat, SIGNAL(BackHide()), this, SLOT(BackHide()));

	connect(ui.cmbQQAccount, SIGNAL(currentIndexChanged(int)), this, SLOT(OnCurrentAccountChanged(int)));
	connect(ui.trQQAccounts, SIGNAL(clicked(const QModelIndex&)), this, SLOT(OnTrQQAccountsClicked(const QModelIndex&)));
}

void QQInfoDlg::FrontShow()
{
	ui.btnFront->show();
}

void QQInfoDlg::BackShow()
{
	ui.btnBack->show();
}

void QQInfoDlg::FrontHide()
{
	ui.btnFront->hide();
}

void QQInfoDlg::BackHide()
{
	ui.btnBack->hide();
}

void QQInfoDlg::Update()
{
	ui.cmbQQAccount->clear();
	ui.edtQQChat->ClearText();

	ui.label_qq_number->setText("");
	ui.label_qq_nickname->setText("");
	ui.label_qq_remark->setText("");
	ui.label_qq_group->setText("");
	ui.label_qq_signature->setText("");

	DataManager& dm = DataManager::GetInstance();
	AccountInfoMap* accounts = dm.GetQQInfoMap(dm.GetCurrentForensicsDir());

	if ( NULL == accounts )
		return;

	for ( AccountInfoMap::iterator it = accounts->begin();
		  it != accounts->end();
		  ++it )
	{
		ui.cmbQQAccount->addItem(Utils::stoq((*it).first));
	}

	OnCurrentAccountChanged(0);
}

void QQInfoDlg::OnCurrentAccountChanged( int index )
{
	m_model->clear();

	if ( ui.cmbQQAccount->currentText().isEmpty() )
		return;

	std::string account = Utils::qtos(ui.cmbQQAccount->currentText());

	DataManager& dm = DataManager::GetInstance();
	AccountInfoMap* accountMap = dm.GetQQInfoMap(dm.GetCurrentForensicsDir());

	if ( NULL == accountMap )
		return;

	AccountInfo& accountInfo = (*accountMap)[account];
	
	AddQQFriends(accountInfo);
	AddQQTroops(accountInfo);
	AddQQDiscusses(accountInfo);
}

QStandardItem* QQInfoDlg::FindParent(std::string& groupName)
{
	QString parentName = groupName.empty() ? Utils::stoq("默认好友列表") : Utils::utoq(groupName);

	QStandardItem* parent = NULL;

	QList<QStandardItem*> items = m_model->findItems(parentName);

	if ( 0 == items.count() )
	{
		parent = new QStandardItem(parentName);
		m_model->appendRow(parent);
	}
	else
	{
		parent = items[0];
	}

	return parent;
}

void QQInfoDlg::AddQQFriends(AccountInfo& accountInfo)
{
	int i = 0;

	for ( std::map<std::string, FriendInfo>::iterator it = accountInfo.friends.begin();
		it != accountInfo.friends.end();
		++it, ++i )
	{
		QStandardItem* item;

		if ( (*it).second.remark.empty() )
			item = new QStandardItem(Utils::utoq((*it).second.nickName + "(" + (*it).second.account + ")"));
		else
			item = new QStandardItem(Utils::utoq((*it).second.remark + "(" + (*it).second.account + ")"));

		if ( !(*it).second.signature.empty() )
			item->setData(Utils::utoq((*it).second.signature), Qt::ToolTipRole);

		if ( accountInfo.chatMap.find((*it).second.account) != accountInfo.chatMap.end() )
			item->setData(QBrush(QColor(255, 100, 100)), Qt::ForegroundRole);

		qDebug() << QString::fromUtf8((*it).second.groupName.c_str());

		item->setData(Utils::utoq((*it).second.account), Qt::UserRole);

		QStandardItem* group = FindParent((*it).second.groupName);

		group->setChild(group->rowCount(), item);
	}
}

void QQInfoDlg::AddQQTroops(AccountInfo& accountInfo)
{
	QStandardItem* group = new QStandardItem(Utils::stoq("群列表"));
	m_model->appendRow(group);

	int i = 0;

	for ( std::list<TroopInfo>::iterator it = accountInfo.troops.begin();
		it != accountInfo.troops.end();
		++it, ++i )
	{
		QStandardItem* item;

		item = new QStandardItem(Utils::utoq(it->troopName + "(" + it->troopUin + ")"));

		if ( !it->troopMemo.empty() )
			item->setData(Utils::utoq(it->troopMemo), Qt::ToolTipRole);

		if ( accountInfo.chatMap.find(it->troopUin) != accountInfo.chatMap.end() )
			item->setData(QBrush(QColor(255, 100, 100)), Qt::ForegroundRole);

		item->setData(Utils::utoq(it->troopUin), Qt::UserRole);

		group->setChild(i, item);
	}
}

void QQInfoDlg::AddQQDiscusses(AccountInfo& accountInfo)
{
	QStandardItem* group = new QStandardItem(Utils::stoq("讨论组列表"));
	m_model->appendRow(group);

	int i = 0;

	for ( std::list<DiscInfo>::iterator it = accountInfo.discusses.begin();
		it != accountInfo.discusses.end();
		++it, ++i )
	{
		QStandardItem* item;

		item = new QStandardItem(Utils::utoq(it->discussName + "(" + it->discussUin + ")"));

		item->setData(Utils::utoq(it->discussUin), Qt::UserRole);

		group->setChild(i, item);
	}
}

void QQInfoDlg::OnTrQQAccountsClicked( const QModelIndex& index )
{
	ui.edtQQChat->ClearText();

	std::string account = Utils::qtos(ui.cmbQQAccount->currentText());

	if ( account.empty() )
		return;

	DataManager& dm = DataManager::GetInstance();
	AccountInfoMap* accountMap = dm.GetQQInfoMap(dm.GetCurrentForensicsDir());

	if ( NULL == accountMap )
		return;

	AccountInfo& accountInfo = (*accountMap)[account];

	std::string friendAccount = Utils::qtos(index.data(Qt::UserRole).toString());

	std::map<std::string, FriendInfo>::iterator it = accountInfo.friends.find(friendAccount);

	if ( it != accountInfo.friends.end() )
	{
		ui.frame_accountInfo->show();
		ui.label_qq_number->setText(Utils::utoq((*it).second.account));
		ui.label_qq_nickname->setText(Utils::utoq((*it).second.nickName));
		ui.label_qq_remark->setText(Utils::utoq((*it).second.remark));
		ui.label_qq_group->setText(Utils::utoq((*it).second.groupName));
		ui.label_qq_signature->setText(Utils::utoq((*it).second.signature));
	}
	else
	{
		ui.frame_accountInfo->hide();
	}

	if ( accountInfo.chatMap.end() == accountInfo.chatMap.find(friendAccount) )
		return;

	ChatHistoryList& history = accountInfo.chatMap[friendAccount];

	for ( ChatHistoryList::iterator it = history.begin(); it != history.end(); ++it )
	{
		//it->msgType
		ui.edtQQChat->AddChatText(
			Utils::utoq(it->senderName.empty() ? it->senderUin : it->senderName +"(" + it->senderUin + ")"), 
			Utils::utoq(it->time), 
			Utils::utoq(it->message));
	}

	ui.edtQQChat->UpdateTextBrowser();
}

void QQInfoDlg::OnEdtFilterTextChanged(QString key)
{
	QRegExp reg(key, Qt::CaseInsensitive, QRegExp::FixedString);
	m_filter->setFilterRegExp(reg);
}
