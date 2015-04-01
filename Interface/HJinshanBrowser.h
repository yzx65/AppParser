#ifndef HJINSHANBROWSER_H
#define HJINSHANBROWSER_H

#include "PublicStructure.h"

#ifdef JinShanDLL_API
#else
#define JinShanDLL_API extern "C" _declspec(dllimport)
#endif

JinShanDLL_API BOOL JinShanBrowser_Start(const wchar_t* dbPath, int sysType);

JinShanDLL_API BrowserBookmark* JinShanBrowser_GetFirstBookMark();
JinShanDLL_API BrowserBookmark* JinShanBrowser_GetNextBookMark();

JinShanDLL_API BrowserHistory* JinShanBrowser_GetFirstHistory();
JinShanDLL_API BrowserHistory* JinShanBrowser_GetNextHistory();

JinShanDLL_API void JinShanBrowser_Free();

#endif