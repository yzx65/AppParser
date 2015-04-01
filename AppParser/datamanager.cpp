#include "StdAfx.h"
#include "datamanager.h"
#include "utils.h"
#include "datasaver.h"
#include "datareader.h"
#include "iosbackupadapter.h"
#include "androidimageadapter.h"
#include "keychainparser.h"

#include "UCParser.h"
#include "HDefaultBrowser.h"
#include "HQQBrowser.h"
#include "HBaiduBrowser.h"
#include "HJinshanBrowser.h"
#include "HSafari.h"

#include "HBaiduMaps.h"
#include "HGaoDeMaps.h"

#include "macros.h"

#include <QDomDocument>

#pragma comment(lib, "Sqlite.lib")
#pragma comment(lib, "QQParser.lib")
#pragma comment(lib, "WeixinParser.lib")
#pragma comment(lib, "UCParser.lib")
#pragma comment(lib, "BrowserSelf.lib")
#pragma comment(lib, "QQBrowser.lib")
#pragma comment(lib, "BaiduBrowser.lib")
#pragma comment(lib, "JinshanBrowser.lib")
#pragma comment(lib, "SafariBrowser.lib")
#pragma comment(lib, "BaiduMaps.lib")
#pragma comment(lib, "GaodeMaps.lib")
#pragma comment(lib, "Line.lib")

typedef
VOID
(WINAPIV
*SetOutputDataDir)(LPWSTR);

SetOutputDataDir g_SetOutputDataDir = NULL;
HMODULE g_OutputDll = NULL;

DataManager& DataManager::GetInstance()
{
	static DataManager dm;
	return dm;
}

DataManager::DataManager()
	: m_errNo(0)
{
	InitForensicsTypeMap();

	std::wstring dllPath = Utils::GetExePath() + L"\\DeleteSqlite3.dll";
	g_OutputDll = LoadLibraryW(dllPath.c_str());

	if ( g_OutputDll )
		g_SetOutputDataDir = (SetOutputDataDir)GetProcAddress(g_OutputDll, "SetOutputDataDir");

}

DataManager::~DataManager()
{
	if ( g_OutputDll )
		FreeLibrary(g_OutputDll);
}

bool DataManager::HasRecord(std::wstring recordType)
{
	if ( L"" == GetCurrentDevice() )
		return true;

	return GetRecordCount(recordType) != 0;
}

int DataManager::GetRecordCount(std::wstring recordType)
{
	QString method = Utils::GetNodeValue(Utils::wtoq(recordType), "function");

	if ( method.isEmpty() )
		return -1;

	int ret = 0;
	QMetaObject::invokeMethod(
		this, 
		method.toAscii(), 
		Qt::DirectConnection,
		Q_RETURN_ARG(int, ret),
		Q_ARG(std::wstring, GetCurrentForensicsDir()));
	
	return ret;
}

void DataManager::InitForensicsTypeMap()
{
	QString config = Utils::wtoq(Utils::GetExePath() + L"\\config.xml");

	QFile xml(config);

	if ( !xml.open(QIODevice::ReadOnly | QIODevice::Text) )
		return;

	QDomDocument doc;

	if ( !doc.setContent(&xml, false) )
		return;

	QDomElement node = doc.documentElement().firstChildElement("forensics");
	QDomNodeList children = node.childNodes();

	for ( int i = 0; i < children.count(); ++i )
	{
		QDomElement node = children.at(i).toElement();
		std::wstring dir = Utils::qtow(node.attribute("dir"));
		std::wstring name = Utils::qtow(node.attribute("name"));
		std::wstring icon = Utils::qtow(node.attribute("icon"));
		ForensicsTypeInfo info = {name, icon};
		m_forensicsTypeMap[dir] = info;
	}
}

bool DataManager::Empty()
{
	return m_caseList.empty();
}

void DataManager::Clear()
{
	m_deviceDataDirMap.clear();
	m_caseList.clear();
	m_deviceMap.clear();
	m_smsMap.clear();
	m_contactMap.clear();
	m_recordMap.clear();
	m_appMap.clear();

	m_qqMap.clear();
	m_weixinMap.clear();
	m_lineMap.clear();

	m_DefaultBrowserBookmarkMap.clear();
	m_DefaultBrowserHistoryMap.clear();
	m_UCBrowserBookmarkMap.clear();
	m_UCBrowserHistoryMap.clear();
	m_QQBrowserBookmarkMap.clear();
	m_QQBrowserHistoryMap.clear();
	m_BaiduBrowserBookmarkMap.clear();
	m_BaiduBrowserHistoryMap.clear();
	m_JinShanBrowserHistoryMap.clear();
	m_JinShanBrowserBookmarkMap.clear();
	m_SafariBrowserBookmarkMap.clear();
	m_SafariBrowserHistoryMap.clear();

	m_keyChainMap.clear();
}

