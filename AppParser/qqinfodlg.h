#ifndef QQINFODLG_H
#define QQINFODLG_H

#include <QFrame>
#include <QSortFilterProxyModel>
#include "ui_qqinfodlg.h"

struct AccountInfo;

class ChildrenFilter : public QSortFilterProxyModel
{
	Q_OBJECT
public:
	ChildrenFilter(QObject* parent = 0) : QSortFilterProxyModel(parent) {}

protected:
	bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;
};

class QQInfoDlg : public QFrame
{
	Q_OBJECT

public:
	QQInfoDlg(QWidget *parent = 0);
	~QQInfoDlg();

public:
	void Update();

private:
	void InitConnections();
	void AddQQFriends(AccountInfo& accountInfo);
	void AddQQTroops(AccountInfo& accountInfo);
	void AddQQDiscusses(AccountInfo& accountInfo);

	QStandardItem* FindParent(std::string& groupName);

public slots:
	void FrontShow();
	void BackShow();
	void FrontHide();
	void BackHide();

	void OnEdtFilterTextChanged(QString key);

private slots:
	void OnCurrentAccountChanged(int index);
	void OnTrQQAccountsClicked(const QModelIndex& index);

private:
	Ui::QQInfoDlg ui;
	QStandardItemModel* m_model;
	ChildrenFilter* m_filter;
};

#endif // QQINFODLG_H
