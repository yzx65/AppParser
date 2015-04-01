#ifndef UCPARSER_H
#define UCPARSER_H

#include "PublicStructure.h"

#ifdef UCPARSER_EXPORTS
#define UCPARSER_API __declspec(dllimport)
#else
#define UCPARSER_API __declspec(dllexport)
#endif

UCPARSER_API bool UCBrowser_Start(const wchar_t* dataPath, int systemType);

UCPARSER_API BrowserBookmark* UCBrowser_GetFirstBookMark();
UCPARSER_API BrowserBookmark* UCBrowser_GetNextBookMark();

UCPARSER_API BrowserHistory* UCBrowser_GetFirstHistory();
UCPARSER_API BrowserHistory* UCBrowser_GetNextHistory();

UCPARSER_API void UCBrowser_Free();

#endif // UCPARSER_H