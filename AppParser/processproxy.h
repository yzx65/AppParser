#ifndef PROCESSPROXY_H
#define PROCESSPROXY_H

#include <QtGui>
#include <windows.h>

class ProcessProxy : public QObject
{
	Q_OBJECT

public:
	ProcessProxy(QString procPath);
	~ProcessProxy();

signals:
	void Attached();
	void Finished();

public:
	bool Start();
	bool Terminate();

public:
	static PROCESS_INFORMATION CreateProcess(const wchar_t* processName, DWORD flag = NULL);
	static void KillProcess(const wchar_t* processName);

private slots:
	void CheckProcess();

private:
	QString m_procPath;
	QTimer m_check;
	HANDLE m_process;
};

#endif // PROCESSPROXY_H