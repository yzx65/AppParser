#ifndef IOS_EMULATORDLG_H
#define IOS_EMULATORDLG_H

#include <QFrame>
#include "ui_ios_emulatordlg.h"
#include <Windows.h>
#include <list>

struct Task
{
	char* deviceId;
	WCHAR appFilePath[MAX_PATH];
	char appId[MAX_PATH];
	WCHAR appDataPath[MAX_PATH];
	std::wstring appName;
	char srcId[MAX_PATH];
	WCHAR rootPath[MAX_PATH];
	char password[MAX_PATH];
};

typedef std::list<Task> TaskList;

class Emulator : public QObject
{
	Q_OBJECT

public:
	Emulator(TaskList& taskList, char** deviceList);
	static void SetInstance(Emulator* instance);
	static Emulator* GetInstance();
	~Emulator();

signals:
	void ProcessTaskStatus(QString status);
	void ProcessTaskDone();
	void ProcessTaskFailed();
	void DeviceListDone();

	void RecoveryBackupProcess(int value);
	void RecoveryBackupDone();
	void RecoveryBackupFailed();

public slots:
	void ProcessExportTask();
	void ProcessInstallTask();
	void RefreshDeviceList();

	void RecoveryBackup();

	void DoNotify(int process)
	{
		emit RecoveryBackupProcess(process);
	}

private:
	TaskList& m_taskList;
	char** m_deviceList;
	static Emulator* m_instance;
};

class IOS_EmulatorDlg : public QFrame
{
	Q_OBJECT

public:
	IOS_EmulatorDlg(QWidget *parent = 0);
	~IOS_EmulatorDlg();

signals:
	void ProcessExportTask();
	void ProcessInstallTask();
	void RefreshDeviceList();

	void RecoveryBackup();

public:
	void Update();

protected:
	bool winEvent( MSG * msg, long * result );

public slots:
	void OnBtnExportClicked();
	void OnBtnExportAllClicked();

	void OnBtnInstallClicked();
	void OnBtnInstallAllClicked();

	void ProcessTaskStatus(QString status);
	void ProcessTaskDone();
	void ProcessTaskFailed();
	void RefreshDeviceListDone();

	void OnBtnRecoveryBackupClicked();
	void RecoveryBackupProcess(int value);
	void RecoveryBackupDone();
	void RecoveryBackupFailed();

private:
	void RegisterUsbNotify();
	void InitConnection();
	void InitTreeView();
	void AddAppItem(QString name, QString domain, QString icon, QString version);
	void SetExportEnable(bool enable);

	bool IsIOSDevice(MSG* msg);
	void DeviceConnected();
	void DeviceRemoved();

	void AddAppTask(QTreeWidgetItem* item);
	void AddRecoveryBackupTask(const char* password);

	void RecoveryBackupTaskWithUserInput();

private:
	Ui::IOS_EmulatorDlg ui;
	HDEVNOTIFY m_hUsbNotify;
	bool m_connected;

	char** m_deviceList;

	Emulator* m_emulator;
	QThread* m_emulatorThd;

	TaskList m_tasks;
};

#endif // IOS_EMULATORDLG_H
