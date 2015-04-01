/***************************************************************************
 * Module:										(BuildNum: 0003-20111109)
 *      AdkFile.h
 *
 * Author:
 *		XieBo(secman_xie@hotmail.com)
 *
 * Time:
 *		2008-10-11,Nanjing
 *
 * Notes:
 *		一些文件相关的辅助函数(当前只支持用户态)
 *
 * Functions:
 *
 *      2014-04-15
 *      AdkLockedFileWriterW(A)     - 在写入完成前，此文件不能访问
 *	    AdkFileWriteAtPointerW(A)   - 一次在某个目录更新文件内容
 *
 *		AdkGetFileExtW(A)			- 得到文件扩展名
 *		AdkGetFileNameW(A)			- 得到文件名
 *		AdkFileIsExistW(A)			- 文件是否存在
 *		AdkDeleteFileExW(A)			- 删除文件, 支持强制删除(在下次重启后删除)
 *		AdkGetFileSizeFromNameW(A)	- 通过文件名获取文件大小(只能正确返回小于4G的文件大小)
 *		AdkSynFileTimeW(A)			- 同步文件时间
 *
 *		AdkCopyFileExW(A)			- 不使用WINAPI CopyFile的拷贝函数
 *		AdkCopyFile2PathW(A)		- 将文件拷贝到一个目录中
 *		AdkPathAppendW(A)			- 添加路径 (实际上是字符串操作，只是特别处理了在路径添加中要处理的'\\')
 *
 *		AdkFileReaderW(A)			- 一次读文件
 *		AdkFileWriterW(A)			- 一次写文件
 *		AdkFileAppendWriterW(A)		- 一次追加写文件
 *
 *		AdkCreateDirectoryW(A)		- 按路径递归创建目录, 一次建多层的目录
 *
 */

#ifndef __ADK_TUOJIE_FILE_H__
#define __ADK_TUOJIE_FILE_H__

#include "AdkString.h"

#ifdef __KERNEL__
    #error "We migth support kernel mode AdkFile module,but not now!"
#endif // !__KERNEL__

// @@@@: 通过下面这个开关，可以控制来自于这个文件的调试输出信息
//
#define ADK_FILE_DBG  ADK_DBG_ON

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

#ifdef UNICODE

#define AdkGetFileExt			AdkGetFileExtW
#define AdkGetFileName			AdkGetFileNameW
#define AdkFileIsExist			AdkFileIsExistW
#define AdkDeleteFileEx			AdkDeleteFileExW
#define AdkGetFileSizeFromName	AdkGetFileSizeFromNameW
#define AdkCopyFileEx			AdkCopyFileExW
#define AdkCopyFile2Path		AdkCopyFile2PathW
#define AdkPathAppend			AdkPathAppendW
#define AdkCreateDirectory		AdkCreateDirectoryW
#define AdkFileReader			AdkFileReaderW
#define AdkFileWriter			AdkFileWriterW
#define AdkFileAppendWriter		AdkFileAppendWriterW
#define AdkLockedFileWriter     AdkLockedFileWriterW
#define AdkFileWriteAtPointer	AdkFileWriteAtPointerW
#define AdkSynFileTime			AdkSynFileTimeW

#else

#define AdkGetFileExt			AdkGetFileExtA
#define AdkGetFileName			AdkGetFileNameA
#define AdkFileIsExist			AdkFileIsExistA
#define AdkDeleteFileEx			AdkDeleteFileExA
#define AdkGetFileSizeFromName	AdkGetFileSizeFromNameA
#define AdkCopyFileEx			AdkCopyFileExA
#define AdkCopyFile2Path		AdkCopyFile2PathA
#define AdkPathAppend			AdkPathAppendA
#define AdkCreateDirectory		AdkCreateDirectoryA
#define AdkFileReader			AdkFileReaderA
#define AdkFileWriter			AdkFileWriterA
#define AdkFileAppendWriter		AdkFileAppendWriterA
#define AdkLockedFileWriter     AdkLockedFileWriterA
#define AdkFileWriteAtPointer	AdkFileWriteAtPointerA
#define AdkSynFileTime			AdkSynFileTimeA

#endif

#ifndef INVALID_FILE_ATTRIBUTES
#define INVALID_FILE_ATTRIBUTES ((DWORD)-1)
#endif

#ifndef INVALID_SET_FILE_POINTER
#define INVALID_SET_FILE_POINTER ((DWORD)-1)	
#endif

