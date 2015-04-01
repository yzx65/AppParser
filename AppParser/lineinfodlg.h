#ifndef LINEINFODLG_H
#define LINEINFODLG_H

#include <QFrame>
#include "ui_lineinfodlg.h"

class LineInfoDlg : public QFrame
{
	Q_OBJECT

public:
	LineInfoDlg(QWidget *parent = 0);
	~LineInfoDlg();

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

	void OnLstLineFriendsClicked(const QModelIndex&);
	void OnEdtFilterTextChanged(QString key);

private:
	Ui::LineInfoDlg ui;
	QStandardItemModel* m_model;
	QSortFilterProxyModel* m_filter;
};

#endif // LINEINFODLG_H
