#ifndef HQQBROWSER_H
#define HQQBROWSER_H

#include "PublicStructure.h"

#ifdef QQDLL_API
#else
#define QQDLL_API extern "C" _declspec(dllimport)
#endif

QQDLL_API BOOL QQBrowser_Start(const wchar_t* dbPath, int sysType);

QQDLL_API BrowserBookmark* QQBrowser_GetFirstBookMark();
QQDLL_API BrowserBookmark* QQBrowser_GetNextBookMark();

QQDLL_API BrowserHistory* QQBrowser_GetFirstHistory();
QQDLL_API BrowserHistory* QQBrowser_GetNextHistory();

QQDLL_API void QQBrowser_Free();

#endif