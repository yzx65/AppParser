#ifndef SafariBrowser_H
#define SafariBrowser_H

#include "PublicStructure.h"

#ifdef SafariBrowser_EXPORTS
#define SafariBrowser_API __declspec(dllimport)
#else
#define SafariBrowser_API __declspec(dllexport)
#endif

SafariBrowser_API bool SafariBrowser_Start(const wchar_t* dataPath, int systemType);

SafariBrowser_API BrowserBookmark* SafariBrowser_GetFirstBookMark();
SafariBrowser_API BrowserBookmark* SafariBrowser_GetNextBookMark();

SafariBrowser_API BrowserHistory* SafariBrowser_GetFirstHistory();
SafariBrowser_API BrowserHistory* SafariBrowser_GetNextHistory();

SafariBrowser_API void SafariBrowser_Free();

#endif // Safari_H