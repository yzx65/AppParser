#ifndef MACRO_H
#define MACRO_H

#define BROWSER_INTERFACE_DECLARE(browserName) 	\
	void Parse##browserName##BrowserInfo(std::wstring key); \
	const HistoryList* Get##browserName##BrowserHistoryList(std::wstring key); \
	const BookmarkList* Get##browserName##BrowserBookmarkList(std::wstring key); \
	Q_INVOKABLE int Get##browserName##BrowserInfoCount(std::wstring key);

#define BROWSER_INTERFACE_IMPLEMENT(browserName) \
void DataManager::Parse##browserName##BrowserInfo(std::wstring key) \
{ \
	if ( m_##browserName##BrowserBookmarkMap.end() != m_##browserName##BrowserBookmarkMap.find(key) ) \
		return; \
	wchar_t dataPath[MAX_PATH] = {0}; \
	wsprintfW(dataPath, L"%s\\%s", m_dirPath.c_str(), key.c_str()); \
	int systemType = m_deviceMap[m_currentDevice].baseDevInfo.devType == DEV_TYPE_IOS; \
	if ( !##browserName##Browser_Start(dataPath, systemType) ) \
		return; \
	HistoryList historys; \
	BrowserHistory* history = ##browserName##Browser_GetFirstHistory(); \
	while ( history ) \
	{ \
		BrowserHistory info; \
		info.name = history->name; \
		info.time = history->time; \
		info.url = history->url; \
		historys.push_back(info); \
		history = ##browserName##Browser_GetNextHistory(); \
	} \
	BookmarkList bookmarks; \
	BrowserBookmark* bookmark = ##browserName##Browser_GetFirstBookMark(); \
	while ( bookmark ) \
	{ \
		BrowserBookmark info; \
		info.name = bookmark->name; \
		info.time = bookmark->time; \
		info.url = bookmark->url; \
		bookmarks.push_back(info); \
		bookmark = ##browserName##Browser_GetNextBookMark(); \
	} \
	##browserName##Browser_Free(); \
	m_##browserName##BrowserHistoryMap[key] = historys; \
	m_##browserName##BrowserBookmarkMap[key] = bookmarks; \
} \
	\
const HistoryList* DataManager::Get##browserName##BrowserHistoryList(std::wstring key) \
{ \
	if ( m_##browserName##BrowserHistoryMap.find(key) != m_##browserName##BrowserHistoryMap.end() ) \
		return & (m_##browserName##BrowserHistoryMap[key]); \
	else \
		return NULL; \
} \
	\
const BookmarkList* DataManager::Get##browserName##BrowserBookmarkList(std::wstring key) \
{ \
	if ( m_##browserName##BrowserBookmarkMap.find(key) != m_##browserName##BrowserBookmarkMap.end() ) \
		return & (m_##browserName##BrowserBookmarkMap[key]); \
	else \
		return NULL; \
} \
	\
int DataManager::Get##browserName##BrowserInfoCount(std::wstring key) \
{ \
	if ( NULL == Get##browserName##BrowserHistoryList(key) && NULL == Get##browserName##BrowserBookmarkList(key) ) \
		return 0; \
	if ( NULL == Get##browserName##BrowserBookmarkList(key) ) \
		return Get##browserName##BrowserHistoryList(key)->size(); \
	if ( NULL == Get##browserName##BrowserHistoryList(key) ) \
		return Get##browserName##BrowserBookmarkList(key)->size(); \
	return Get##browserName##BrowserBookmarkList(key)->size() + Get##browserName##BrowserHistoryList(key)->size(); \
} 

#endif