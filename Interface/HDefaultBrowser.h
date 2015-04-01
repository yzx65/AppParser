#ifndef HDEFAULTBROWSER_H
#define HDEFAULTBROWSER_H

#include "PublicStructure.h"

#ifdef SelfDLL_API
#else
#define SelfDLL_API extern "C" _declspec(dllimport)
#endif

SelfDLL_API BOOL DefaultBrowser_Start(const wchar_t* dbPath, int sysType);

SelfDLL_API BrowserBookmark* DefaultBrowser_GetFirstBookMark();
SelfDLL_API BrowserBookmark* DefaultBrowser_GetNextBookMark();

SelfDLL_API BrowserHistory* DefaultBrowser_GetFirstHistory();
SelfDLL_API BrowserHistory* DefaultBrowser_GetNextHistory();

SelfDLL_API void DefaultBrowser_Free();

#endif