/*********************************************************************
 * AdkGetFileExtW
 *
 */
INLINE
LPWSTR WINAPI AdkGetFileExtW(IN LPCWSTR lpszFilePath)
{
	AdkASSERT((lpszFilePath));

	return AdkWcsRChr(lpszFilePath, L'.');
}

/*********************************************************************
 * AdkGetFileExtA
 *
 */
INLINE
LPSTR WINAPI AdkGetFileExtA(IN LPCSTR lpszFilePath)
{
	AdkASSERT((lpszFilePath));

	return AdkStrRChr(lpszFilePath, '.');
}

/*********************************************************************
 * AdkGetFileNameW
 *
 */
INLINE
PWCHAR WINAPI AdkGetFileNameW(IN LPCWSTR lpwzFilePath)
{
	PWCHAR lpwzFileName;

	AdkASSERT((lpwzFilePath));

	lpwzFileName = AdkWcsRChr(lpwzFilePath, L'\\');
	if (lpwzFileName)
	{
		lpwzFileName++;
	}
	else
	{
		lpwzFileName = (PWCHAR)lpwzFilePath;
	}

	return lpwzFileName;
}

/*********************************************************************
 * AdkGetFileNameA
 *
 */
INLINE
PCHAR WINAPI AdkGetFileNameA(IN LPCSTR lpszFilePath)
{
	PCHAR lpszFileName;

	AdkASSERT((lpszFilePath));

	lpszFileName = AdkStrRChr(lpszFilePath, '\\');
	if (lpszFileName)
	{
		lpszFileName++;
	}
	else
	{
		lpszFileName = (PCHAR)lpszFilePath;
	}

	return lpszFileName;
}

/*********************************************************************
 * AdkFileIsExistA
 *
 */
INLINE
BOOL WINAPI AdkFileIsExistA(IN LPCSTR lpszFile)
{
	BOOL	bExist = TRUE;
	DWORD	dwErrId;

	xASSERT((lpszFile));

	if (INVALID_FILE_ATTRIBUTES == GetFileAttributesA(lpszFile))
	{
		dwErrId = GetLastError();

		if (ERROR_FILE_NOT_FOUND == dwErrId || ERROR_PATH_NOT_FOUND == dwErrId 
		 || ERROR_INVALID_NAME == dwErrId   || ERROR_NETWORK_UNREACHABLE == dwErrId)
		{
			bExist = FALSE;
		}
	}

	return bExist;
}

/*********************************************************************
 * AdkFileIsExistW
 *
 */
INLINE
BOOL WINAPI AdkFileIsExistW(IN LPCWSTR lpwzFile)
{
	BOOL	bExist = TRUE;
	DWORD	dwErrId;

	xASSERT((lpwzFile));

	if (INVALID_FILE_ATTRIBUTES == GetFileAttributesW(lpwzFile))
	{
		dwErrId = GetLastError();

		if (ERROR_FILE_NOT_FOUND == dwErrId || ERROR_PATH_NOT_FOUND == dwErrId 
		 || ERROR_INVALID_NAME == dwErrId   || ERROR_NETWORK_UNREACHABLE == dwErrId)
		{
			bExist = FALSE;
		}
	}

	return bExist;
}

/*********************************************************************
 * AdkDeleteFileExW
 *
 */
INLINE
BOOL WINAPI AdkDeleteFileExW(IN LPCWSTR lpwzFile, IN BOOL bForce)
{
	wchar_t   wzTmpPath[MAX_PATH] ;
	wchar_t   wzTmpFile[MAX_PATH] ;
	DWORD     dwError             ;

	xASSERT((lpwzFile));

	if (DeleteFileW(lpwzFile))
	{
		return TRUE;
	}
	else
	{
		dwError  = GetLastError();
		if ( ERROR_FILE_NOT_FOUND == dwError || ERROR_PATH_NOT_FOUND == dwError )
		{
			return TRUE;
		}

		// 如果想强制删除，则需要一些技巧了
		//
		if ( bForce )
		{
			if ( 0 == GetTempPathW(MAX_PATH, wzTmpPath))			// The returned string ends with a backslash, for example, "C:\TEMP\"
			{
				return FALSE;
			}

			wsprintfW(wzTmpFile, L"%ws%u", wzTmpPath, GetTickCount());

			if (0 == MoveFileExW(lpwzFile, wzTmpFile, MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH))
			{
				MoveFileExW(wzTmpFile, NULL, MOVEFILE_DELAY_UNTIL_REBOOT);
				return TRUE;
			}
		}
	}

	return FALSE;
}

