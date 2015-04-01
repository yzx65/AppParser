#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <string>
#include <list>
#include <map>
#include "CommonDef.h"
#include "ParserInterface.h"
#include "SQLiteHelper.h"
#include "datastructure.h"

#include "QQParser.h"
#include "WeixinParser.h"
#include "HLine.h"

#include "UCParser.h"

#include <QObject>


struct ForensicsTypeInfo
{
	std::wstring name;
	std::wstring icon;
};

// Key : dir
typedef std::map<std::wstring, ForensicsTypeInfo> ForensicsTypeMap;

// Key : deviceName
// Value : \App
typedef std::multimap<std::wstring, std::wstring> DeviceDataDirMap;

class DataManager : public QObject
{
	Q_OBJECT

public:

	enum ErrorDescription{EXTRACT_IOS_BACKUP_FAILED = 1};
	int GetError() { return m_errNo; }
	void SetIosBackupPassword(const std::string password) { m_iosBackupPasswrod = password; }

	static DataManager& GetInstance();

public:
	DataManager();
	~DataManager();

	bool HasRecord(std::wstring recordType);
	int GetRecordCount(std::wstring recordType);

	bool Empty();

	void Clear();
	void SetDirPath(std::wstring dirPath);
	const std::wstring& GetDirPath();

	std::wstring GetCurrentDevice();
	std::wstring GetCurrentDevicePath();
	std::wstring GetCurrentForensicsDir();
	std::wstring GetCurrentForensicsType();
	void SetCurrentDevice(std::wstring device);
	void SetCurrentForensicsDir(std::wstring dir);

	void SaveCurrentDeviceData();

	bool ParseCaseInfo();
	const std::list<CASE_INFO>& GetCaseList();
	ForensicsTypeMap& GetForensicsTypeMap();
	DeviceDataDirMap& GetDeviceDataDirMap();

	void ParseDeviceInfo(std::wstring deviceName);
	DeviceInfoMap& GetDeviceMap();

	void ExtractBackupFile(std::wstring key);

	void ParseKeyChainInfo(std::wstring key);
	KeyChainInfoMap* GetKeyChainInfoMap(std::wstring key);
	Q_INVOKABLE int GetKeyChainInfoCount(std::wstring key);

	void ParseAppInfo(std::wstring key);
	APP_InfoMap* GetAppInfoMap(std::wstring key);

	Q_INVOKABLE int GetSystemAppInfoCount(std::wstring key);

	void ParseSmsInfo(std::wstring key);
	SMS_InfoMap* GetSmsInfoMap(std::wstring key);
	Q_INVOKABLE int GetSmsInfoCount(std::wstring key);
	Q_INVOKABLE int GetSmsInfoCountDel(std::wstring key);

	void ParseContactInfo(std::wstring key);
	const CONTACT_InfoList* GetContactInfoList(std::wstring key);
	Q_INVOKABLE int GetContactInfoCount(std::wstring key);
	Q_INVOKABLE int GetContactInfoCountDel(std::wstring key);

	void ParseRecordInfo(std::wstring key);
	RECORD_InfoMap* GetRecordInfoList(std::wstring key);
	Q_INVOKABLE int GetRecordInfoCount(std::wstring key);
	Q_INVOKABLE int GetRecordInfoCountDel(std::wstring key);

	Q_INVOKABLE int GetSnsAppInfoCount(std::wstring key);

	void ParseQQInfo(std::wstring key);
	AccountInfoMap* GetQQInfoMap(std::wstring key);
	Q_INVOKABLE int GetQQInfoCount(std::wstring key);

	void ParseWeixinInfo(std::wstring key);
	AccountInfoMap* GetWeixinInfoMap(std::wstring key);
	Q_INVOKABLE int GetWeixinInfoCount(std::wstring key);

	void ParseLineInfo(std::wstring key);
	LineInfoMap* GetLineInfoMap(std::wstring key);
	Q_INVOKABLE int GetLineInfoCount(std::wstring key);

	Q_INVOKABLE int GetBrowserAppInfoCount(std::wstring key);

	void ParseDefaultBrowserInfo(std::wstring key);
	const HistoryList* GetDefaultBrowserHistoryList(std::wstring key);
	const BookmarkList* GetDefaultBrowserBookmarkList(std::wstring key);
	Q_INVOKABLE int GetDefaultBrowserInfoCount(std::wstring key);

	void ParseUCBrowserInfo(std::wstring key);
	const HistoryList* GetUCBrowserHistoryList(std::wstring key);
	const BookmarkList* GetUCBrowserBookmarkList(std::wstring key);
	Q_INVOKABLE int GetUCBrowserInfoCount(std::wstring key);

	void ParseQQBrowserInfo(std::wstring key);
	const HistoryList* GetQQBrowserHistoryList(std::wstring key);
	const BookmarkList* GetQQBrowserBookmarkList(std::wstring key);
	Q_INVOKABLE int GetQQBrowserInfoCount(std::wstring key);

