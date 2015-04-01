#ifndef WEIXININFODLG_H
#define WEIXININFODLG_H

#include <QFrame>
#include "ui_weixininfodlg.h"

struct AccountInfo;

class WeixinInfoDlg : public QFrame
{
	Q_OBJECT

public:
	WeixinInfoDlg(QWidget *parent = 0);
	~WeixinInfoDlg();

public:
	void Update();

private:
	void InitConnections();
	void AddWeixinFriends(AccountInfo& accountInfo);

public slots:
	void FrontShow();
	void BackShow();
	void FrontHide();
	void BackHide();

	void OnEdtFilterTextChanged(QString key);

private slots:
	void OnCurrentAccountChanged(int index);
	void OnLstWeixinFriendsClicked(const QModelIndex& index);

private:
	Ui::WeixinInfoDlg ui;
	QStandardItemModel* m_model;
	QSortFilterProxyModel* m_filter;
};

#endif // WEIXININFODLG_H
