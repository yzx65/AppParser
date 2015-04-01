#ifndef SMSINFODLG_H
#define SMSINFODLG_H

#include <QFrame>
#include "ui_smsinfodlg.h"

class SmsInfoDlg : public QFrame
{
	Q_OBJECT

public:
	SmsInfoDlg(QWidget *parent = 0);
	~SmsInfoDlg();

public:
	void Update();

private:
	void InitConnections();
	void InitListView();

public slots:
	void FrontShow();
	void BackShow();
	void FrontHide();
	void BackHide();

	void OnLstSmsFriendsClicked(const QModelIndex&);
	void OnEdtFilterTextChanged(QString key);

private:
	Ui::SmsInfoDlg ui;
	QStandardItemModel* m_model;
	QSortFilterProxyModel* m_filter;
};

#endif // SMSINFODLG_H
