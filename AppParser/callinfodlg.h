#ifndef CALLINFODLG_H
#define CALLINFODLG_H

#include <QFrame>
#include "ui_callinfodlg.h"

class CallInfoDlg : public QFrame
{
	Q_OBJECT

public:
	CallInfoDlg(QWidget *parent = 0);
	~CallInfoDlg();

public:
	void Update();

public slots:
	void OnLstCallFriendsClicked(const QModelIndex&);
	void OnEdtFilterTextChanged(QString key);

private:
	void InitListView();
	void InitConnection();

private:
	Ui::CallInfoDlg ui;

private:
	QStandardItemModel* m_model;
	QSortFilterProxyModel* m_filter;
};

#endif // CALLINFODLG_H
