#include "StdAfx.h"
#include "callinfodlg.h"
#include "utils.h"
#include "datamanager.h"

CallInfoDlg::CallInfoDlg(QWidget *parent)
	: QFrame(parent)
{
	ui.setupUi(this);
	Utils::InitStyle(this);

	ui.tbCallInfo->header()->resizeSection(0, 200);
	ui.tbCallInfo->header()->resizeSection(1, 120);
	ui.tbCallInfo->header()->resizeSection(2, 100);

	InitListView();
	InitConnection();
}

CallInfoDlg::~CallInfoDlg()
{

}

void CallInfoDlg::InitListView()
{
	m_filter = new QSortFilterProxyModel(this);
	m_model = new QStandardItemModel(this);
	m_filter->setSourceModel(m_model);
	ui.lstCallFriends->setModel(m_filter);
}

void CallInfoDlg::InitConnection()
{
	connect(ui.lstCallFriends, SIGNAL(clicked(const QModelIndex&)), this, SLOT(OnLstCallFriendsClicked(const QModelIndex&)));
}

void CallInfoDlg::Update()
{
	ui.tbCallInfo->clear();
	m_model->clear();

	DataManager& dm = DataManager::GetInstance();
	RECORD_InfoMap* records = dm.GetRecordInfoList(dm.GetCurrentForensicsDir());

	if ( NULL == records )
		return;

	for ( RECORD_InfoMap::iterator it = records->begin();
		  it != records->end();
		  it = records->upper_bound(it->first) )
	{
		QStandardItem* item;

		if ( !(*it).second.name.empty() )
			item = new QStandardItem(Utils::wtoq((*it).second.name + L" " + (*it).first));
		else
			item = new QStandardItem(Utils::wtoq((*it).first));

		item->setData(Utils::wtoq((*it).first), Qt::UserRole);
		m_model->appendRow(item);
	}
}

void CallInfoDlg::OnLstCallFriendsClicked( const QModelIndex& index )
{
	ui.tbCallInfo->clear();
	DataManager& dm = DataManager::GetInstance();
	RECORD_InfoMap* records = dm.GetRecordInfoList(dm.GetCurrentForensicsDir());
	
	if ( NULL == records )
		return;

	std::wstring key = Utils::qtow(index.data(Qt::UserRole).toString());

	int count = records->count(key);
	RECORD_InfoMap::iterator it = records->find(key);

	for ( int i = 0; i < count; ++it, ++i )
	{
		QTreeWidgetItem* item = new QTreeWidgetItem;
		item->setText(0, Utils::wtoq(it->second.date));
		item->setText(1, Utils::wtoq(it->second.time + L" Ãë"));
		item->setText(2, Utils::wtoq(it->second.type));
		item->setText(3, Utils::wtoq(it->second.location));

		ui.tbCallInfo->addTopLevelItem(item);
	}
}

void CallInfoDlg::OnEdtFilterTextChanged(QString key)
{
	QRegExp reg(key, Qt::CaseInsensitive, QRegExp::FixedString);
	m_filter->setFilterRegExp(reg);
}
