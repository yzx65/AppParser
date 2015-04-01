/***************************************************************************
 * Module:											(BuildNum:0002-20110711)
 *       AdkLnk.h
 *
 * Author:
 *		DING ZHAOKUN(dzkad@hotmail.com)
 *
 * Time:
 *		2007-12-28,Nanjing
 *
 * Notes:
 *		PE文件操作
 *
 * Functions:
 *
 *      AdkCreateLnkW(A)            - 创建快捷方式
 *		AdkGetLinkPathW(A)		    - 获取快捷方式的信息
 *      AdkSetLinkPathW(A)          - 修改快捷方式
 *
 *
 */

#pragma once

#ifndef _ADK_TUOJIE_LNK_H_
#define _ADK_TUOJIE_LNK_H_

#include "AdkPrecomp.h"
#include <Objbase.h>
#include <comdef.h>
#include <comutil.h>
#include <shlobj.h>

#ifdef _UNICODE

#define AdkCreateLink	AdkCreateLinkW
#define AdkGetLinkPath	AdkGetLinkPathW
#define AdkSetLinkPath	AdkSetLinkPathW

#else

#define AdkCreateLink	AdkCreateLinkA
#define AdkGetLinkPath	AdkGetLinkPathA
#define AdkSetLinkPath	AdkSetLinkPathA

#endif

/****************************************************************************
 * AdkCreateLnkA
 *
 */
INLINE
BOOL WINAPI AdkCreateLnkA(IN LPSTR		lpszLinkPath,
						  IN LPSTR		lpszFile,
						  IN LPSTR		lpszArguments = NULL,
						  IN LPSTR		lpszIconLocation = NULL,
						  IN INT		iIcon = 0)
{
	BOOL			bRet = FALSE;
	CHAR			szFileDir[MAX_PATH];
	IShellLinkA		*pLink = NULL;				// IShellLinkW对应的接口直接使用UNICODE
	IPersistFile	*ppf = NULL;
	PWCHAR			lpwzFilePath;

	xASSERT((lpszLinkPath));
	xASSERT((lpszFile));

	CoInitialize(NULL);

	do
	{
		if (S_OK != CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLinkA, (void **)&pLink))
		{
			break;
		}

		if (S_OK != pLink->SetPath(lpszFile))
		{
			break;
		}

		AdkStrCpy(szFileDir, lpszFile);
		szFileDir[2] = '\0';

		pLink->SetWorkingDirectory(szFileDir);
		pLink->SetShowCmd(SW_SHOW);

		if (lpszArguments)
		{
            if (S_OK != pLink->SetArguments(lpszArguments))
			{
				break;
			}
		}

		if (lpszIconLocation)
		{
			if (S_OK != pLink->SetIconLocation(lpszIconLocation, iIcon))
			{
				break;
			}
		}

		if (S_OK != pLink->QueryInterface(IID_IPersistFile, (void **)&ppf))
		{
			break;
		}

		lpwzFilePath = AdkStrToWStr(lpszLinkPath);
		if (lpwzFilePath)
		{
			if (S_OK == ppf->Save(lpwzFilePath, TRUE))
			{
				bRet = true;;
			}

			AdkFree(lpwzFilePath);
		}

	} while (FALSE);

	if (ppf)
	{
		ppf->Release();
	}

	if (pLink)
	{
		pLink->Release();
	}

	CoUninitialize();

	return bRet;
}

/****************************************************************************
 * AdkCreateLnkW
 *
 */
INLINE
BOOL WINAPI AdkCreateLnkW(IN LPWSTR		lpwzLinkPath,
						  IN LPWSTR		lpwzFile,
						  IN LPWSTR		lpwzArguments = NULL,
						  IN LPWSTR		lpwzIconLocation = NULL,
						  IN INT		iIcon = 0)
{
	BOOL			bRet = FALSE;
	WCHAR			wzFileDir[MAX_PATH];
	IShellLinkW		*pLink	= NULL;				// IShellLinkW对应的接口直接使用UNICODE
	IPersistFile	*ppf	= NULL;

	xASSERT((lpwzLinkPath));
	xASSERT((lpwzFile));

	CoInitialize(NULL);

	do
	{
		if (S_OK != CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLinkW, (void **)&pLink))
		{
			break;
		}

		if (S_OK != pLink->SetPath(lpwzFile))
		{
			break;
		}

		AdkWcsCpy(wzFileDir, lpwzFile);
		wzFileDir[2] = L'\0';

		pLink->SetWorkingDirectory(wzFileDir);
		pLink->SetShowCmd(SW_SHOW);

		if (lpwzArguments)
		{
            if (S_OK != pLink->SetArguments(lpwzArguments))
			{
				break;
			}
		}

		if (lpwzIconLocation)
		{
			if (S_OK != pLink->SetIconLocation(lpwzIconLocation, iIcon))
			{
				break;
			}
		}

		if (S_OK != pLink->QueryInterface(IID_IPersistFile, (void **)&ppf))
		{
			break;
		}

		if (S_OK == ppf->Save((LPCOLESTR)lpwzLinkPath, TRUE))
		{
			bRet = TRUE;
		}

	} while (FALSE);

	if (ppf)
	{
		ppf->Release();
	}

	if (pLink)
	{
		pLink->Release();
	}

	CoUninitialize();

	return bRet;
}