/*********************************************************************
 * AdkDeleteFileExA
 *
 */
INLINE
BOOL WINAPI AdkDeleteFileExA(IN LPCSTR lpszFile, IN BOOL bForce)
{
	BOOL	bRet = FALSE;
	PWCHAR  lpwzFile = AdkStrToWStr(lpszFile);
	if (lpwzFile)
	{
		bRet = AdkDeleteFileExW(lpwzFile, bForce);
		AdkFree(lpwzFile);
	}

	return bRet;
}

/*********************************************************************
 * AdkGetFileSizeFromNameW
 *
 */
INLINE
DWORD WINAPI AdkGetFileSizeFromNameW(IN LPCWSTR lpwzFile)
{
	WIN32_FILE_ATTRIBUTE_DATA  wfad;

	xASSERT((lpwzFile));

	if ( GetFileAttributesExW(lpwzFile, GetFileExInfoStandard, &wfad) )
	{
        return wfad.nFileSizeLow;
	}

	return 0;
}

/*********************************************************************
 * AdkGetFileSizeFromNameA
 *
 */
INLINE
DWORD WINAPI AdkGetFileSizeFromNameA(IN LPCSTR lpszFile)
{
	WIN32_FILE_ATTRIBUTE_DATA  wfad;

	xASSERT((lpszFile));

	if ( GetFileAttributesExA(lpszFile, GetFileExInfoStandard, &wfad) )
	{
		return wfad.nFileSizeLow;
	}

	return 0;
}

/*********************************************************************
 * AdkSynFileTimeW  - syn the szDest's time with szSrc's time
 *
 */
INLINE
BOOL WINAPI AdkSynFileTimeW(LPCWSTR lpwzSrcFile, LPCWSTR lpwzDstFile)
{
	BOOL	bRet = FALSE;
	HANDLE	hFileDest;
	WIN32_FILE_ATTRIBUTE_DATA	wfad;

	AdkASSERT((lpwzSrcFile));
	AdkASSERT((lpwzDstFile));

	if ( ! GetFileAttributesExW(lpwzSrcFile, GetFileExInfoStandard, &wfad))
	{
		return FALSE;
	}

	hFileDest = CreateFileW(lpwzDstFile,
							GENERIC_WRITE | GENERIC_READ,
							0,
							NULL,
							OPEN_EXISTING,
							FILE_ATTRIBUTE_NORMAL,
							NULL);

	if ( INVALID_HANDLE_VALUE == hFileDest)
	{
		return FALSE;
	}
	
	bRet = SetFileTime(hFileDest, &wfad.ftCreationTime, &wfad.ftLastAccessTime, &wfad.ftLastWriteTime); 

	CloseHandle(hFileDest);

	return bRet;
}

/* ********************************************************************
 *
 * AdkSynFileTimeA
 *
 *    syn the szDest's time with szSrc's time
 *
 */
INLINE
BOOL WINAPI AdkSynFileTimeA(PCHAR lpszSrcFile, PCHAR lpszDstFile)
{
	BOOL	bRet = FALSE;
	HANDLE	hFileDest;
	WIN32_FILE_ATTRIBUTE_DATA	wfad;

	AdkASSERT((lpszSrcFile));
	AdkASSERT((lpszDstFile));

	if ( ! GetFileAttributesExA(lpszSrcFile, GetFileExInfoStandard, &wfad))
	{
		return FALSE;
	}

	hFileDest = CreateFileA(lpszDstFile,
							GENERIC_WRITE | GENERIC_READ,
							0,
							NULL,
							OPEN_EXISTING,
							FILE_ATTRIBUTE_NORMAL,
							NULL);

	if ( INVALID_HANDLE_VALUE == hFileDest)
	{
		return FALSE;
	}
	
	bRet = SetFileTime(hFileDest, &wfad.ftCreationTime, &wfad.ftLastAccessTime, &wfad.ftLastWriteTime); 
	CloseHandle(hFileDest);

	return bRet;
}

/**************************************************************
 *	AdkPathAppendA
 *
 */
