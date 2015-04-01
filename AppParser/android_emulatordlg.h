#ifndef ANDROIDEMULATORDLG_H
#define ANDROIDEMULATORDLG_H

#include <QFrame>
#include <QThread>
#include <list>
#include <map>
#include "ui_android_emulatordlg.h"
#include "waitdlg.h"

typedef std::list<std::wstring> ExportTaskList; // a list of app name

class AdbController;

class ExportWorker : public QObject
{
	Q_OBJECT

public:
	ExportWorker(const ExportTaskList& taskList);
	~ExportWorker();

	void Quit(){ m_quit = true; }

signals:
	void ProcessTaskStatus(QString status);
	void ProcessTaskDone();
	void ProcessTaskFailed();

	void EmulatorReady();

public slots:
	void ProcessExportTask();
	void ProcessUninstallTask();
	void CheckEmulatorReady();

private:
	const ExportTaskList& m_taskList;
	AdbController* m_adb;
	bool m_quit;
};

class ProcessProxy;

class Android_EmulatorDlg : public QFrame
{
	Q_OBJECT

public:
	Android_EmulatorDlg(QWidget *parent = 0);
	~Android_EmulatorDlg();

public:
	void Update();

signals:
	void CheckEmulatorReady();
	void ProcessExportTask();
	void ProcessUninstallTask();

public slots:

	void OnBtnExportClicked();
	void OnBtnExportAllClicked();

	void OnBtnUninstallClicked();
	void OnBtnUninstallAllClicked();

	void OnBtnEmulatorClicked();
	void OnBtnToggleNetworkClicked();

	void EmulatorFinished();
	void EmulatorAttached();

	void EmulatorReady();
	void ProcessTaskStatus(QString status);
	void ProcessTaskDone();

private:
	
	void InitConnection();
	void InitTreeView();
	void AddAppItem(QString name, QString domain, QString icon, QString version );

	void SetExportEnable(bool enable);

private:
	Ui::Android_EmulatorDlg ui;
	ProcessProxy* m_emulator;
	ExportTaskList m_exportTask;
	ExportWorker* m_exportWorker;
	QThread* m_exportThread;

	WaitDlg* m_waitDlg;
};

#endif // ANDROIDEMULATORDLG_H
