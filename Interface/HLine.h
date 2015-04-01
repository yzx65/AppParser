#ifndef HLINE_H
#define HLINE_H

#ifdef LINEDLL_API
#else
#define LINEDLL_API extern "C" _declspec(dllimport)
#endif

#include <map>

struct LineBasicInfo
{
	std::string                      time;
	std::string                      name;
	std::string                      content;
	BOOL							isSend;
};

LINEDLL_API BOOL Line_Start(const wchar_t* dbPath, int systemType);
LINEDLL_API LineBasicInfo* Line_GetFirst();
LINEDLL_API LineBasicInfo* Line_GetNext();

LINEDLL_API void Line_Free();

// Key : friend name
typedef std::multimap<std::string, LineBasicInfo> LineInfoMap;

#endif