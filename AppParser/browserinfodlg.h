#ifndef BROWSERINFODLG_H
#define BROWSERINFODLG_H

#include <QFrame>
#include "ui_BrowserInfoDlg.h"

class BrowserInfoDlg : public QFrame
{
	Q_OBJECT

public:

	enum BrowserType
	{
		BROWSER_UC,
		BROWSER_DEFAULT,
		BROWSER_QQ,
		BROWSER_BAIDU,
		BROWSER_JINSHAN,
		BROWSER_SAFARI
	};

	BrowserInfoDlg(QWidget *parent = 0, BrowserType type = BROWSER_UC);
	~BrowserInfoDlg();

public:
	void Update();

public slots:
	void CurrentDisplayChanged();
	void OnLstBrowserDataClicked(const QModelIndex&);
	void OnEdtFilterTextChanged(QString key);

private:
	void InitConnections();

private:
	Ui::BrowserInfoDlg ui;
	QStandardItemModel* m_model;
	QSortFilterProxyModel* m_filter;

	int m_type;
};

#endif // BROWSERINFODLG_H