	void ParseBaiduBrowserInfo(std::wstring key);
	const HistoryList* GetBaiduBrowserHistoryList(std::wstring key);
	const BookmarkList* GetBaiduBrowserBookmarkList(std::wstring key);
	Q_INVOKABLE int GetBaiduBrowserInfoCount(std::wstring key);

	void ParseJinShanBrowserInfo(std::wstring key);
	const HistoryList* GetJinShanBrowserHistoryList(std::wstring key);
	const BookmarkList* GetJinShanBrowserBookmarkList(std::wstring key);
	Q_INVOKABLE int GetJinShanBrowserInfoCount(std::wstring key);

	void ParseSafariBrowserInfo(std::wstring key);
	const HistoryList* GetSafariBrowserHistoryList(std::wstring key);
	const BookmarkList* GetSafariBrowserBookmarkList(std::wstring key);
	Q_INVOKABLE int GetSafariBrowserInfoCount(std::wstring key);

	Q_INVOKABLE int GetMapAppInfoCount(std::wstring key);

	void ParseBaiduMapInfo(std::wstring key);
	const MapsList* GetBaiduMapList(std::wstring key);
	Q_INVOKABLE int GetBaiduMapInfoCount(std::wstring key);

	void ParseGaodeMapInfo(std::wstring key);
	const MapsList* GetGaodeMapList(std::wstring key);
	Q_INVOKABLE int GetGaodeMapInfoCount(std::wstring key);

	void ReadDeviceData(std::wstring deviceName);


private:

	void InitForensicsTypeMap();

	void GetQQFriendInfo(AccountInfo& accountInfo);
	void GetQQTroopInfo(AccountInfo& accountInfo);
	void GetQQDiscussInfo(AccountInfo& accountInfo);
	void GetQQChatHistoryList(ChatHistoryList& chatList, std::string accountNumber, std::string friendNumber, int type);

	void GetWeixinFriendInfo(AccountInfo& accountInfo);
	void GetWeixinChatHistoryList(ChatHistoryList& chatList, std::string accountNumber, std::string friendNumber, int type);

private:

	ForensicsTypeMap m_forensicsTypeMap;

	DeviceDataDirMap m_deviceDataDirMap;
	DeviceDataDirMap m_upcomingDeviceDataDirMap;

	std::wstring m_dirPath;

	std::list<CASE_INFO> m_caseList;
	std::list<CASE_INFO> m_upcomingCaseList;

	// Key : device name
	std::map<std::wstring, DEV_INFO> m_deviceMap;
	std::map<std::wstring, DEV_INFO> m_upcomingDeviceMap;

	// Key : deviceName + app path 
	// Eg : GT-I9228-358059045626946\App
	//
	std::map<std::wstring, APP_InfoMap> m_appMap;
	std::map<std::wstring, KeyChainInfoMap> m_keyChainMap;

	std::map<std::wstring, SMS_InfoMap> m_smsMap;		
	std::map<std::wstring, CONTACT_InfoList> m_contactMap;
	std::map<std::wstring, RECORD_InfoMap> m_recordMap;

	std::map<std::wstring, AccountInfoMap> m_qqMap;
	std::map<std::wstring, AccountInfoMap> m_weixinMap;
	std::map<std::wstring, LineInfoMap> m_lineMap;

	std::map<std::wstring, HistoryList> m_DefaultBrowserHistoryMap;
	std::map<std::wstring, BookmarkList> m_DefaultBrowserBookmarkMap;

	std::map<std::wstring, HistoryList> m_UCBrowserHistoryMap;
	std::map<std::wstring, BookmarkList> m_UCBrowserBookmarkMap;

	std::map<std::wstring, HistoryList> m_QQBrowserHistoryMap;
	std::map<std::wstring, BookmarkList> m_QQBrowserBookmarkMap;

	std::map<std::wstring, HistoryList> m_BaiduBrowserHistoryMap;
	std::map<std::wstring, BookmarkList> m_BaiduBrowserBookmarkMap;

	std::map<std::wstring, HistoryList> m_JinShanBrowserHistoryMap;
	std::map<std::wstring, BookmarkList> m_JinShanBrowserBookmarkMap;

	std::map<std::wstring, HistoryList> m_SafariBrowserHistoryMap;
	std::map<std::wstring, BookmarkList> m_SafariBrowserBookmarkMap;

	std::map<std::wstring, MapsList> m_BaiduMapsInfoMap;
	std::map<std::wstring, MapsList> m_GaodeMapsInfoMap;

	std::wstring m_currentDevice;
	std::wstring m_currentForensicsDir;

	int m_errNo;
	std::string m_iosBackupPasswrod;
};

#endif // DATAMANAGER_H