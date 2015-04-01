#include "stdafx.h"
#include <Windows.h>
#include <tchar.h>
#include <strsafe.h>
#include <string>

//////////////////////////////////////////////////////////////////////////
//加密狗函数
// 狗的位置
//
#define RC_OPEN_FIRST_IN_LOCAL			1
#define RC_OPEN_NEXT_IN_LOCAL			2
#define RC_OPEN_IN_LAN					3
#define RC_OPEN_LOCAL_FIRST				4
#define RC_OPEN_LAN_FIRST				5

// 密码类型
//
#define RC_PASSWORDTYPE_USER			1
#define RC_PASSWORDTYPE_DEVELOPER		2

// 狗类型位置
//
#define RC_DOGTYPE_LOCAL				1
#define RC_DOGTYPE_NET					2

// 文件类型
//
#define RC_TYPEFILE_DATA				1
#define RC_TYPEFILE_LICENSE				2
#define RC_TYPEFILE_ALGORITHMS			3
#define RC_TYPEFILE_DIR					4

// 加密算法
//
#define RC_KEY_AES						1
#define RC_KEY_SIGN						2

/////////////////////////////////////////////////////////////////
// some structure definitoin used in dog
#pragma pack(1)

typedef struct _RC_HARDWARE_INFO
{
	ULONG 	ulSerialNumber;			//The Serial Number
	ULONG 	ulCurrentNumber;   		//The Hardware Current Number
	UCHAR 	ucDogType;        		//Hardware Dog Type, NetDog or LocalDog
	UCHAR	ucDogModel[4];			//UGRA or PGRA, at this version ,it is equal to UGRA
}RC_HARDWARE_INFO,*PRC_HARDWARE_INFO;

typedef struct _RC_PRODUCT_INFO
{
	CHAR	szProductName[16];       //Product Name
	ULONG 	ulProductCurNumber;   	 //The Developer Current Number
}RC_PRODUCT_INFO,*PRC_PRODUCT_INFO;

#pragma pack()

// function prototype
//
typedef HRESULT (WINAPI *RC_OPENDOG)(ULONG ulFlag, CHAR * pszProductName, ULONG * pDogHandle);
typedef HRESULT (WINAPI *RC_CLOSEDOG)(ULONG DogHandle);
typedef HRESULT (WINAPI *RC_CHECKDOG)(ULONG DogHandle);
typedef HRESULT (WINAPI *RC_GETDOGINFO)(ULONG DogHandle, RC_HARDWARE_INFO * pHardwareInfo, ULONG * pulLen);
typedef HRESULT (WINAPI *RC_GETPRODUCTCURRENTNO)(ULONG DogHandle, ULONG * pulProductCurrentNo);
typedef HRESULT (WINAPI *RC_VERIFYPASSWORD)(ULONG DogHandle, UCHAR ucPasswordType, CHAR * pszPassword,  UCHAR * pucDegree);
typedef HRESULT (WINAPI *RC_CHANGEPASSWORD)(ULONG DogHandle, UCHAR ucPasswordType, CHAR * pszPassword);
typedef HRESULT (WINAPI *RC_UPGRADE)(ULONG DogHandle, UCHAR * pucUpgrade, ULONG ulLen);
typedef HRESULT (WINAPI *RC_GETRANDOM)(ULONG DogHandle, UCHAR * pucRandom, UCHAR ucLen);
typedef HRESULT (WINAPI *RC_ENCRYPTDATA)(ULONG DogHandle, UCHAR * pucIn, ULONG ulInLen, UCHAR * pucOut, ULONG * pulOutLen);
typedef HRESULT (WINAPI *RC_DECRYPTDATA)(ULONG DogHandle, UCHAR * pucIn, ULONG ulInLen, UCHAR * pucOut, ULONG * pulOutLen);
typedef HRESULT (WINAPI *RC_CONVERTDATA)(ULONG DogHandle, UCHAR * pucIn, ULONG ulLen, ULONG * pulRet);
typedef HRESULT (WINAPI *RC_SETKEY)(ULONG DogHandle, UCHAR ucKeyType, UCHAR * pucIn, ULONG ulLen);
typedef HRESULT (WINAPI *RC_SIGNDATA)(ULONG DogHandle, UCHAR * pucIn, ULONG ulLen, UCHAR * pucOut, ULONG * pulOutLen);
typedef HRESULT (WINAPI *RC_EXECUTEFILE)(ULONG DogHandle, USHORT usDirID, USHORT usFileID, UCHAR * pucDataIn, ULONG ulInLen, UCHAR * pucDataOut, ULONG * pulOutLen);				
typedef HRESULT (WINAPI *RC_WRITEFILE)(ULONG DogHandle, USHORT usDirID, USHORT usFileID, ULONG ulPos, ULONG ulLen, UCHAR * pucbuf);
typedef HRESULT (WINAPI *RC_VISITLICENSEFILE)(ULONG DogHandle, USHORT usDirID, USHORT usFileID, ULONG ulReserved);
typedef HRESULT (WINAPI *RC_CREATEFILE)(ULONG DogHandle, USHORT usDirID, USHORT usFileID, UCHAR ucFileType, ULONG ulFileLen);
typedef HRESULT (WINAPI *RC_DELETEFILE)(ULONG DogHandle, USHORT usDirID, USHORT usFileID);
typedef HRESULT (WINAPI *RC_CREATEDIR)(ULONG DogHandle, USHORT usDirID, ULONG ulSize);
typedef HRESULT (WINAPI *RC_DELETEDIR)(ULONG DogHandle, USHORT usDirID);
typedef HRESULT (WINAPI *RC_DEFRAGFILESYSTEM)(ULONG DogHandle, USHORT usDirID);
typedef HRESULT (WINAPI *RC_READFILE)(ULONG DogHandle, USHORT usDirID, USHORT usFileID, ULONG ulPos, ULONG ulLen, UCHAR * pucbuf);
typedef HRESULT (WINAPI *RC_GETUPGRADEREQUESTSTRING)(ULONG DogHandle, UCHAR * pucBuf, ULONG * pulLen);	


