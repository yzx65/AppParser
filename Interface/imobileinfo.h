#ifndef IMOBILE_INFO_H
#define IMOBILE_INFO_H

#define IMOBILE_API extern "C" _declspec(dllexport) 

IMOBILE_API  DWORD WINAPI ListIosDevice(char **ppszList, DWORD dwMaxCount);
IMOBILE_API  BOOL WINAPI InstallApp(char *lpszDevId, LPWSTR lpwzFilePath);
IMOBILE_API  BOOL WINAPI ImportAppData(char *lpszDevId, char *lpszAppId, LPWSTR lpwzSrc);

//list cydia installed app list /var/lib/dpkg/status

typedef void (WINAPI *LPFNUPDATERATE)(double dRate);

IMOBILE_API  BOOL WINAPI RestoreFromBackup(char				*lpszSrcId,
										   char				*lpszDstId,
										   LPWSTR			lpwzRootPath,
										   char				*lpszPassword,
										   LPFNUPDATERATE   lpfnUpdateRate);

IMOBILE_API  BOOL WINAPI IsAppInstalled(char *lpszDevId, char *lpszAppID);

#endif
