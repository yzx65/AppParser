#ifndef HBAIDUBROWSER_H
#define HBAIDUBROWSER_H

#include "PublicStructure.h"

#ifdef BAIDUDLL_API
#else
#define BAIDUDLL_API extern "C" _declspec(dllimport)
#endif

BAIDUDLL_API BOOL BaiduBrowser_Start(const wchar_t* dbPath, int sysType);

BAIDUDLL_API BrowserBookmark* BaiduBrowser_GetFirstBookMark();
BAIDUDLL_API BrowserBookmark* BaiduBrowser_GetNextBookMark();

BAIDUDLL_API BrowserHistory* BaiduBrowser_GetFirstHistory();
BAIDUDLL_API BrowserHistory* BaiduBrowser_GetNextHistory();

BAIDUDLL_API void BaiduBrowser_Free();

#endif