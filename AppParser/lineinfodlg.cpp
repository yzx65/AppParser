#include "StdAfx.h"
#include "lineinfodlg.h"

#include "utils.h"
#include "datamanager.h"

LineInfoDlg::LineInfoDlg(QWidget *parent)
	: QFrame(parent)
{
	ui.setupUi(this);
	Utils::InitStyle(this);

	ui.btnBack->hide();
	ui.btnFront->hide();

	InitListView();
	InitConnections();
}

LineInfoDlg::~LineInfoDlg()
{

}

void LineInfoDlg::InitConnections()
{
	connect(ui.btnBack, SIGNAL(clicked()), ui.edtLineRecord, SLOT(Back()));
	connect(ui.btnFront, SIGNAL(clicked()), ui.edtLineRecord, SLOT(Front()));

	connect(ui.edtLineRecord, SIGNAL(FrontShow()), this, SLOT(FrontShow()));
	connect(ui.edtLineRecord, SIGNAL(BackShow()), this, SLOT(BackShow()));
	connect(ui.edtLineRecord, SIGNAL(FrontHide()), this, SLOT(FrontHide()));
	connect(ui.edtLineRecord, SIGNAL(BackHide()), this, SLOT(BackHide()));

	connect(ui.lstLineFriends, SIGNAL(clicked(const QModelIndex&)), this, SLOT(OnLstLineFriendsClicked(const QModelIndex&)));
}

void LineInfoDlg::InitListView()
{
	m_filter = new QSortFilterProxyModel(this);
	m_model = new QStandardItemModel(this);
	m_filter->setSourceModel(m_model);
	ui.lstLineFriends->setModel(m_filter);
}

void LineInfoDlg::FrontShow()
{
	ui.btnFront->show();
}

void LineInfoDlg::BackShow()
{
	ui.btnBack->show();
}

void LineInfoDlg::FrontHide()
{
	ui.btnFront->hide();
}

void LineInfoDlg::BackHide()
{
	ui.btnBack->hide();
}

void LineInfoDlg::Update()
{
	ui.edtLineRecord->ClearText();
	m_model->clear();

	DataManager& dm = DataManager::GetInstance();
	LineInfoMap* lines = dm.GetLineInfoMap(dm.GetCurrentForensicsDir());

	if ( NULL == lines )
		return;

	for ( LineInfoMap::iterator it = lines->begin();
		it != lines->end();
		it = lines->upper_bound(it->first) )
	{
		QStandardItem* item = new QStandardItem(Utils::utoq((*it).first));

		item->setData(Utils::utoq((*it).first), Qt::UserRole);
		m_model->appendRow(item);
	}
}

void LineInfoDlg::OnLstLineFriendsClicked( const QModelIndex& index )
{
	QString name = index.data(Qt::UserRole).toString();

	DataManager& dm = DataManager::GetInstance();
	LineInfoMap* lines = dm.GetLineInfoMap(dm.GetCurrentForensicsDir());

	if ( NULL == lines )
		return;

	std::string lineName = Utils::qtou(name);
	LineInfoMap::iterator it = lines->find(lineName);
	int count = lines->count(lineName);

	ui.edtLineRecord->ClearText();

	for ( int i = 0 ; i < count; ++i, ++it )
	{

		if ( (*it).second.isSend )
			ui.edtLineRecord->AddChatText(
			Utils::stoq("·¢ËÍ"), Utils::utoq((*it).second.time), Utils::utoq((*it).second.content));
		else
			ui.edtLineRecord->AddChatText(
			Utils::stoq("½ÓÊÕ"), Utils::utoq((*it).second.time), Utils::utoq((*it).second.content));
	}

	ui.edtLineRecord->UpdateTextBrowser();
}

void LineInfoDlg::OnEdtFilterTextChanged(QString key)
{
	QRegExp reg(key, Qt::CaseInsensitive, QRegExp::FixedString);
	m_filter->setFilterRegExp(reg);
}