INLINE
LPSTR WINAPI AdkPathAppendA(LPSTR lpszPath, LPCSTR lpszMore)
{
	xASSERT((lpszPath));
	xASSERT((lpszMore));

	if (lpszPath[AdkStrLen(lpszPath) - 1] == '\\')
	{
		return lstrcatA(lpszPath, lpszMore);
	}

	lstrcatA(lpszPath, "\\");

	return lstrcatA(lpszPath, lpszMore);
}

/**************************************************************
 *	AdkPathAppendW
 *
 */
INLINE
LPWSTR WINAPI AdkPathAppendW(LPWSTR lpwzPath, LPCWSTR lpwzMore)
{
	xASSERT((lpwzPath));
	xASSERT((lpwzMore));

	if (lpwzPath[AdkWcsLen(lpwzPath) - 1] == L'\\')
	{
		return lstrcatW(lpwzPath, lpwzMore);
	}

	lstrcatW(lpwzPath, L"\\");

	return lstrcatW(lpwzPath, lpwzMore);
}

/*********************************************************************
 * AdkCopyFileExW    -  不使用CopyFile、CopyFileEx等API进行拷贝
 *
 */
INLINE
BOOL WINAPI AdkCopyFileExW(LPCWSTR	lpwzSrcFile, 
						   LPCWSTR	lpwzDestFile, 
						   BOOL		bFailIfExists)
{
	BOOL	bRet		= FALSE;
	HANDLE	hDstFile	= INVALID_HANDLE_VALUE;
	HANDLE	hSrcFile	= INVALID_HANDLE_VALUE;
	PBYTE	lpbyData	= NULL;
	DWORD	dwDataLen	= 64 * 1024;		// 一次读取64K
	DWORD	dwByteReaded;
	DWORD	dwByteWritten;
	PBYTE   lpDelta     = NULL;
	DWORD   dwFileAttri ;

	AdkASSERT(lpwzSrcFile);
	AdkASSERT(lpwzDestFile);

	do
	{
		hSrcFile = CreateFileW(lpwzSrcFile,
							   GENERIC_READ,
							   FILE_SHARE_READ | FILE_SHARE_WRITE,
							   NULL,
							   OPEN_EXISTING,
							   0,
							   NULL);

		if ( INVALID_HANDLE_VALUE == hSrcFile )
		{
			break;
		}

		dwFileAttri = GetFileAttributesW(lpwzDestFile);
		if (dwFileAttri != INVALID_FILE_ATTRIBUTES)
		{
			if (bFailIfExists)
			{
				// 文件存在则退出
				//
				break;
			}
			else
			{
				dwFileAttri &= ~FILE_ATTRIBUTE_READONLY;
				dwFileAttri &= ~FILE_ATTRIBUTE_SYSTEM;
				SetFileAttributesW(lpwzDestFile, dwFileAttri);
			}
		}

		hDstFile = CreateFileW(lpwzDestFile,
							   GENERIC_READ | GENERIC_WRITE, 
							   FILE_SHARE_READ | FILE_SHARE_WRITE,
							   NULL, 
							   OPEN_EXISTING,
							   0,
							   NULL);

		if ( bFailIfExists && (INVALID_HANDLE_VALUE != hDstFile) )
		{
			// 已存在
			//
			break;
		}

		if ( (INVALID_HANDLE_VALUE == hDstFile) && ( ERROR_FILE_NOT_FOUND == GetLastError()) )
		{
			hDstFile = CreateFileW(lpwzDestFile,
									GENERIC_READ | GENERIC_WRITE,
									FILE_SHARE_READ | FILE_SHARE_WRITE,
									NULL,
									CREATE_ALWAYS,
									0,
									NULL);

			if ( INVALID_HANDLE_VALUE == hDstFile )
			{
				break;
			}
		}

		lpbyData = (PBYTE)AdkMalloc(dwDataLen);
		if ( !lpbyData )
		{
			break;
		}

		while( TRUE )
		{
			bRet = ReadFile(hSrcFile, lpbyData, dwDataLen, &dwByteReaded, NULL);
			if ( !bRet || (0 == dwByteReaded) )
			{
				break;
			}

			bRet = WriteFile(hDstFile, lpbyData, dwByteReaded, &dwByteWritten, NULL);
			if ( !bRet )
			{
				break;
			}
		}

		SetEndOfFile(hDstFile);

	} while(FALSE);

	if ( INVALID_HANDLE_VALUE != hDstFile )
	{
		CloseHandle(hDstFile);
	}

	if ( INVALID_HANDLE_VALUE != hSrcFile )
	{
		CloseHandle(hSrcFile);
	}

	if ( lpbyData )
	{
		AdkFree(lpbyData);
	}

	return bRet;
}