RC_OPENDOG 							RC_OpenDog;
RC_CLOSEDOG 						RC_CloseDog;
RC_CHECKDOG							RC_CheckDog;
RC_GETDOGINFO						RC_GetDogInfo;
RC_GETPRODUCTCURRENTNO				RC_GetProductCurrentNo;
RC_VERIFYPASSWORD					RC_VerifyPassword;
RC_CHANGEPASSWORD					RC_ChangePassword;
RC_UPGRADE							RC_Upgrade;
RC_GETRANDOM						RC_GetRandom;
RC_ENCRYPTDATA						RC_EncryptData;
RC_DECRYPTDATA						RC_DecryptData;
RC_CONVERTDATA						RC_ConvertData;
RC_SETKEY							RC_SetKey;
RC_SIGNDATA							RC_SignData;
RC_EXECUTEFILE						RC_ExecuteFile;
RC_WRITEFILE						RC_WriteFile;
RC_VISITLICENSEFILE					RC_VisitLicenseFile;
RC_CREATEFILE						RC_CreateFile;
RC_DELETEFILE						RC_DeleteFile;
RC_CREATEDIR						RC_CreateDir;
RC_DELETEDIR						RC_DeleteDir;
RC_DEFRAGFILESYSTEM					RC_DefragFileSystem;
RC_READFILE							RC_ReadFile;
RC_GETUPGRADEREQUESTSTRING			RC_GetUpgradeRequestString;
HMODULE                             __hModDog = NULL;

/* ******************************************************************************
 *
 * AdkGrandDogCheck
 *
 */

