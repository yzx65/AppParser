#include "StdAfx.h"
#include "BrowserInfoDlg.h"
#include "utils.h"
#include "datamanager.h"
#include "historydelegate.h"

typedef const HistoryList* (DataManager::*GetHistoryMethod)(std::wstring key);
typedef const BookmarkList* (DataManager::*GetBookmarkMethod)(std::wstring key);

struct GetBrowserInfoMethod
{
	GetHistoryMethod historyMethod;
	GetBookmarkMethod bookmarkMethod;
};

GetBrowserInfoMethod BrowserDict[] = 
{
	{
		&DataManager::GetUCBrowserHistoryList,
		&DataManager::GetUCBrowserBookmarkList
	},
	{
		&DataManager::GetDefaultBrowserHistoryList,
		&DataManager::GetDefaultBrowserBookmarkList
	},
	{
		&DataManager::GetQQBrowserHistoryList,
		&DataManager::GetQQBrowserBookmarkList
	},
	{
		&DataManager::GetBaiduBrowserHistoryList,
		&DataManager::GetBaiduBrowserBookmarkList
	},
	{
		&DataManager::GetJinShanBrowserHistoryList,
		&DataManager::GetJinShanBrowserBookmarkList
	},
	{
		&DataManager::GetSafariBrowserHistoryList,
		&DataManager::GetSafariBrowserBookmarkList
	}
};

BrowserInfoDlg::BrowserInfoDlg(QWidget *parent, BrowserType type)
	: QFrame(parent)
	, m_type(type)
{
	ui.setupUi(this);
	Utils::InitStyle(this);

	m_filter = new QSortFilterProxyModel(this);
	m_model = new QStandardItemModel(this);
	m_filter->setSourceModel(m_model);
	ui.lstBrowserData->setModel(m_filter);
	ui.lstBrowserData->setItemDelegate(new HistoryDelegate(this));
	
	InitConnections();
}

BrowserInfoDlg::~BrowserInfoDlg()
{

}

void BrowserInfoDlg::InitConnections()
{
	connect(ui.btnHistory, SIGNAL(clicked()), this, SLOT(CurrentDisplayChanged()));
	connect(ui.btnBookmark, SIGNAL(clicked()), this, SLOT(CurrentDisplayChanged()));
	connect(ui.lstBrowserData, SIGNAL(clicked(const QModelIndex&)), this, SLOT(OnLstBrowserDataClicked(const QModelIndex&)));
}

void BrowserInfoDlg::Update()
{
	m_model->clear();
	
	DataManager& dm = DataManager::GetInstance();
	std::wstring key = dm.GetCurrentForensicsDir();

	GetBrowserInfoMethod browserMethod = BrowserDict[m_type];

	const HistoryList* historys = ui.btnHistory->isChecked() ? (dm.*browserMethod.historyMethod)(key) : (dm.*browserMethod.bookmarkMethod)(key);

	if ( NULL == historys )
		return;

	for ( HistoryList::const_iterator it = historys->begin();
		  it != historys->end();
		  ++it )
	{
		QStandardItem* item = new QStandardItem(Utils::utoq(it->name + "\n" + it->url + "\n" + it->time));
		item->setData(Utils::utoq(it->url), Qt::UserRole);
		m_model->appendRow(item);
	}
}

void BrowserInfoDlg::CurrentDisplayChanged()
{
	Update();
}


void BrowserInfoDlg::OnLstBrowserDataClicked(const QModelIndex& index)
{
	ShellExecuteW(NULL, L"open", Utils::qtow(index.data(Qt::UserRole).toString()).c_str(), NULL, NULL, SW_SHOW);
}

void BrowserInfoDlg::OnEdtFilterTextChanged(QString key)
{
	QRegExp reg(key, Qt::CaseInsensitive, QRegExp::FixedString);
	m_filter->setFilterRegExp(reg);
}