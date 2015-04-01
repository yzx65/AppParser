#include "StdAfx.h"
#include "contactinfodlg.h"
#include "utils.h"
#include "datamanager.h"

ContactInfoDlg::ContactInfoDlg(QWidget *parent)
	: QFrame(parent)
{
	ui.setupUi(this);
	Utils::InitStyle(this);

	InitTreeView();
	InitConnection();
}

ContactInfoDlg::~ContactInfoDlg()
{

}

void ContactInfoDlg::InitTreeView()
{
	ui.tbContactInfo->header()->resizeSection(0, 50);
	ui.tbContactInfo->header()->resizeSection(1, 100);
	ui.tbContactInfo->header()->resizeSection(2, 200);

	m_model = new QStandardItemModel(0, 7, this);
	m_filter = new QSortFilterProxyModel(this);

	m_model->setHeaderData(0, Qt::Horizontal, Utils::stoq("分组"));
	m_model->setHeaderData(1, Qt::Horizontal, Utils::stoq("姓名"));
	m_model->setHeaderData(2, Qt::Horizontal, Utils::stoq("电话号码"));
	m_model->setHeaderData(3, Qt::Horizontal, Utils::stoq("邮件"));
	m_model->setHeaderData(4, Qt::Horizontal, Utils::stoq("地址"));
	m_model->setHeaderData(5, Qt::Horizontal, Utils::stoq("职位"));

	m_model->setHeaderData(6, Qt::Horizontal, "used for filter");

	m_filter->setSourceModel(m_model);
	m_filter->setFilterKeyColumn(6);

	ui.tbContactInfo->setModel(m_filter);
	ui.tbContactInfo->hideColumn(6);
	ui.tbContactInfo->hideColumn(0);
}

void ContactInfoDlg::InitConnection()
{
}

void ContactInfoDlg::Update()
{
	m_model->removeRows(0, m_model->rowCount());

	DataManager& dm = DataManager::GetInstance();
	const CONTACT_InfoList* contacts = dm.GetContactInfoList(dm.GetCurrentForensicsDir());

	if ( NULL == contacts )
		return;

	for ( CONTACT_InfoList::const_iterator it = contacts->begin();
		  it != contacts->end();
		  ++it )
	{
		//if ( it->number.empty() )
		//	continue;

		m_model->insertRow(0);
		m_model->setData(m_model->index(0, 0), Utils::wtoq(it->group));
		m_model->setData(m_model->index(0, 1), Utils::wtoq(it->name));
		m_model->setData(m_model->index(0, 2), Utils::wtoq(it->number));
		m_model->setData(m_model->index(0, 3), Utils::wtoq(it->email));
		m_model->setData(m_model->index(0, 4), Utils::wtoq(it->address));
		m_model->setData(m_model->index(0, 5), Utils::wtoq(it->profession));
		m_model->setData(m_model->index(0, 6), Utils::wtoq(it->name + L" " + it->number));
	}
}

void ContactInfoDlg::OnEdtFilterTextChanged(QString filterString)
{
	QRegExp reg(filterString, Qt::CaseInsensitive, QRegExp::FixedString);
	m_filter->setFilterRegExp(reg);
}
