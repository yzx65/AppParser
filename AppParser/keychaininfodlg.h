#ifndef KEYCHAININFODLG_H
#define KEYCHAININFODLG_H

#include <QFrame>
#include "ui_keychaininfodlg.h"

class KeyChainInfoDlg : public QFrame
{
	Q_OBJECT

public:
	KeyChainInfoDlg(QWidget *parent = 0);
	~KeyChainInfoDlg();

public:
	void Update();

public slots:
	void OnLstServiceClicked(const QModelIndex&);
	void OnEdtFilterTextChanged(QString key);

private:
	void InitListView();
	void InitConnections();

private:
	Ui::KeyChainInfoDlg ui;

private:
	QStandardItemModel* m_model;
	QSortFilterProxyModel* m_filter;
};

#endif // KEYCHAININFODLG_H
