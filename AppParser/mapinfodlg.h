#ifndef MAPINFODLG_H
#define MAPINFODLG_H

#include <QFrame>
#include "ui_mapinfodlg.h"

class MapInfoDlg : public QFrame
{
	Q_OBJECT

public:

	enum MapType
	{
		MAP_BAIDU,
		MAP_GAODE
	};

	MapInfoDlg(QWidget *parent = 0, MapType type = MAP_BAIDU);
	~MapInfoDlg();

public:
	void Update();

public slots:
	void CurrentDisplayChanged();
	void OnLstBrowserDataClicked(const QModelIndex&);
	void OnEdtFilterTextChanged(QString key);

private:
	void InitConnections();

private:
	Ui::MapInfoDlg ui;
	QStandardItemModel* m_model;
	QSortFilterProxyModel* m_filter;

	int m_type;
};

#endif // MAPINFODLG_H
