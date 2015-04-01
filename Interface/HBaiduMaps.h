#include <list>
#include <string>
#include "sqlite3.h"

#ifdef MAPDLL_API
#else
#define MAPDLL_API extern "C" _declspec(dllimport)
#endif

#include "PublicStructure.h"

MAPDLL_API BOOL BaiduMaps_Start(const wchar_t* dbPath, int sysType);

MAPDLL_API MapsBasicInfo* BaiduMaps_GetFirstMaps();
MAPDLL_API MapsBasicInfo* BaiduMaps_GetNextMaps();

MAPDLL_API void BaiduMaps_Free();