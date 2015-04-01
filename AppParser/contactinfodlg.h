#ifndef CONTACTINFODLG_H
#define CONTACTINFODLG_H

#include <QFrame>
#include "ui_contactinfodlg.h"

class ContactInfoDlg : public QFrame
{
	Q_OBJECT

public:
	ContactInfoDlg(QWidget *parent = 0);
	~ContactInfoDlg();

public:
	void Update();

public slots:
	void OnEdtFilterTextChanged(QString filterString);

private:
	void InitTreeView();
	void InitConnection();

private:
	Ui::ContactInfoDlg ui;
	QStandardItemModel* m_model;
	QSortFilterProxyModel* m_filter;
};

#endif // CONTACTINFODLG_H