void DataManager::SetDirPath(std::wstring dirPath)
{
	m_dirPath = dirPath;
}

const std::wstring& DataManager::GetDirPath()
{
	return m_dirPath;
}

std::wstring DataManager::GetCurrentDevice()
{
	return m_currentDevice;
}

std::wstring DataManager::GetCurrentDevicePath()
{
	return m_dirPath + L"\\" + m_currentDevice;
}

std::wstring DataManager::GetCurrentForensicsDir()
{
	return m_currentDevice + m_currentForensicsDir;
}

std::wstring DataManager::GetCurrentForensicsType()
{
	return m_currentForensicsDir;
}

void DataManager::SetCurrentDevice(std::wstring device)
{
	m_currentDevice = device;
}

void DataManager::SetCurrentForensicsDir(std::wstring dir)
{
	m_currentForensicsDir = dir;
}

void DataManager::SaveCurrentDeviceData()
{
	if ( m_currentDevice.empty() )
		return;

	DataSaver saver(m_currentDevice);

	saver.SaveBasicInfo(m_deviceMap[m_currentDevice]);
	saver.SaveSmsInfo(m_smsMap[m_currentDevice]);
	saver.SaveRecordInfo(m_recordMap[m_currentDevice]);
	saver.SaveContactInfo(m_contactMap[m_currentDevice]);
}

void DataManager::ReadDeviceData(std::wstring deviceName)
{
	DataReader reader(deviceName);
	reader.ReadBasicInfo(m_deviceMap[deviceName]);
	reader.ReadSmsInfo(m_smsMap[deviceName]);
	reader.ReadRecordInfo(m_recordMap[deviceName]);
	reader.ReadContactInfo(m_contactMap[deviceName]);
}

bool DataManager::ParseCaseInfo()
{
	std::wstring findStr = m_dirPath + L"\\*.*";
	WIN32_FIND_DATA fd = {0};

	HANDLE hf = FindFirstFile(findStr.c_str(), &fd);

	if ( INVALID_HANDLE_VALUE == hf )
		return false;

	do 
	{
		if ( ! ( fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) )
			continue;

		if ( 0 == wcscmp(fd.cFileName, L"..") || 0 == wcscmp(fd.cFileName, L".") )
			continue;

		if ( !Utils::FileExist(m_dirPath + L"\\" + fd.cFileName + L"\\DeviceInfo" )
			&& !Utils::FileExist(m_dirPath + L"\\" + fd.cFileName + L"\\Device_Info.xml" ) )
			continue;

		CASE_INFO info;
		wcscpy(info.wzDirPath, fd.cFileName);
		m_caseList.push_back(info);

		for ( ForensicsTypeMap::iterator it = m_forensicsTypeMap.begin();
			  it != m_forensicsTypeMap.end();
			  ++it )
		{
			if ( Utils::FileExist(m_dirPath + L"\\" + fd.cFileName + (*it).first) )
				m_deviceDataDirMap.insert(std::pair<std::wstring, std::wstring>(fd.cFileName, (*it).first));
		}

	} while ( FindNextFile(hf, &fd) );

	FindClose(hf);

	return true;
}

const std::list<CASE_INFO>& DataManager::GetCaseList()
{
	return m_caseList;
}

ForensicsTypeMap& DataManager::GetForensicsTypeMap()
{
	return m_forensicsTypeMap;
}

DeviceDataDirMap& DataManager::GetDeviceDataDirMap()
{
	return m_deviceDataDirMap;
}

