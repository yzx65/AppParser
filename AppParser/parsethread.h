#ifndef PARSETHREAD_H
#define PARSETHREAD_H

#include <QThread>

class ParseThread : public QThread
{
	Q_OBJECT

public:
	ParseThread(QObject *parent);
	~ParseThread();

	void SetKey(std::wstring key);
	void SetClear(bool clear);

	void CancleExtract() { m_cancleExtract = true; }
	void InputFinished() { m_input = true; }
	void SetExtractPassword(std::string password) { m_extractPassword = password; }

signals:
	void CurrentStatus(QString status);
	void CurrentProcess(int value);
	void TotalProcess(int value);
	void ParseDone();
	void ParseFailed();
	
	void QueryIosBackupPassword();

protected:
	void run();

private:
	void WaitForUserInput();

private:
	std::wstring m_key;
	bool m_clear;	
	std::wstring m_path;

	std::string m_extractPassword;
	bool m_cancleExtract;
	bool m_input;
};

#endif // PARSETHREAD_H
