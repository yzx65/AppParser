#ifndef SELECTDIRDLG_H
#define SELECTDIRDLG_H

#include <QFrame>
#include <QThread>
#include "ui_selectdirdlg.h"
#include "datamanager.h"

class SelectDirDlg : public QFrame
{
	Q_OBJECT

public:
	SelectDirDlg(QWidget *parent = 0);
	~SelectDirDlg();

public:
	static int Invoke(QString dir = "");

signals:
	void OK();
	void Resize(QSize size);
	void CenterWindow();
	void SetSubTitle(QString title);

public slots:
	void Browse();
	void SelectForensicsType();

	void SelectForensicsTypeFinished();

private:
	void InitConnections();
	void SetDataDir(QString dir);

	void ListDevices();

private:
	Ui::SelectDirDlg ui;
	DataManager m_dm;	// Used to cache temp data
};

#endif // SELECTDIRDLG_H
