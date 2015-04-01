#ifndef PUBLICSTRUCTURE_H
#define PUBLICSTRUCTURE_H

#include <string>
#include <list>

struct BrowseBasicInfo
{
	std::string time;
	std::string name;
	std::string url;
};

typedef BrowseBasicInfo BrowserHistory;
typedef BrowseBasicInfo BrowserBookmark;

typedef std::list<BrowserBookmark> BookmarkList;
typedef std::list<BrowserHistory> HistoryList;

struct MapsBasicInfo
{
	std::string                      route;
	BOOL                            isPos;
};

typedef std::list<MapsBasicInfo> MapsList;

#endif