/*********************************************************************
 * AdkCopyFileExA    -  不使用CopyFile、CopyFileEx等API进行拷贝
 *
 */
INLINE
BOOL WINAPI AdkCopyFileExA(LPCSTR	lpszSrcFile, 
						   LPCSTR	lpszDstFile, 
						   BOOL		bFailIfExists)
{
	BOOL	bRet = FALSE;
	PWCHAR	lpwzSrcFile = AdkStrToWStr(lpszSrcFile);
	PWCHAR	lpwzDstFile = AdkStrToWStr(lpszDstFile);

	if (lpwzSrcFile && lpwzDstFile)
	{
		bRet = AdkCopyFileExW(lpwzSrcFile, lpwzDstFile, bFailIfExists);
	}

	if (lpwzSrcFile)
	{
		AdkFree(lpwzSrcFile);
	}

	if (lpwzDstFile)
	{
		AdkFree(lpwzDstFile);
	}

	return bRet;
}

/*********************************************************************
 * AdkCopyFile2PathW
 *
 */
INLINE
BOOL WINAPI AdkCopyFile2PathW(LPCWSTR	lpSrcFile, 
							  LPCWSTR	lpDestDir, 
							  BOOL		bFailIfExist)
{
	BOOL	bRet       ;
	PWCHAR	lpDestFile ;
	PWCHAR  lpFileName ;
	INT     iLen       ;

	xASSERT(lpSrcFile);
	xASSERT(lpDestDir);

	if ( 0 == AdkWcsLen(lpSrcFile) || 0 == AdkWcsLen(lpDestDir) )
	{
		return FALSE;
	}

	lpFileName = AdkGetFileNameW(lpSrcFile);
	if (NULL == lpFileName)
	{
		return FALSE;
	}

	iLen = AdkWcsLen(lpDestDir) + AdkWcsLen(lpFileName) + 4;
	lpDestFile = (PWCHAR)AdkMalloc(iLen);
	if ( NULL == lpDestFile)
	{
		return FALSE;
	}

	AdkWcsCpy(lpDestFile, lpDestDir);
	AdkPathAppendW(lpDestFile, lpFileName);

	bRet = CopyFileW(lpSrcFile, lpDestFile, bFailIfExist);

	AdkFree(lpDestFile);

	return bRet;
}

/*********************************************************************
 * AdkCopyFile2PathA
 *
 *
 */
INLINE
BOOL WINAPI AdkCopyFile2PathA(LPCSTR	lpszSrcFile, 
							  LPCSTR	lpszDstDir, 
							  BOOL		bFailIfExist)
{
	BOOL	bRet = FALSE;
	PWCHAR	lpwzSrcFile;
	PWCHAR	lpwzDstDir;

	AdkASSERT((lpszSrcFile));
	AdkASSERT((lpszDstDir));

	lpwzSrcFile = AdkStrToWStr(lpszSrcFile);
	lpwzDstDir  = AdkStrToWStr(lpszDstDir);
	
	if (lpwzSrcFile && lpwzDstDir)
	{
		bRet = AdkCopyFile2PathW(lpwzSrcFile, lpwzDstDir, bFailIfExist);
	}

	if (lpwzSrcFile)
	{
		AdkFree(lpwzSrcFile);
	}

	if (lpwzDstDir)
	{
		AdkFree(lpwzDstDir);
	}

	return bRet;
}

/*********************************************************************
 * AdkCreateDirectoryW
 *
 * 参数：
 *		lpwzDir 的结尾必须包含'\\', 如 "C:\test\test\"
 *
 */
INLINE
BOOL WINAPI AdkCreateDirectoryW(IN LPCWSTR lpwzDir)
{
	BOOL    bRet    = TRUE;
	PWCHAR	lpwzTemp  ;
	DWORD   dwLen   ;
	DWORD	dwCur = 0;

	xASSERT((lpwzDir));

	dwLen  = AdkWcsLen(lpwzDir) + 1;
	lpwzTemp = (PWCHAR)AdkMalloc(dwLen * sizeof(WCHAR));
	if ( NULL == lpwzTemp )
	{
		return FALSE;
	}

	for (; dwCur < dwLen; dwCur++)
	{
		if ( L'\\' == lpwzDir[dwCur] )
		{
			if ( 2 < AdkWcsLen(lpwzTemp) && ! CreateDirectoryW(lpwzTemp, NULL))
			{
                if ( ERROR_ALREADY_EXISTS != GetLastError() )
                {
                    bRet = FALSE;
                    break;
				}
			}
		}

        lpwzTemp[dwCur] = lpwzDir[dwCur];

		if ( L'\0' == lpwzDir[dwCur] )
		{
            break;
		}
	}

	AdkFree(lpwzTemp);

	return bRet;
}