void DataManager::ParseDeviceInfo(std::wstring deviceName)
{
	std::wstring key = deviceName;

	wchar_t deviceFile[MAX_PATH] = {0};
	wsprintfW(deviceFile, L"%s\\%s\\DeviceInfo", m_dirPath.c_str(), key.c_str());

	HANDLE hDevice = CreateFileW(
		deviceFile, FILE_GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if ( INVALID_HANDLE_VALUE == hDevice )
	{
		Utils::__TRACE(L"[DataManager] Create File Failed.[%s] [%d]\r\n", deviceFile, GetLastError());
		wsprintfW(deviceFile, L"%s\\%s\\Device_Info.xml", m_dirPath.c_str(), key.c_str());

		QFile xml(Utils::wtoq(deviceFile));

		if ( !xml.open(QIODevice::ReadOnly | QIODevice::Text) )
			return ;

		QDomDocument doc;

		if ( !doc.setContent(&xml, false) )
			return;

		QString type = doc.documentElement().firstChildElement("type").text();
		QString brand = doc.documentElement().firstChildElement("brand").text();
		QString model = doc.documentElement().firstChildElement("model").text();
		QString version = doc.documentElement().firstChildElement("version").text();
		QString cpu = doc.documentElement().firstChildElement("cpu_abi").text();
		QString imei = doc.documentElement().firstChildElement("imei").text();
		bool root = doc.documentElement().firstChildElement("root").text() == "yes";

		DEV_INFO devItem;
		memset(&devItem, 0, sizeof(DEV_INFO));
		devItem.baseDevInfo.devType = DEV_TYPE_ANDROID;
		wsprintfA(devItem.baseDevInfo.szDevName, "%s", Utils::qtou(brand).c_str());
		wsprintfA(devItem.baseDevInfo.szDevModel, "%s", Utils::qtou(model).c_str());
		wsprintfA(devItem.baseDevInfo.szOSVersion, "%s", Utils::qtou(version).c_str());
		wsprintfA(devItem.baseDevInfo.szCpuArc, "%s", Utils::qtou(cpu).c_str());
		wsprintfA(devItem.baseDevInfo.szSerialNum, "%s", Utils::qtou(imei).c_str());
		devItem.baseDevInfo.bJailBroken = root;

		m_deviceMap[key] = devItem;

		return;
	}

	SetFilePointer(hDevice, sizeof(LAST_STATUS), NULL, FILE_BEGIN);

	DEV_INFO devItem;
	DWORD readed = 0;

	ReadFile(hDevice, &devItem, sizeof(DEV_INFO), &readed, NULL);

	if ( !readed )
		return;

	Utils::CastChar(devItem.baseDevInfo.szCpuArc, '\n');
	Utils::CastChar(devItem.baseDevInfo.szOSVersion, '\n');

	m_deviceMap[key] = devItem;

	CloseHandle(hDevice);
}

DeviceInfoMap& DataManager::GetDeviceMap()
{
	return m_deviceMap;
}

void DataManager::ExtractBackupFile(std::wstring key)
{
	if ( DEV_TYPE_ANDROID == m_deviceMap[GetCurrentDevice()].baseDevInfo.devType )
	{
		Utils::ExtractBackUp(m_dirPath + L"\\" + key + L"\\backup.ab");

		std::wstring findStr = m_dirPath + L"\\" + key + L"\\*@*";
		WIN32_FIND_DATA fd = {0};
		HANDLE hf = FindFirstFile(findStr.c_str(), &fd);

		if ( INVALID_HANDLE_VALUE == hf )
		{
			int err = GetLastError();
			return;
		}

		do 
		{
			AndroidImageAdapter::ExtractImageFile(m_dirPath + L"\\" + key + L"\\" + fd.cFileName);

		} while ( FindNextFile(hf, &fd) );

		FindClose(hf);
	}
	else
	{
		if ( !IosBackupAdapter::UnBackup(m_dirPath + L"\\" + key, m_iosBackupPasswrod) )
		{
			m_errNo = EXTRACT_IOS_BACKUP_FAILED;
			return;
		}

		m_errNo = 0;

		IosBackupAdapter::GenerateKeyChain(m_dirPath + L"\\" + key);
	}
}

void DataManager::ParseKeyChainInfo(std::wstring key)
{
	if ( m_keyChainMap.end() != m_keyChainMap.find(key) )
		return;

	std::wstring path = m_dirPath + L"\\" + key;
	KeyChainParser parser(path);

	if ( !parser.Start() )
		return;

	KeyChainInfoMap keyChainMap;
	KeyChainInfo* info = parser.GetFirstKeyChainInfo();

	while ( info )
	{
		KeyChainInfo copy;
		copy.name = info->name;
		copy.password = info->password;
		copy.service = info->service;
		copy.serviceName = info->serviceName;
		copy.prefix = info->prefix;
		keyChainMap.insert(std::pair<std::string, KeyChainInfo>(copy.service, copy));

		info = parser.GetNextKeyChainInfo();
	}

	m_keyChainMap[key] = keyChainMap;
}

KeyChainInfoMap* DataManager::GetKeyChainInfoMap(std::wstring key)
{
	if ( m_keyChainMap.find(key) != m_keyChainMap.end())
		return & ( m_keyChainMap[key] );
	else
		return NULL;
}

int DataManager::GetKeyChainInfoCount(std::wstring key)
{
	if ( NULL == GetKeyChainInfoMap(key) )
		return 0;

	return GetKeyChainInfoMap(key)->size();
}

void DataManager::ParseAppInfo(std::wstring key)
{
	if ( m_appMap.end() != m_appMap.find(key) )
		return;

	wchar_t configPath[MAX_PATH] = {0};
	wsprintfW(configPath, L"%s\\%s\\Bin\\app_info.xml", m_dirPath.c_str(), key.c_str());

	APP_InfoMap info;

	QFile xml(Utils::wtoq(configPath));

	if ( !xml.open(QIODevice::ReadOnly | QIODevice::Text) )
	{
		Utils::__TRACE(L"[DataManager][ParseAppInfo] xml open failed. [%s]\r\n", configPath);
		return;
	}

	QDomDocument doc;

	if ( !doc.setContent(&xml, false) )
	{
		Utils::__TRACE(L"[DataManager][ParseAppInfo] xml setContent failed. [%s]\r\n", configPath);
		return;
	}

	QDomNode node = doc.documentElement();
	QDomNodeList children = node.childNodes();

	for ( int i = 0; i < children.count(); ++i )
	{
		QDomElement appInfoNode = children.at(i).toElement();
		APP_Info app;
		app.name = Utils::qtow(appInfoNode.attribute("name"));
		app.apk = Utils::qtow(appInfoNode.attribute("apk"));
		app.icon = Utils::qtow(appInfoNode.attribute("icon"));
		app.className = Utils::qtow(appInfoNode.attribute("class"));
		app.activity = Utils::qtow(appInfoNode.attribute("activity"));
		app.version = Utils::qtow(appInfoNode.attribute("version"));

		if ( Utils::FileExist(m_dirPath + L"\\" + key + L"\\" + app.className)
			|| Utils::FileExist(m_dirPath + L"\\" + key + L"\\" + app.className + L".tar.gz")
			|| Utils::FileExist(m_dirPath + L"\\" + key + L"\\" + app.className + L".zip") )
			info[app.name] = app;
	}

	m_appMap[key] = info;
}

APP_InfoMap* DataManager::GetAppInfoMap(std::wstring key)
{
	if ( m_appMap.find(key) != m_appMap.end() )
		return & (m_appMap[key]);
	else
		return NULL;
}

int DataManager::GetSystemAppInfoCount(std::wstring key)
{
	if ( NULL == GetSmsInfoMap(key)
		&& NULL == GetContactInfoList(key) 
		&& NULL == GetRecordInfoList(key) )
		return 0;

	return -1;
}

void DataManager::ParseSmsInfo(std::wstring key)
{
	if ( m_smsMap.end() != m_smsMap.find(key) )
		return;

	wchar_t dataPath[MAX_PATH] = {0};
	wsprintfW(dataPath, L"%s\\%s", m_dirPath.c_str(), key.c_str());

	if ( g_SetOutputDataDir )
		g_SetOutputDataDir(dataPath);

	if ( !SMS_Start(dataPath) )
		return;

	int recordCount = SMS_GetRecordCount();

	if ( 0 == recordCount )
		return;

	SMS_InfoMap infoMap;

	for ( int i = 0; i < recordCount; ++i )
	{
		SMS_Info* info = SMS_GetRecordAt(i);
		SMS_Info copy;
		copy.isSend = info->isSend;
		copy.message = info->message;
		copy.name = info->name;
		copy.number = info->number;
		copy.time = info->time;
		infoMap.insert(std::pair<std::wstring, SMS_Info>(copy.number, copy));
	}

	SMS_Free();
	m_smsMap[key] = infoMap;
}

SMS_InfoMap* DataManager::GetSmsInfoMap( std::wstring key )
{
	if ( m_smsMap.find(key) != m_smsMap.end() )
		return & (m_smsMap[key]);
	else
		return NULL;
}

int DataManager::GetSmsInfoCount(std::wstring key)
{
	if ( NULL == GetSmsInfoMap(key) )
		return 0;

	return GetSmsInfoMap(key)->size();
}

int DataManager::GetSmsInfoCountDel(std::wstring key)
{
	wchar_t dataPath[MAX_PATH] = {0};
	wsprintfW(dataPath, L"%s\\%s\\sms.bin", m_dirPath.c_str(), key.c_str());

	if ( Utils::FileExist(dataPath) )
		return -1;

	return 0;
}

void DataManager::ParseContactInfo(std::wstring key)
{
	if ( m_contactMap.end() != m_contactMap.find(key) )
		return;

	wchar_t dataPath[MAX_PATH] = {0};
	wsprintfW(dataPath, L"%s\\%s", m_dirPath.c_str(), key.c_str());

	if ( !CONTACT_Start(dataPath) )
		return;

	int recordCount = CONTACT_GetRecordCount();

	if ( 0 == recordCount )
		return;

	CONTACT_Info info;
	CONTACT_InfoList infoList;

	for ( int i = 0; i < recordCount; ++i )
	{
		CONTACT_Info* contact = CONTACT_GetRecordAt(i);
		info.address = contact->address;
		info.email = contact->email;
		info.group = contact->group;
		info.name = contact->name;
		info.number = contact->number;
		info.profession = contact->profession;

		if ( info.address.empty() 
			&& info.email.empty() 
			&& info.name.empty() 
			&& info.number.empty() 
			&& info.profession.empty() )
			continue;

		infoList.push_back(info);
	}

	m_contactMap[key] = infoList;
	CONTACT_Free();
}

const CONTACT_InfoList* DataManager::GetContactInfoList( std::wstring key )
{
	if ( m_contactMap.find(key) != m_contactMap.end() )
		return &(m_contactMap[key]);
	else
		return NULL;
}

int DataManager::GetContactInfoCount(std::wstring key)
{
	if ( NULL == GetContactInfoList(key) )
		return 0;

	return GetContactInfoList(key)->size();
}

int DataManager::GetContactInfoCountDel(std::wstring key)
{
	wchar_t dataPath[MAX_PATH] = {0};
	wsprintfW(dataPath, L"%s\\%s\\contacts.bin", m_dirPath.c_str(), key.c_str());

	if ( Utils::FileExist(dataPath) )
		return -1;

	return 0;
}

void DataManager::ParseRecordInfo(std::wstring key)
{
	if ( m_recordMap.end() != m_recordMap.find(key) )
		return;

	SQLiteHelper* sqlite = NULL;
	std::wstring location = Utils::GetExePath() + L"\\location.db";

	if ( Utils::FileExist(location) )
		sqlite = new SQLiteHelper;

	if ( sqlite )
		sqlite->ConnectToDatabase(location);

	wchar_t dataPath[MAX_PATH] = {0};
	wsprintfW(dataPath, L"%s\\%s", m_dirPath.c_str(), key.c_str());

	if ( !RECORD_Start(dataPath) )
		return;

	int recordCount = RECORD_GetRecordCount();

	if ( 0 == recordCount )
		return;

	RECORD_Info info;
	RECORD_InfoMap infoMap;

	for ( int i = 0; i < recordCount; ++i )
	{
		RECORD_Info* record = RECORD_GetRecordAt(i);
		info.date = record->date;
		info.location = record->location;
		info.name = record->name;
		info.number = record->number;
		info.time = record->time;
		info.type = record->type;

		// Update location info
		if ( sqlite )
		{
			std::wstring number = Utils::FilterChar(info.number, L' ');
			std::wstring mobileCode = number, areaCode = number;

			if ( number.length() > 7 )
				mobileCode = number.substr(0, 7);

			if ( areaCode.length() > 4 )
				areaCode = number.substr(0, 4);

			WCHAR sqlCmd[1024] = {0};
			wsprintfW(sqlCmd, L"select MobileArea from Dm_Mobile where MobileNumber='%s' or AreaCode='%s'", mobileCode.c_str(), areaCode.c_str());

			if ( sqlite->Exec(sqlCmd) && sqlite->Step() )
			{
				info.location = sqlite->GetText(0);
				sqlite->Finalize();
			}
		}

		infoMap.insert(std::pair<std::wstring, RECORD_Info>(info.number, info));
	}

	m_recordMap[key] = infoMap;

	RECORD_Free();

	if ( sqlite )
		sqlite->CloseDatabase();

	delete sqlite;
}

RECORD_InfoMap* DataManager::GetRecordInfoList(std::wstring key)
{
	if ( m_recordMap.find(key) != m_recordMap.end() )
		return &(m_recordMap[key]);
	else
		return NULL;
}

int DataManager::GetRecordInfoCount(std::wstring key)
{
	if ( NULL == GetRecordInfoList(key) )
		return 0;

	return GetRecordInfoList(key)->size();
}

int DataManager::GetRecordInfoCountDel(std::wstring key)
{
	wchar_t dataPath[MAX_PATH] = {0};
	wsprintfW(dataPath, L"%s\\%s\\records.bin", m_dirPath.c_str(), key.c_str());

	if ( Utils::FileExist(dataPath) )
		return -1;

	return 0;
}

int DataManager::GetSnsAppInfoCount(std::wstring key)
{
	if ( NULL == GetQQInfoCount(key)
		&& NULL == GetWeixinInfoCount(key)
		&& NULL == GetLineInfoMap(key) )
		return 0;

	return -1;
}

void DataManager::ParseQQInfo(std::wstring key)
{
	if ( m_qqMap.end() != m_qqMap.find(key) )
		return;

	wchar_t dataPath[MAX_PATH] = {0};
	wsprintfW(dataPath, L"%s\\%s", m_dirPath.c_str(), key.c_str());

	int systemType = m_deviceMap[m_currentDevice].baseDevInfo.devType == DEV_TYPE_IOS;

	AccountInfoMap accounts;

	if ( !QQ_InitEntry(dataPath, systemType) )
		return;

	char accoutListStr[2048] = {0};

	if ( !QQ_GetAccountList(accoutListStr, 2048) )
		return;

	std::list<std::string> accountList = Utils::SplitLines(accoutListStr, '|');

	for ( std::list<std::string>::iterator it = accountList.begin();
		it != accountList.end();
		++it )
	{
		AccountInfo accountInfo;
		std::string accountNumber = *it;
		accountInfo.account = accountNumber;

		int t1 = GetTickCount();

		if ( !QQ_GetAccoutInfo(accountNumber) )
			continue;

		int t2 = GetTickCount();
		Utils::__TRACE(L"QQ_GetAccoutInfo : %d ms\r\n", t2-t1);

		// Get friend info
		GetQQFriendInfo(accountInfo);

		// Get troop info
		GetQQTroopInfo(accountInfo);

		// Get discuss info
		GetQQDiscussInfo(accountInfo);

		int t3 = GetTickCount();
		Utils::__TRACE(L"Other operation : %d ms\r\n", t3-t2);

		accounts[accountNumber] = accountInfo;
	}

	QQ_Free();

	m_qqMap[key] = accounts;
}

void DataManager::GetQQFriendInfo(AccountInfo& accountInfo)
{
	FriendInfo* friendInfo = QQ_GetFirstFriend(accountInfo.account);

	while ( friendInfo )
	{
		FriendInfo copy;
		copy.account = friendInfo->account;
		copy.alias = friendInfo->alias;
		copy.groupId = friendInfo->groupId;
		copy.groupName = friendInfo->groupName;
		copy.iType = friendInfo->iType;
		copy.nickName = friendInfo->nickName;
		copy.remark = friendInfo->remark;
		copy.signature = friendInfo->signature;

		accountInfo.friends[copy.account] = copy;
		friendInfo = QQ_GetNextFriend(accountInfo.account);

		ChatHistoryList chatList;
		GetQQChatHistoryList(chatList, accountInfo.account, copy.account, 0);

		if ( !chatList.empty() )
			accountInfo.chatMap[copy.account] = chatList;
	}
}

void DataManager::GetQQTroopInfo(AccountInfo& accountInfo)
{
	TroopInfo* troopInfo = QQ_GetFirstTroop(accountInfo.account);

	while ( troopInfo )
	{
		TroopInfo copy;
		copy.troopMemo = troopInfo->troopMemo;
		copy.troopName = troopInfo->troopName;
		copy.troopUin = troopInfo->troopUin;

		accountInfo.troops.push_back(copy);
		troopInfo = QQ_GetNextTroop(accountInfo.account);
		
		ChatHistoryList chatList;
		GetQQChatHistoryList(chatList, accountInfo.account, copy.troopUin, 1);

		if ( !chatList.empty() )
			accountInfo.chatMap[copy.troopUin] = chatList;
	}
}

void DataManager::GetQQDiscussInfo(AccountInfo& accountInfo)
{
	DiscInfo* disscussInfo = QQ_GetFirstDisc(accountInfo.account);

	while ( disscussInfo )
	{
		DiscInfo copy;
		copy.createTime = disscussInfo->createTime;
		copy.discussName = disscussInfo->discussName;
		copy.discussUin = disscussInfo->discussUin;

		accountInfo.discusses.push_back(copy);
		disscussInfo = QQ_GetNextDisc(accountInfo.account);

		ChatHistoryList chatList;
		GetQQChatHistoryList(chatList, accountInfo.account, copy.discussUin, 2);

		if ( !chatList.empty() )
			accountInfo.chatMap[copy.discussUin] = chatList;
	}
}

void DataManager::GetQQChatHistoryList(ChatHistoryList& chatList, std::string accountNumber, std::string friendNumber, int type)
{
	ChatHistory* chat = QQ_GetFirstChatHistory(accountNumber, friendNumber, type);

	while ( chat )
	{
		ChatHistory copy;
		copy.filePath = chat->filePath;
		copy.isSend = chat->isSend;
		copy.message = chat->message;
		copy.msgType = chat->msgType;
		copy.senderName = chat->senderName;
		copy.senderUin = chat->senderUin;
		copy.time = chat->time;

		//Utils::__TRACE("%s %s %s %s\r\n", 
		//	copy.time.c_str(), accountNumber.c_str(), friendNumber.c_str(), Utils::Utf8ToGbk(copy.message).c_str());

		chatList.push_back(copy);
		chat = QQ_GetNextChatHistory(accountNumber, friendNumber, type);
	}
}

AccountInfoMap* DataManager::GetQQInfoMap(std::wstring key)
{
	if ( m_qqMap.find(key) != m_qqMap.end() )
		return & (m_qqMap[key]);
	else
		return NULL;
}

int DataManager::GetQQInfoCount(std::wstring key)
{
	if ( NULL == GetQQInfoMap(key) )
		return 0;

	return GetQQInfoMap(key)->size();
}

void DataManager::ParseWeixinInfo(std::wstring key)
{
	if ( m_weixinMap.end() != m_weixinMap.find(key) )
		return;

	wchar_t dataPath[MAX_PATH] = {0};
	wsprintfW(dataPath, L"%s\\%s", m_dirPath.c_str(), key.c_str());
	int systemType = m_deviceMap[m_currentDevice].baseDevInfo.devType == DEV_TYPE_IOS;

	AccountInfoMap accounts;
	char* imei = m_deviceMap[m_currentDevice].baseDevInfo.szSerialNum;

	if ( !WEIXIN_InitEntry(dataPath, systemType, imei) )
		return;

	char accoutListStr[2048] = {0};

	if ( !WEIXIN_GetAccountList(accoutListStr, 2048) )
		return;

	std::list<std::string> accountList = Utils::SplitLines(accoutListStr, '|');

	for ( std::list<std::string>::iterator it = accountList.begin();
		it != accountList.end();
		++it )
	{
		AccountInfo accountInfo;
		std::string accountNumber = *it;
		accountInfo.account = accountNumber;

		int t1 = GetTickCount();

		if ( !WEIXIN_GetAccoutInfo(accountNumber) )
			continue;

		int t2 = GetTickCount();
		Utils::__TRACE(L"Weixin_GetAccoutInfo : %d ms\r\n", t2-t1);

		// Get friend info
		GetWeixinFriendInfo(accountInfo);

		int t3 = GetTickCount();
		Utils::__TRACE(L"Other operation : %d ms\r\n", t3-t2);

		accounts[accountNumber] = accountInfo;
	}

	WEIXIN_Free();

	m_weixinMap[key] = accounts;
}

void DataManager::GetWeixinFriendInfo(AccountInfo& accountInfo)
{
	FriendInfo* friendInfo = WEIXIN_GetFirstFriend(accountInfo.account);

	while ( friendInfo )
	{
		FriendInfo copy;
		copy.account = friendInfo->account;
		copy.alias = friendInfo->alias;
		copy.groupId = friendInfo->groupId;
		copy.groupName = friendInfo->groupName;
		copy.iType = friendInfo->iType;
		copy.nickName = friendInfo->nickName;
		copy.remark = friendInfo->remark;
		copy.signature = friendInfo->signature;

		accountInfo.friends[copy.account] = copy;
		friendInfo = WEIXIN_GetNextFriend(accountInfo.account);

		ChatHistoryList chatList;
		GetWeixinChatHistoryList(chatList, accountInfo.account, copy.account, 0);

		if ( !chatList.empty() )
			accountInfo.chatMap[copy.account] = chatList;
	}
}

void DataManager::GetWeixinChatHistoryList(ChatHistoryList& chatList, std::string accountNumber, std::string friendNumber, int type)
{
	ChatHistory* chat = WEIXIN_GetFirstChatHistory(accountNumber, friendNumber, type);

	while ( chat )
	{
		ChatHistory copy;
		copy.filePath = chat->filePath;
		copy.isSend = chat->isSend;
		copy.message = chat->message;
		copy.msgType = chat->msgType;
		copy.senderName = chat->senderName;
		copy.senderUin = chat->senderUin;
		copy.time = chat->time;

		//Utils::__TRACE("Weixin : %s %s %d %s %s\r\n", 
		//	copy.time.c_str(), accountNumber.c_str(), copy.msgType, friendNumber.c_str(), Utils::Utf8ToGbk(copy.message).c_str());

		chatList.push_back(copy);
		chat = WEIXIN_GetNextChatHistory(accountNumber, friendNumber, type);
	}
}

AccountInfoMap* DataManager::GetWeixinInfoMap(std::wstring key)
{
	if ( m_weixinMap.find(key) != m_weixinMap.end() )
		return & (m_weixinMap[key]);
	else
		return NULL;
}

int DataManager::GetWeixinInfoCount(std::wstring key)
{
	if ( NULL == GetWeixinInfoMap(key) )
		return 0;

	return GetWeixinInfoMap(key)->size();
}

void DataManager::ParseLineInfo(std::wstring key)
{
	if ( m_lineMap.find(key) != m_lineMap.end() )
		return;

	WCHAR dataPath[MAX_PATH] = {0};
	wsprintfW(dataPath, L"%s\\%s", m_dirPath.c_str(), key.c_str());

	int systemType = m_deviceMap[m_currentDevice].baseDevInfo.devType == DEV_TYPE_IOS;

	if ( !Line_Start(dataPath, systemType) )
		return;

	LineInfoMap lineMap;
	LineBasicInfo* info = Line_GetFirst();

	while ( info )
	{
		LineBasicInfo copy;
		copy.name = info->name;
		copy.content = info->content;
		copy.time = info->time;
		copy.isSend = info->isSend;
		lineMap.insert(std::pair<std::string, LineBasicInfo>(copy.name, copy));
		info = Line_GetNext();
	}

	if ( !lineMap.empty() )
		m_lineMap[key] = lineMap;
}

LineInfoMap* DataManager::GetLineInfoMap(std::wstring key)
{
	if ( m_lineMap.find(key) == m_lineMap.end() )
		return NULL;

	return &(m_lineMap[key]);
}

int DataManager::GetLineInfoCount(std::wstring key)
{
	if ( NULL == GetLineInfoMap(key) )
		return 0;

	return GetLineInfoMap(key)->size();
}

int DataManager::GetBrowserAppInfoCount(std::wstring key)
{
	if ( NULL == GetUCBrowserInfoCount(key)
		&& NULL == GetDefaultBrowserInfoCount(key) 
		&& NULL == GetQQBrowserInfoCount(key)
		&& NULL == GetBaiduBrowserInfoCount(key)
		&& NULL == GetJinShanBrowserInfoCount(key)
		&& NULL == GetSafariBrowserInfoCount(key) )
		return 0;

	return -1;
}

BROWSER_INTERFACE_IMPLEMENT(Default)
BROWSER_INTERFACE_IMPLEMENT(UC)
BROWSER_INTERFACE_IMPLEMENT(QQ)
BROWSER_INTERFACE_IMPLEMENT(Baidu)
BROWSER_INTERFACE_IMPLEMENT(JinShan)
BROWSER_INTERFACE_IMPLEMENT(Safari)

Q_INVOKABLE int DataManager::GetMapAppInfoCount( std::wstring key )
{
	if ( NULL == GetBaiduMapInfoCount(key)
		&& NULL == GetGaodeMapInfoCount(key) )
		return 0;

	return -1;
}

void DataManager::ParseBaiduMapInfo( std::wstring key )
{
	if ( m_BaiduMapsInfoMap.find(key) != m_BaiduMapsInfoMap.end() )
		return;

	wchar_t dataPath[MAX_PATH] = {0};
	wsprintfW(dataPath, L"%s\\%s", m_dirPath.c_str(), key.c_str());

	int systemType = m_deviceMap[m_currentDevice].baseDevInfo.devType == DEV_TYPE_IOS;

	if ( !BaiduMaps_Start(dataPath, systemType) )
		return;

	MapsBasicInfo* info = BaiduMaps_GetFirstMaps();

	MapsList mapInfoList;

	while ( info )
	{
		MapsBasicInfo copy;
		copy.isPos = info->isPos;
		copy.route = info->route;
		mapInfoList.push_back(copy);

		info = BaiduMaps_GetNextMaps();
	}

	BaiduMaps_Free();

	m_BaiduMapsInfoMap[key] = mapInfoList;
}

const MapsList* DataManager::GetBaiduMapList( std::wstring key )
{
	if ( m_BaiduMapsInfoMap.find(key) == m_BaiduMapsInfoMap.end() )
		return NULL;

	return & (m_BaiduMapsInfoMap[key]);
}

Q_INVOKABLE int DataManager::GetBaiduMapInfoCount( std::wstring key )
{
	if ( NULL == GetBaiduMapList(key) )
		return 0;

	return GetBaiduMapList(key)->size();
}

void DataManager::ParseGaodeMapInfo( std::wstring key )
{
	if ( m_GaodeMapsInfoMap.find(key) != m_GaodeMapsInfoMap.end() )
		return;

	wchar_t dataPath[MAX_PATH] = {0};
	wsprintfW(dataPath, L"%s\\%s", m_dirPath.c_str(), key.c_str());

	int systemType = m_deviceMap[m_currentDevice].baseDevInfo.devType == DEV_TYPE_IOS;

	if ( !GaodeMaps_Start(dataPath, systemType) )
		return;

	MapsBasicInfo* info = GaodeMaps_GetFirstMaps();

	MapsList mapInfoList;

	while ( info )
	{
		MapsBasicInfo copy;
		copy.isPos = info->isPos;
		copy.route = info->route;
		mapInfoList.push_back(copy);

		info = GaodeMaps_GetNextMaps();
	}

	GaodeMaps_Free();

	m_GaodeMapsInfoMap[key] = mapInfoList;
}

const MapsList* DataManager::GetGaodeMapList( std::wstring key )
{
	if ( m_GaodeMapsInfoMap.find(key) == m_GaodeMapsInfoMap.end() )
		return NULL;

	return & (m_GaodeMapsInfoMap[key]);
}

Q_INVOKABLE int DataManager::GetGaodeMapInfoCount( std::wstring key )
{
	if ( NULL == GetGaodeMapList(key) )
		return 0;

	return GetGaodeMapList(key)->size();
}
