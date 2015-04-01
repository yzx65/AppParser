#include "StdAfx.h"
#include "keychaininfodlg.h"
#include "utils.h"

#include "datamanager.h"

KeyChainInfoDlg::KeyChainInfoDlg(QWidget *parent)
	: QFrame(parent)
{
	ui.setupUi(this);

	Utils::InitStyle(this);

	ui.tbPassword->header()->resizeSection(0, 250);

	InitListView();
	InitConnections();

	ui.tbPassword->hideColumn(0);
}

KeyChainInfoDlg::~KeyChainInfoDlg()
{

}

void KeyChainInfoDlg::InitListView()
{
	m_filter = new QSortFilterProxyModel(this);
	m_model = new QStandardItemModel(this);
	m_filter->setSourceModel(m_model);
	ui.lstService->setModel(m_filter);
}

void KeyChainInfoDlg::InitConnections()
{
	connect(ui.lstService, SIGNAL(clicked(const QModelIndex&)), this, SLOT(OnLstServiceClicked(const QModelIndex&)));
}

void KeyChainInfoDlg::Update()
{
	m_model->clear();
	DataManager& dm = DataManager::GetInstance();
	KeyChainInfoMap* keychains = dm.GetKeyChainInfoMap(dm.GetCurrentForensicsDir());

	if ( NULL == keychains )
		return;

	for ( KeyChainInfoMap::iterator it = keychains->begin();
		  it != keychains->end();
		  it = keychains->upper_bound((*it).first) )
	{
		if ( (*it).first.empty() )
			continue;

		QStandardItem* item = NULL;

		Utils::__TRACE("[KeyChain] %s\r\n", (*it).second.serviceName.c_str());

		if ( ! ((*it).second.serviceName.empty()) )
			item = new QStandardItem(Utils::stoq((*it).second.serviceName));
		else
			item = new QStandardItem(Utils::stoq((*it).first));

		item->setData(Utils::stoq((*it).first), Qt::UserRole);
		m_model->appendRow(item);
	}
}

void KeyChainInfoDlg::OnLstServiceClicked( const QModelIndex& index)
{
	ui.tbPassword->clear();
	DataManager& dm = DataManager::GetInstance();
	KeyChainInfoMap* keychains = dm.GetKeyChainInfoMap(dm.GetCurrentForensicsDir());

	if ( NULL == keychains )
		return;

	std::string key = Utils::qtos(index.data(Qt::UserRole).toString());

	if ( key == "ÆäËû" )
		ui.tbPassword->showColumn(0);
	else
		ui.tbPassword->hideColumn(0);

	int count = keychains->count(key);
	KeyChainInfoMap::iterator it = keychains->find(key);

	for ( int i = 0; i < count; ++i, ++it )
	{
		QTreeWidgetItem* item = new QTreeWidgetItem;
		item->setText(0, Utils::stoq((*it).second.prefix));
		item->setText(1, Utils::stoq((*it).second.name));
		item->setText(2, Utils::stoq((*it).second.password));

		ui.tbPassword->addTopLevelItem(item);
	}
}

void KeyChainInfoDlg::OnEdtFilterTextChanged( QString key )
{
	QRegExp reg(key, Qt::CaseInsensitive, QRegExp::FixedString);
	m_filter->setFilterRegExp(reg);
}