/*********************************************************************
 * AdkCreateDirectoryA
 *
 * 参数：
 *		lpwzDir 的结尾必须包含'\\', 如 "C:\test\test\"
 *
 */
INLINE
BOOL WINAPI AdkCreateDirectoryA(IN LPCSTR lpszDir)
{
	BOOL	bRet = FALSE;
	PWCHAR  lpwzDir = AdkStrToWStr(lpszDir);

	if (lpwzDir)
	{
		bRet = AdkCreateDirectoryW(lpwzDir);
		AdkFree(lpwzDir);
	}

	return bRet;
}

/*********************************************************************
 * AdkFileReaderW
 * 
 */
INLINE
BOOL WINAPI AdkFileReaderW(IN LPCWSTR		lpwzFile, 
						   IN DWORD			nNumberOfBytesToRead, 
						   IN OUT LPDWORD	lpdwByteRead, 
						   IN LPVOID		lpBuffer, 
						   IN DWORD			dwBufLen)
{
	HANDLE   hFile = INVALID_HANDLE_VALUE;
	BOOL     bRet  = FALSE;

	xASSERT((lpwzFile));
	xASSERT((lpBuffer));
	xASSERT((nNumberOfBytesToRead <= dwBufLen));

	if ( nNumberOfBytesToRead > dwBufLen )
	{
		::SetLastError(ERROR_DS_USER_BUFFER_TO_SMALL);
		xTRACEExW(ADK_FILE_DBG, (L"AdkFileReaderW nNumberOfBytesToRead > dwBufLen\r\n"));
		return FALSE;
	}

	do
	{
		hFile = CreateFileW(lpwzFile,
							GENERIC_READ,
							FILE_SHARE_READ | FILE_SHARE_WRITE,
							NULL,
							OPEN_EXISTING,
							0,
							NULL);

		if ( INVALID_HANDLE_VALUE == hFile )
		{
			xTRACEExW(ADK_FILE_DBG, (L"AdkFileReaderW CreateFileW failed with %u\r\n", GetLastError()));
			break;
		}

		bRet = ReadFile(hFile, lpBuffer, nNumberOfBytesToRead, lpdwByteRead, NULL);

	} while(FALSE);

	if ( INVALID_HANDLE_VALUE != hFile )
	{
		CloseHandle(hFile);
	}

	return bRet;
}

/*********************************************************************
 * AdkFileReaderA
 *
 */
INLINE
BOOL WINAPI AdkFileReaderA(IN LPCSTR		lpszFile, 
						   IN DWORD			nNumberOfBytesToRead, 
						   IN OUT LPDWORD	lpdwByteRead, 
						   IN LPVOID		lpBuffer, 
						   IN DWORD			dwBufLen)
{
	BOOL	bRet = FALSE;
	PWCHAR  lpwzFile = AdkStrToWStr(lpszFile);
	if (lpwzFile)
	{
		bRet = AdkFileReaderW(lpwzFile,
			 				  nNumberOfBytesToRead,
							  lpdwByteRead,
							  lpBuffer,
							  dwBufLen);

		AdkFree(lpwzFile);
	}

	return bRet;
}


/*********************************************************************
 * AdkLockedFileWriterW
 *
 */
