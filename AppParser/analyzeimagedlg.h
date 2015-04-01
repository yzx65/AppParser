#ifndef ANALYZEIMAGEDLG_H
#define ANALYZEIMAGEDLG_H

#include <QFrame>
#include "ui_analyzeimagedlg.h"

#include <QThread>
#include <string>

class SearchImageThread : public QThread
{
	Q_OBJECT
public:
	SearchImageThread(QObject* parent = 0) : QThread(parent) {};

public:
	void SetSearchParameters(std::wstring imageFile, QString searchStr, bool utf8 = true);

signals:
	void TotalProgress(int value);
	void CurrentProgress(int value);
	void SearchResult(QString result, __int64 offset);
	void SearchFinished();

protected:
	void run();

private:
	std::wstring m_imageFile;
	QString m_searchStr;
	bool m_utf8;
};

class AnalyzeImageDlg : public QFrame
{
	Q_OBJECT

public:
	AnalyzeImageDlg(QWidget *parent = 0);
	~AnalyzeImageDlg();

public:
	void Update();

private:
	void InitConnections();

public slots:

	void TotalProgress(int process);
	void CurrentProgress(int process);
	void SearchFinished();
	void SearchResult(QString result, __int64 offset);

private slots:

	void OnBtnBrowseSavePathClicked();
	void OnBtnRecoveryClicked();

	void OnEdtSearchStrTextChanged(const QString & text);

	void OnBtnSearchClicked();
	void OnBtnExportClicked();

	void OnBtnBrowseImageClicked();

private:
	Ui::AnalyzeImageDlg ui;
	SearchImageThread* m_searchThd;
	int m_resultCount;
	bool m_closed;
};

#endif // ANALYZEIMAGEDLG_H