/****************************************************************************
 * AdkGetLinkPathA
 *
 *	- 参数lpszPath		- 需要调用者提供
 *	- 参数dwPathBufLen  - 指字符长度
 *
 */
INLINE
BOOL WINAPI AdkGetLinkPathA(HWND	hWnd,
							PCSTR	lpszLinkPath,
							PSTR	lpszPathBuffer,
							DWORD	dwPathBufLen)
{
	BOOL				bRet = FALSE;
	WIN32_FIND_DATAA	wfd;
    IShellLinkA			*pShLink = NULL;
	IPersistFile		*ppf = NULL;
	PWCHAR				lpwzLinkPath = NULL;

	xASSERT((lpszLinkPath));
	xASSERT((lpszPathBuffer));

	// Call CoCreateInstance to obtain the IShellLink Interface pointer. 
	//
	CoInitialize(NULL);

	do
	{
		if (S_OK != CoCreateInstance(CLSID_ShellLink,
								NULL,
								CLSCTX_INPROC_SERVER,
								IID_IShellLinkA,
                                (LPVOID *)&pShLink ))
		{
			break;
		}

        // The IShellLink Interface supports the IPersistFile
        // interface. Get an interface pointer to it.
        
        if (S_OK != pShLink->QueryInterface(IID_IPersistFile, (LPVOID *)&ppf ))
		{
			break;
		}
        
        // Load the file.
		//
		lpwzLinkPath = AdkStrToWStr(lpszLinkPath);
		if (lpwzLinkPath == NULL)
		{
			break;
		}

        if (S_OK != ppf->Load(lpwzLinkPath, STGM_READ))
		{
			break;
		}

        // Resolve the link by calling the Resolve() interface function.
        // This enables us to find the file the link points to even if
        // it has been moved or renamed.
		//
        if ( S_OK != pShLink->Resolve(hWnd, SLR_ANY_MATCH | SLR_NO_UI))
		{
			break;
		}

		// Get the path of the file the link points to.
		//
        if (S_OK == pShLink->GetPath(lpszPathBuffer,
									 dwPathBufLen,
									 &wfd,
									 SLGP_SHORTPATH))
		{
			bRet = TRUE;
        }

	} while(FALSE);

	if (ppf)
	{
		ppf->Release();
	}

    if (pShLink)
	{
        pShLink->Release();
	}

	if (lpwzLinkPath)
	{
		AdkFree(lpwzLinkPath);
	}

    CoUninitialize();

    return bRet;
}

/****************************************************************************
 * AdkGetLinkPathW
 *
 *	- 参数lpwzPath		- 需要调用者提供
 *	- 参数dwPathBufLen  - 指字符长度
 *
 */
INLINE
BOOL WINAPI AdkGetLinkPathW(HWND		hWnd,
							PCWSTR		lpwzLinkPath,
							PWSTR		lpwzPathBuffer,
							DWORD		dwPathBufLen)
{
	BOOL				bRet = FALSE;
	WIN32_FIND_DATAW	wfd;
    IShellLinkW			*pShLink = NULL;
	IPersistFile		*ppf = NULL;

	xASSERT((lpwzLinkPath));
	xASSERT((lpwzPathBuffer));

	// Call CoCreateInstance to obtain the IShellLink Interface pointer. 
	//
	CoInitialize(NULL);

	do
	{
		if (S_OK != CoCreateInstance(CLSID_ShellLink,
									 NULL,
									 CLSCTX_INPROC_SERVER,
									 IID_IShellLinkW,
									 (LPVOID *)&pShLink ))
		{
			break;
		}

        // The IShellLink Interface supports the IPersistFile
        // interface. Get an interface pointer to it.
        
        if (S_OK != pShLink->QueryInterface(IID_IPersistFile, (LPVOID *)&ppf ))
		{
			break;
		}
        
        // Load the file.
		//
        if (S_OK != ppf->Load(lpwzLinkPath, STGM_READ))
		{
			break;
		}

        // Resolve the link by calling the Resolve() interface function.
        // This enables us to find the file the link points to even if
        // it has been moved or renamed.
		//
        if ( S_OK != pShLink->Resolve(hWnd, SLR_ANY_MATCH | SLR_NO_UI))
		{
			break;
		}

		// Get the path of the file the link points to.
		//
        if (S_OK == pShLink->GetPath(lpwzPathBuffer,
									 dwPathBufLen,
									 &wfd,
									 SLGP_SHORTPATH))
		{
			bRet = TRUE;
        }

	} while(FALSE);

	if (ppf)
	{
		ppf->Release();
	}

    if (pShLink)
	{
        pShLink->Release();
	}

    CoUninitialize();

    return bRet;
}