INLINE
BOOL WINAPI AdkLockedFileWriterW(IN LPCWSTR	lpwzFileName, 
						   IN LPVOID	lpBuffer, 
						   IN DWORD		dwBufLen)
{
	BOOL   bRet    = FALSE;
	HANDLE hFile   = INVALID_HANDLE_VALUE;
	DWORD  dwByteWritten ;

	AdkASSERT((lpwzFileName));
	AdkASSERT((lpBuffer));

	do
	{
		hFile = CreateFileW(lpwzFileName,
							GENERIC_READ | GENERIC_WRITE,
							0,
							NULL,
							CREATE_ALWAYS,
							0,			
							NULL);

		if ( INVALID_HANDLE_VALUE == hFile )
		{
			xTRACEExW(ADK_FILE_DBG, (L"AdkLockedFileWriterW CreateFileW failed with %u\r\n", GetLastError()));
			break;
		}

		if ( !WriteFile(hFile, lpBuffer, dwBufLen, &dwByteWritten, NULL) )
		{
			xTRACEExW(ADK_FILE_DBG, (L"AdkLockedFileWriterW WriteFile failed with %u\r\n", GetLastError()));
			break;
		}

		if ( dwByteWritten != dwBufLen )
		{
			xTRACEExW(ADK_FILE_DBG, (L"AdkLockedFileWriterW dwByteWritten != dwBufLen\r\n"));
			break;
		}

		bRet = TRUE;

	} while (FALSE);

	if ( INVALID_HANDLE_VALUE != hFile )
	{
		CloseHandle(hFile);
	}

	return bRet;
}

/*********************************************************************
 * AdkLockedFileWriterA
 *
 */
INLINE
BOOL WINAPI AdkLockedFileWriterA(IN LPCSTR	lpszFileName, 
						   IN LPVOID	lpBuffer, 
						   IN DWORD		dwBufLen)
{
	BOOL	bRet = FALSE;
	PWCHAR	lpwzFileName = AdkStrToWStr(lpszFileName);
	if (lpwzFileName)
	{
		bRet = AdkLockedFileWriterW(lpwzFileName, lpBuffer, dwBufLen);
		AdkFree(lpwzFileName);
	}

	return bRet;
}

/*********************************************************************
 * AdkFileWriteAtPointerW
 *
 */
INLINE
BOOL WINAPI AdkFileWriteAtPointerW(IN LPCWSTR	lpwzFileName, 
								   IN LPVOID	lpBuffer, 
								   IN DWORD		dwBufLen,
							       IN LONG		lDistanceToMove,
								   IN PLONG		lpDistanceToMoveHigh,
								   IN DWORD		dwMoveMethod)
{
	BOOL	bRet    = FALSE;
	HANDLE	hFile   = INVALID_HANDLE_VALUE;
	DWORD	dwByteWritten;

	xASSERT((lpwzFileName));
	xASSERT((lpBuffer));

	do
	{
		hFile = CreateFileW(lpwzFileName, 
							GENERIC_READ | GENERIC_WRITE,
							FILE_SHARE_READ,
							NULL,
							OPEN_EXISTING, 
							FILE_ATTRIBUTE_NORMAL,
							NULL);

		if (INVALID_HANDLE_VALUE == hFile)
		{
			break;
		}

		if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, lDistanceToMove, lpDistanceToMoveHigh, dwMoveMethod))
		{
			break;
		}

		if ( ! WriteFile(hFile, lpBuffer, dwBufLen, &dwByteWritten, NULL))
		{
			break;
		}

		bRet = TRUE;

	} while(FALSE);

	if (hFile != INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFile);
	}

	return bRet;
}

/*********************************************************************
 * AdkFileWriteAtPointerA
 *
 */
INLINE
BOOL WINAPI AdkFileWriteAtPointerA(IN LPCSTR	lpszFileName, 
								   IN LPVOID	lpBuffer, 
								   IN DWORD		dwBufLen,
							       IN LONG		lDistanceToMove,
								   IN PLONG		lpDistanceToMoveHigh,
								   IN DWORD		dwMoveMethod)
{
	BOOL	bRet = FALSE;
	PWCHAR	lpwzFileName = AdkStrToWStr(lpszFileName);
	if (lpwzFileName)
	{
		bRet = AdkFileWriteAtPointerW(lpwzFileName, 
									  lpBuffer, 
									  dwBufLen,
									  lDistanceToMove,
									  lpDistanceToMoveHigh,
									  dwMoveMethod);
		AdkFree(lpwzFileName);
	}

	return bRet;
}

/*********************************************************************
 * AdkFileWriterW
 *
 */