BOOL
WINAPI
AdkGrandDogCheck(char *szProductName, char* szPassword)
{
	BOOL            bRet               = FALSE;
	HRESULT         hrReturnCode       ;
	unsigned long	ulCurrentDogHandle ;
	unsigned long	ulOpenFlag         = RC_OPEN_FIRST_IN_LOCAL;
	UCHAR	        ucVerifyCount      ;
	ULONG		    ulLen              = 100;
	HMODULE         hModDog            = NULL;
	WCHAR			modulePath[MAX_PATH] = L"";
	std::wstring	strModulePath;
	do
	{
		// Load Dll
		//

		GetModuleFileNameW(NULL, modulePath, MAX_PATH);
		strModulePath = modulePath;
		if(strModulePath.rfind(L"\\") != std::string::npos)
		{
			strModulePath = strModulePath.substr(0, strModulePath.rfind(L"\\"));
			strModulePath += L"\\RCGrandDogW32.dll";
		}
	
		hModDog = LoadLibraryW(strModulePath.c_str());
		if ( NULL == hModDog )
		{
			break;
		}
		// get the pointer of functions
		//
		RC_OpenDog = (RC_OPENDOG)GetProcAddress(hModDog, "rc_OpenDog");
		RC_CloseDog = (RC_CLOSEDOG)GetProcAddress(hModDog, "rc_CloseDog");
		RC_CheckDog = (RC_CHECKDOG)GetProcAddress(hModDog, "rc_CheckDog");
		RC_GetDogInfo = (RC_GETDOGINFO)GetProcAddress(hModDog, "rc_GetDogInfo");
		RC_GetProductCurrentNo = (RC_GETPRODUCTCURRENTNO)GetProcAddress(hModDog, "rc_GetProductCurrentNo");

		RC_VerifyPassword = (RC_VERIFYPASSWORD)GetProcAddress(hModDog, "rc_VerifyPassword");
		RC_ChangePassword = (RC_CHANGEPASSWORD)GetProcAddress(hModDog, "rc_ChangePassword");
		RC_Upgrade = (RC_UPGRADE)GetProcAddress(hModDog, "rc_Upgrade");
		RC_GetRandom = (RC_GETRANDOM)GetProcAddress(hModDog, "rc_GetRandom");
		RC_EncryptData = (RC_ENCRYPTDATA)GetProcAddress(hModDog, "rc_EncryptData");

		RC_DecryptData = (RC_DECRYPTDATA)GetProcAddress(hModDog, "rc_DecryptData");
		RC_ConvertData = (RC_CONVERTDATA)GetProcAddress(hModDog, "rc_ConvertData");
		RC_SetKey = (RC_SETKEY)GetProcAddress(hModDog, "rc_SetKey");
		RC_SignData = (RC_SIGNDATA)GetProcAddress(hModDog, "rc_SignData");
		RC_ExecuteFile = (RC_EXECUTEFILE)GetProcAddress(hModDog, "rc_ExecuteFile");

		RC_WriteFile = (RC_WRITEFILE)GetProcAddress(hModDog, "rc_WriteFile");
		RC_VisitLicenseFile = (RC_VISITLICENSEFILE)GetProcAddress(hModDog, "rc_VisitLicenseFile");
		RC_CreateFile = (RC_CREATEFILE)GetProcAddress(hModDog, "rc_CreateFile");
		RC_DeleteFile = (RC_DELETEFILE)GetProcAddress(hModDog, "rc_DeleteFile");
		RC_CreateDir = (RC_CREATEDIR)GetProcAddress(hModDog, "rc_CreateDir");

		RC_DeleteDir = (RC_DELETEDIR)GetProcAddress(hModDog, "rc_DeleteDir");
		RC_DefragFileSystem = (RC_DEFRAGFILESYSTEM)GetProcAddress(hModDog, "rc_DefragFileSystem");
		RC_ReadFile = (RC_READFILE)GetProcAddress(hModDog, "rc_ReadFile");
		RC_GetUpgradeRequestString = (RC_GETUPGRADEREQUESTSTRING)GetProcAddress(hModDog, "rc_GetUpgradeRequestString");

		if ( !RC_OpenDog || !RC_CloseDog || !RC_CheckDog || !RC_GetDogInfo || !RC_GetProductCurrentNo \
			|| !RC_VerifyPassword || !RC_ChangePassword || !RC_Upgrade || !RC_GetRandom || !RC_EncryptData \
			|| !RC_DecryptData || !RC_ConvertData || !RC_SetKey || !RC_SignData || !RC_ExecuteFile \
			|| !RC_WriteFile || !RC_VisitLicenseFile || !RC_CreateFile || !RC_DeleteFile || !RC_CreateDir \
			|| !RC_DeleteDir || !RC_DefragFileSystem || !RC_ReadFile || !RC_GetUpgradeRequestString
			)
		{
			break;
		}
		// get the nandle of dog
		//
		hrReturnCode = RC_OpenDog(ulOpenFlag, szProductName, &ulCurrentDogHandle);
		if ( S_OK != hrReturnCode )
		{
			break;//ExitProcess(0);
		}
		// verify the password of dog
		//
		hrReturnCode = RC_VerifyPassword(ulCurrentDogHandle, RC_PASSWORDTYPE_USER, szPassword, &ucVerifyCount);
		if ( S_OK != hrReturnCode )
		{
			break;
		}
		//
		bRet = TRUE;

	} while(FALSE);

	if ( hModDog )
	{
		FreeLibrary(hModDog);
	}
	return bRet;
}
