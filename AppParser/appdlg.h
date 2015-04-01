#ifndef APPDLG_H
#define APPDLG_H

#include <QFrame>
#include <QThread>
#include "ui_appdlg.h"
#include <map>
#include "datamanager.h"

class SaveDataThread : public QThread
{
	Q_OBJECT
public:
	SaveDataThread(QObject* parent)
		: QThread(parent)
	{

	}

	void run()
	{
		DataManager::GetInstance().SaveCurrentDeviceData();
	}
};

class WaitDlg;

class SmsInfoDlg;
class CallInfoDlg;
class WeixinInfoDlg;
class QQInfoDlg;
class LineInfoDlg;
class BrowserInfoDlg;
class BasicInfoDlg;
class ContactInfoDlg;
class EmulatorDlg;
class AnalyzeImageDlg;
class KeyChainInfoDlg;
class DelInfoDlg;

class MapInfoDlg;

class NavModel;
class NavDelegate;

class AppDlg : public QFrame
{
	Q_OBJECT

public:
	AppDlg(QWidget *parent = 0);
	~AppDlg();

signals:
	void AddMenuAction(QAction* action);
	void AddSubMenu(QMenu* action);
	void RemoveMenuAction(QAction* action);
	void SetSubTitle(QString subTitle);

public:
	void InitAction();
	void AnalyzeDir(QString dir);

public slots:
	void SelectDataDir();
	void SaveData();
	void SaveDataFinished();

private slots:
	void OnListViewClicked(const QModelIndex &index);
	void CurrentDeviceChanged();
	void OnBtnCollapseNavBarClicked();

private:
	void InitNavBar();
	void InitAppStack();
	void InitConnection();
	void InitDragAndDrop();

	void UpdateCase();
	void SetCurrentDevice(QString key, bool clear = false);

	bool SearchBarCanShow(const std::wstring& content);

	void UpdateBtnCollapseNavBar();

protected:

	void dropEvent(QDropEvent *e);
	void dragMoveEvent(QDragMoveEvent *e);
	void dragEnterEvent(QDragEnterEvent* e);
	bool eventFilter(QObject *obj, QEvent *event);

private:
	Ui::AppDlg ui;
	std::map<std::wstring, int> m_appMap;

	NavModel* m_navModel;
	NavDelegate* m_navDelegate;

	QMenu* m_deviceMenu;

	SmsInfoDlg* m_sms;
	CallInfoDlg* m_call;
	ContactInfoDlg* m_contactInfo;

	DelInfoDlg* m_smsDel;
	DelInfoDlg* m_callDel;
	DelInfoDlg* m_contactDel;

	WeixinInfoDlg* m_weixin;
	QQInfoDlg* m_qq;
	LineInfoDlg* m_line;

	BrowserInfoDlg* m_defaultBrowser;
	BrowserInfoDlg* m_ucBrowser;
	BrowserInfoDlg* m_qqBrowser;
	BrowserInfoDlg* m_baiduBrowser;
	BrowserInfoDlg* m_jinshanBrowser;
	BrowserInfoDlg* m_safariBrowser;

	BasicInfoDlg* m_basicInfo;
	EmulatorDlg* m_emulator;
	AnalyzeImageDlg* m_analyzeImage;
	KeyChainInfoDlg* m_keyChain;

	MapInfoDlg* m_baiduMapInfo;
	MapInfoDlg* m_gaodeMapInfo;

	SaveDataThread* m_save;
	WaitDlg* m_wait;

	QPushButton* m_btnCollapseNavBar;
};

#endif // APPDLG_H
