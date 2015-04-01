#include <list>
#include <string>
#include "sqlite3.h"

#ifdef MAPDLL_API
#else
#define MAPDLL_API extern "C" _declspec(dllimport)
#endif

#include "PublicStructure.h"


MAPDLL_API BOOL GaodeMaps_Start(const wchar_t* dbPath, int sysType);

MAPDLL_API MapsBasicInfo* GaodeMaps_GetFirstMaps();
MAPDLL_API MapsBasicInfo* GaodeMaps_GetNextMaps();

MAPDLL_API void GaodeMaps_Free();