/****************************************************************************
 * AdkSetLinkPathA
 *
 *	- 参数lpszLinkPath			- 快捷方式
 *	- 参数lpszPathBuffer		- 快捷方式指向的文件名
 *
 */
INLINE
BOOL WINAPI AdkSetLinkPathA(IN HWND		hWnd,
							IN PSTR		lpszLinkPath,
							IN PSTR		lpszPathBuffer)
{
	BOOL			bRet     = FALSE;
	IShellLinkA		*pShLink = NULL;
	IPersistFile	*ppf     = NULL;
	PWCHAR			lpwzLinkPath = NULL;

	xASSERT((lpszLinkPath));
	xASSERT((lpszPathBuffer));

	// Call CoCreateInstance to obtain the IShellLink Interface pointer. 
	//
	CoInitialize(NULL);

	do
	{
		if (S_OK != CoCreateInstance(CLSID_ShellLink,
									 NULL,
									 CLSCTX_INPROC_SERVER,
									 IID_IShellLinkA,
									 (LPVOID *)&pShLink ))
		{
			break;
		}

		// The IShellLink Interface supports the IPersistFile
		// interface. Get an interface pointer to it.
		//        
		if (S_OK != pShLink->QueryInterface(IID_IPersistFile, (LPVOID *)&ppf ))
		{
			break;
		}

		// Load the file.
		//
		lpwzLinkPath = AdkStrToWStr(lpszLinkPath);
		if (S_OK != ppf->Load((LPCOLESTR)lpwzLinkPath, STGM_READWRITE))
		{
			break;
		}

		// Set the path of the file the link points to.
		//
		if (S_OK != pShLink->SetPath(lpszPathBuffer))
		{
			break;
		}

		if (S_OK == ppf->Save((LPCOLESTR)lpwzLinkPath, TRUE))
		{
			bRet = TRUE;
		}

	} while(FALSE);

	if (ppf)
	{
		ppf->Release();
	}

	if (pShLink)
	{
		pShLink->Release();
	}

	if (lpwzLinkPath)
	{
		AdkFree(lpwzLinkPath);
	}

	CoUninitialize();

    return bRet;
}

/****************************************************************************
 * AdkSetLinkPathW
 *
 *	- 参数lpwzLinkPath			- 快捷方式
 *	- 参数lpwzPathBuffer		- 快捷方式指向的文件名
 *
 */
INLINE
BOOL WINAPI AdkSetLinkPathW(IN HWND    hWnd,
							IN PWSTR   lpwzLinkPath,
							IN PWSTR   lpwzPathBuffer)
{
	BOOL			bRet     = FALSE;
	IShellLinkW		*pShLink = NULL;
	IPersistFile	*ppf     = NULL;

	xASSERT((lpwzLinkPath));
	xASSERT((lpwzPathBuffer));

	// Call CoCreateInstance to obtain the IShellLink Interface pointer. 
	//
	CoInitialize(NULL);

	do
	{
		if (S_OK != CoCreateInstance(CLSID_ShellLink,
									 NULL,
									 CLSCTX_INPROC_SERVER,
									 IID_IShellLinkW,
									 (LPVOID *)&pShLink ))
		{
			break;
		}

		// The IShellLink Interface supports the IPersistFile
		// interface. Get an interface pointer to it.
		//        
		if (S_OK != pShLink->QueryInterface(IID_IPersistFile, (LPVOID *)&ppf ))
		{
			break;
		}

		// Load the file.
		//
		if (S_OK != ppf->Load((LPCOLESTR)lpwzLinkPath, STGM_READWRITE))
		{
			break;
		}

		// Set the path of the file the link points to.
		//
		if (S_OK != pShLink->SetPath(lpwzPathBuffer))
		{
			break;
		}

		if (S_OK == ppf->Save((LPCOLESTR)lpwzLinkPath, TRUE))
		{
			bRet = TRUE;
		}

	} while(FALSE);

	if (ppf)
	{
		ppf->Release();
	}

	if (pShLink)
	{
		pShLink->Release();
	}

	CoUninitialize();

    return bRet;
}

#endif // _ADK_TUOJIE_LNK_H_

/*
 * Revision:
 *
 *		2. 重构AdkLnk.h，提供三种函数	(BuildNum: 0002-20110711)
 *
 *		1. AdkGetLinkPath				(BuildNum: 0001-20100416)
 *
 *****************************************************************************/