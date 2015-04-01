#include "StdAfx.h"
#include "mapinfodlg.h"

#include "utils.h"
#include "datamanager.h"

#include "historydelegate.h"

typedef const MapsList* (DataManager::*GetMapListMethod)(std::wstring key);

const GetMapListMethod MapInfoDict[] = 
{
	&DataManager::GetBaiduMapList,
	&DataManager::GetGaodeMapList
};

MapInfoDlg::MapInfoDlg(QWidget *parent, MapType type)
	: QFrame(parent)
	, m_type(type)
{
	ui.setupUi(this);

	Utils::InitStyle(this);

	m_filter = new QSortFilterProxyModel(this);
	m_model = new QStandardItemModel(this);
	m_filter->setSourceModel(m_model);
	ui.lstMapData->setModel(m_filter);
	ui.lstMapData->setItemDelegate(new HistoryDelegate(this));

	InitConnections();
}

MapInfoDlg::~MapInfoDlg()
{

}

void MapInfoDlg::InitConnections()
{
	connect(ui.btnRoute, SIGNAL(clicked()), this, SLOT(CurrentDisplayChanged()));
	connect(ui.btnPos, SIGNAL(clicked()), this, SLOT(CurrentDisplayChanged()));
	connect(ui.lstMapData, SIGNAL(clicked(const QModelIndex&)), this, SLOT(OnLstBrowserDataClicked(const QModelIndex&)));
}

void MapInfoDlg::Update()
{
	m_model->clear();

	DataManager& dm = DataManager::GetInstance();
	std::wstring key = dm.GetCurrentForensicsDir();

	GetMapListMethod mapListMethod = MapInfoDict[m_type];

	const MapsList* mapsInfo = (dm.*mapListMethod)(key);

	if ( NULL == mapsInfo )
		return;

	for ( MapsList::const_iterator it = mapsInfo->begin();
		it != mapsInfo->end();
		++it )
	{
		if ( it->isPos && ui.btnRoute->isChecked() )
			continue;

		if ( !it->isPos && ui.btnPos->isChecked() )
			continue;

		QStandardItem* item = new QStandardItem(Utils::utoq(it->route + "\n\n"));
		item->setData(Utils::utoq(it->route), Qt::UserRole);
		m_model->appendRow(item);
	}
}

void MapInfoDlg::CurrentDisplayChanged()
{
	Update();
}

void MapInfoDlg::OnLstBrowserDataClicked(const QModelIndex& index)
{
	QString url = QString("http://api.map.baidu.com/geocoder?address=%1&output=html").arg(index.data(Qt::UserRole).toString());
	ShellExecuteW(NULL, L"open", Utils::qtow(url).c_str(), NULL, NULL, SW_SHOW);
}

void MapInfoDlg::OnEdtFilterTextChanged(QString key)
{
	QRegExp reg(key, Qt::CaseInsensitive, QRegExp::FixedString);
	m_filter->setFilterRegExp(reg);
}