INLINE
BOOL WINAPI AdkFileWriterW(IN LPCWSTR	lpwzFileName, 
						   IN LPVOID	lpBuffer, 
						   IN DWORD		dwBufLen)
{
	BOOL   bRet    = FALSE;
	HANDLE hFile   = INVALID_HANDLE_VALUE;
	DWORD  dwByteWritten ;

	AdkASSERT((lpwzFileName));
	AdkASSERT((lpBuffer));

	do
	{
		hFile = CreateFileW(lpwzFileName,
							GENERIC_READ | GENERIC_WRITE,
							FILE_SHARE_READ,
							NULL,
							CREATE_ALWAYS,
							0,			
							NULL);

		if ( INVALID_HANDLE_VALUE == hFile )
		{
			xTRACEExW(ADK_FILE_DBG, (L"AdkFileWriterW CreateFileW failed with %u\r\n", GetLastError()));
			break;
		}

		if ( !WriteFile(hFile, lpBuffer, dwBufLen, &dwByteWritten, NULL) )
		{
			xTRACEExW(ADK_FILE_DBG, (L"AdkFileWriterW WriteFile failed with %u\r\n", GetLastError()));
			break;
		}

		if ( dwByteWritten != dwBufLen )
		{
			xTRACEExW(ADK_FILE_DBG, (L"AdkFileWriterW dwByteWritten != dwBufLen\r\n"));
			break;
		}

		bRet = TRUE;

	} while (FALSE);

	if ( INVALID_HANDLE_VALUE != hFile )
	{
		CloseHandle(hFile);
	}

	return bRet;
}

/*********************************************************************
 * AdkFileWriterA
 *
 */
INLINE
BOOL WINAPI AdkFileWriterA(IN LPCSTR	lpszFileName, 
						   IN LPVOID	lpBuffer, 
						   IN DWORD		dwBufLen)
{
	BOOL	bRet = FALSE;
	PWCHAR	lpwzFileName = AdkStrToWStr(lpszFileName);
	if (lpwzFileName)
	{
		bRet = AdkFileWriterW(lpwzFileName, lpBuffer, dwBufLen);
		AdkFree(lpwzFileName);
	}

	return bRet;
}

/*********************************************************************
 * AdkFileAppendWriterW
 *
 */
INLINE
BOOL WINAPI AdkFileAppendWriterW(IN LPCWSTR lpwzFileName, 
								 IN LPVOID	lpBuffer, 
								 IN DWORD	dwBufLen)
{
	BOOL   bRet    = FALSE;
	HANDLE hFile   = INVALID_HANDLE_VALUE;
	DWORD  dwByteWritten ;

	xASSERT((lpwzFileName));
	xASSERT((lpBuffer));

	do
	{
		hFile = CreateFileW(lpwzFileName,
							GENERIC_READ | GENERIC_WRITE,
							FILE_SHARE_READ,
							NULL,
							OPEN_ALWAYS,
							0,
							NULL);

		if ( INVALID_HANDLE_VALUE == hFile )
		{
			xERRORExW(ADK_FILE_DBG, (L"AdkFileAppendWriterW %u %ws\r\n", GetLastError(), lpwzFileName));
			break;
		}

		SetFilePointer(hFile, 0, NULL, FILE_END);

		if ( !WriteFile(hFile, lpBuffer, dwBufLen, &dwByteWritten, NULL) )
		{
			xERRORExW(ADK_FILE_DBG, (L"AdkFileAppendWriterW %u\r\n", GetLastError()));
			break;
		}

		if ( dwByteWritten != dwBufLen )
		{
			break;
		}

		bRet = TRUE;

	} while (FALSE);

	if ( INVALID_HANDLE_VALUE != hFile )
	{
		CloseHandle(hFile);
	}

	return bRet;
}

/*********************************************************************
 * AdkFileAppendWriterA
 *
 */
INLINE
BOOL WINAPI AdkFileAppendWriterA(IN LPCSTR	lpszFileName, 
								 IN LPVOID	lpBuffer, 
								 IN DWORD	dwBufLen)
{
	BOOL	bRet = FALSE;
	PWCHAR	lpwzFileName = AdkStrToWStr(lpszFileName);
	if (lpwzFileName)
	{
		bRet = AdkFileAppendWriterW(lpwzFileName, lpBuffer, dwBufLen);
		AdkFree(lpwzFileName);
	}

	return bRet;
}

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ! __ADK_TUOJIE_FILE_H__

/*
 * Revision:
 *
 *		3. 更正AdkGetFileNameW(A),当参数中没有\时，即可能参数就是文件名，原来策略是返回NULL，现在是返回文件名		(BuildNum: 0003-20111109)
 *
 *		2. dzkad: 整合进ADK库					(BuildNum: 0002-20100914)
 *
 *		1. xieb: clean up the older xFile.hxx   (BuildNum: 0001-20081011)
 *
 *****************************************************************************/