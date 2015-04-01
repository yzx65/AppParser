#ifndef PARSEDLG_H
#define PARSEDLG_H

#include <QFrame>
#include "ui_parsedlg.h"

class ParseThread;
class ParseDlg : public QFrame
{
	Q_OBJECT

public:
	ParseDlg(QWidget *parent, std::wstring deviceName, bool clear);
	~ParseDlg();

public:
	static void Invoke(std::wstring key, bool clear=false);

signals:
	void OK();

public slots:
	void StartParse();
	void ParseDone();
	void ParseFailed();

	void CurrentStatus(QString status);
	void CurrentProcess(int value);
	void TotalProcess(int value);

	void OnQueryIosBackupPassword();

private:
	void InitConnections();

private:
	Ui::ParseDlg ui;
	std::wstring m_key;
	ParseThread* m_parse;
	bool m_clear;
};

#endif // PARSEDLG_H
