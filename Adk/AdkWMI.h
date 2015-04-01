/***************************************************************************
 * Module:											(BuildNum:0001-20100414)
 *       AdkWMI.h
 *
 * Author:
 *		DING ZHAOKUN(dzkad@hotmail.com)
 *
 * Time:
 *		2007-12-28,Nanjing
 *
 * Notes:
 *		包装了WMI操作, 只能在C++编译环境下编译
 *
 * Functions:
 *
 *		PVOID AdkWMIInitialize()
 *
 *		PVOID AdkWMIQueryEnumeratorExW(PVOID lpWmiServices, PWCHAR lpwcQuery)
 *		PVOID AdkWMIQueryDiskDriveEnumerator(PVOID lpWmiServices)
 *
 *		PVOID AdkWMIEnumInstances(PVOID lpEnumerator)
 *
 *		BOOL  AdkWMIQueryStrInfoW(PVOID lpWmiInstance,PWCHAR lpwzItem, PWCHAR lpwcValue)
 *		BOOL  AdkWMIQueryUIntInfo(PVOID lpWmiInstance,PWCHAR lpwzItem, UINT *lpiValue)
 *		BOOL  AdkWMIQueryLargeIntInfo(PVOID lpWmiInstance,PWCHAR lpwzItem, unsigned __int64 *lpliValue)
 *
 *		VOID  AdkWMIFreeEnumerator(PVOID lpEnumerator)
 *		VOID  AdkWMIFreeInstance(PVOID lpInstance);
 *
 *		BOOL  AdkWMIDestroy(PVOID lpWmiServices)
 *
 */

#pragma once

#ifndef _ADK_TUOJIE_WMI_H_
#define _ADK_TUOJIE_WMI_H_

#include "AdkPrecomp.h"
#include <Objbase.h>
#include <commctrl.h>
#include <comdef.h>
#include <Wbemidl.h>

#pragma comment(lib, "WbemUuid.Lib")

/**************************************************************
 * Converts variant to 64 bit unsigned integer. Floating point values are not rounded, just integer part is returned. For string
 *  variants it will try to convert it using _atoi64()
 *
 *  \param var Variant to convert.
 *  \return Integer representation of value in variant. 0 if variant was empty or contained undefined value or value with unsupported type or
 *          error occured during conversion from string variants.
 *
 *  \note Function does not support date/time/array variants.
*/
__inline 
unsigned __int64 VariantToUInt(const VARIANT &var)
{
    unsigned __int64 result = 0;

    switch (var.vt)
    {
        case VT_NULL:                                           // No data
        case VT_EMPTY:
        case VT_EMPTY | VT_BYREF:                               // Empty reference = invalid data
            break;

        case VT_UI1:                                            // char
            result = (unsigned __int64) var.bVal;
            break;

        case VT_UI1 | VT_BYREF:                                 // Reference to char
            result = (unsigned __int64) *var.pbVal;
            break;

        case VT_UI2:                                            // 16 bit unsigned int
            result = (unsigned __int64) var.uiVal;
            break;

        case VT_UI2 | VT_BYREF:                                 // Reference to 16 bit unsigned int
            result = (unsigned __int64) *var.puiVal;
            break;

        case VT_UI4:                                            // 32 bit unsigned int
            result = (unsigned __int64) var.ulVal;
            break;

        case VT_UI4 | VT_BYREF:                                 // Reference to 32 bit unsigned int
            result = (unsigned __int64) *var.pulVal;
            break;

        case VT_UI8:                                            // 64 bit unsigned int
            result = (unsigned __int64) var.ullVal;
            break;

        case VT_UI8 | VT_BYREF:                                 // Reference to 64 bit unsigned int
            result = (unsigned __int64) *var.pullVal;
            break;

        case VT_UINT:                                           // Unsigned int
            result = (unsigned __int64) var.uintVal;
            break;

        case VT_UINT | VT_BYREF:                                // Reference to unsigned int
            result = (unsigned __int64) *var.puintVal;
            break;

        case VT_INT:                                            // int
            result = (unsigned __int64) var.intVal;
            break;

        case VT_INT | VT_BYREF:                                 // Reference to int
            result = (unsigned __int64) *var.puintVal;
            break;

        case VT_I1:                                             // char
            result = (unsigned __int64) var.cVal;
            break;

        case VT_I1 | VT_BYREF:                                  // reference to char
            result = (unsigned __int64) *var.pcVal;
            break;

        case VT_I2:                                             // 16 bit int
            result = (unsigned __int64) var.iVal;
            break;

        case VT_I2 | VT_BYREF:                                  // Pointer to 16 bit int
            result = (unsigned __int64) *var.piVal;
            break;

        case VT_I4:                                             // 32 bit int
            result = (unsigned __int64) var.lVal;
            break;

        case VT_I4 | VT_BYREF:                                  // Pointer to 32 bit int
            result = (unsigned __int64) *var.plVal;
            break;

        case VT_I8:                                             // 64 bit int
            result = (unsigned __int64) var.llVal;
            break;

        case VT_I8 | VT_BYREF:                                  // Pointer to 64 bit int
            result = (unsigned __int64) *var.pllVal;
            break;

        case VT_R4:                                             // 32 bit real (float)
            result = (unsigned __int64) var.fltVal;
            break;

        case VT_R4 | VT_BYREF:                                  // Pointer to 32 bit real (float)
            result = (unsigned __int64) *var.pfltVal;
            break;

        case VT_R8:                                             // double
            result = (unsigned __int64) var.dblVal;
            break;

        case VT_R8 | VT_BYREF:                                  // Pointer to double
            result = (unsigned __int64) *var.pdblVal;
            break;

        case VT_BSTR:                                           // string (BSTR)
#ifndef UNICODE
            {
                CHAR    str[64] = {0};

                WideCharToMultiByte(CP_ACP, 0, var.bstrVal, -1, str, 64, NULL, NULL);

                if (str[0] != 0)
                {
                    result = _atoi64(str);
                }
            }
#else
            {
                StringStream stream;

                stream << var.bstrVal;

                stream >> result;
            }
#endif
            break;

        case VT_BSTR | VT_BYREF:                                // Pointer to string (BSTR)
#ifndef UNICODE
            {
                CHAR    str[64] = {0};

                WideCharToMultiByte(CP_ACP, 0, *var.pbstrVal, -1, str, 64, NULL, NULL);

                if (str[0] != 0)
                {
                    result = _atoi64(str);
                }
            }
#else
            {
                StringStream stream;

                stream << *var.pbstrVal;

                stream >> result;
            }
#endif
            break;

        case VT_BOOL:                                           // BOOL
            result = (unsigned __int64) var.boolVal;
            break;

        case VT_BOOL | VT_BYREF:                                // Pointer to BOOL
            result = (unsigned __int64) *var.pboolVal;
            break;
    }

    return result;
}

/**************************************************************
 * WMIInitialize:
 *	- This will connect to the WMI server on local computer and connect to the ROOT\\CIMV2 WMI namespace.
 *
 */
__inline
PVOID AdkWMIInitialize()
{
	HRESULT hres;												// Result of API calls.
	IWbemServices * Services = NULL;
	IWbemLocator  * Locator  = NULL;                            // Locator service

    // Initialize COM interface
	//
    CoInitializeEx(NULL, COINIT_MULTITHREADED);
  
    // Set general COM security levels
	//
    hres = CoInitializeSecurity(NULL,                          // Security descriptor
                                -1,                            // COM authentication
                                NULL,                          // Authentication services
                                NULL,                          // Reserved
                                RPC_C_AUTHN_LEVEL_DEFAULT,     // Default authentication
                                RPC_C_IMP_LEVEL_IMPERSONATE,   // Default Impersonation
                                NULL,                          // Authentication info
                                EOAC_NONE,                     // Additional capabilities
                                NULL);                         // Reserved

    if (FAILED(hres))
    {
        xPANICA(("Failed to initialize security.\r\n"));
        CoUninitialize();
        return Services;
    }

    hres = CoCreateInstance(CLSID_WbemLocator,                  // Class id (locator class)
                            0,                                  // Not aggregate object
                            CLSCTX_INPROC_SERVER,               // Context (INPROC_SERVER = dll which runs in same process as caller)
                            IID_IWbemLocator,                   // Interface reference
                            (void**) &Locator);                 // result

    if (FAILED(hres))
    {
        xPANICA(("Failed to create Locator service.\r\n"));
        CoUninitialize();
        return Services;
    }

    // Connect to WMI through the IWbemLocator::ConnectServer method
    // Connect to the root\cimv2 namespace with the current user and obtain pointer Services to make IWbemServices calls.
	//
    hres = Locator->ConnectServer(bstr_t(L"ROOT\\CIMV2"),		// Connect to CIMV2 namespace of WMI
                                  NULL,                         // User Name (NULL = curren user)
                                  NULL,                         // User Password (NULL = current)
                                  0,                            // Locale, current
                                  NULL,                         // Security flags
                                  0,                            // Authority
                                  0,                            // Context object
                                  &Services);                   // IWbemServices proxy

    if (FAILED(hres))
    {
        xPANICA(("[AdkWMI.h] InitializeWMI : Could not connect to WMI.\r\n"));
        Locator->Release();
        CoUninitialize();
        return Services;
    }

    Locator->Release();

    // Set security levels on the proxy
	//
    hres = CoSetProxyBlanket(Services,								// Indicates the proxy to set
                             RPC_C_AUTHN_WINNT,						// Authentication service (xxx_WINNT = use NTLMSSP (Windows NT LAN Manager Security Support Provider))
                             RPC_C_AUTHZ_NONE,						// Authorization service (xxx_NONE = no authorization performed on server)
                             NULL,									// Server principal name
                             RPC_C_AUTHN_LEVEL_CALL,				// Authentication level (xxx_CALL = auth only at the beginning of each call)
                             RPC_C_IMP_LEVEL_IMPERSONATE,			// Impersonation level (xxx_IMPERSONATE = server can impersonate client's security context)
                             NULL,									// Client identity handle
                             EOAC_NONE);							// Proxy capabilities (NONE = no flags set)

    if (FAILED(hres))
    {
        xPANICA(("[AdkWMI.h] InitializeWMI : Unable to set proxy blanket.\r\n"));
        Services->Release();
        CoUninitialize();
        return Services;
    }

    return Services;
}

/**************************************************************
 * AdkWMIQueryEnumeratorExW
 *
 */
__inline
PVOID AdkWMIQueryEnumeratorExW(PVOID lpWmiServices, PWCHAR lpwcQuery)
{
	HRESULT              hres;
	IWbemServices		 *Services = (IWbemServices *)lpWmiServices;
    IEnumWbemClassObject *Enumerator = NULL;

    // find all hard drives
	//
    hres = Services->ExecQuery(bstr_t((L"WQL")),										// query language
                               bstr_t((lpwcQuery)),									// Query text
                               WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,	// flags
                               NULL,													// No context
                               &Enumerator);											// Output enumerator


    if (SUCCEEDED(hres))
    {
		return Enumerator;
	}

	return NULL;
}

/**************************************************************
 * AdkWMIQueryDiskDriveEnumerator
 *
 */
__inline
PVOID AdkWMIQueryDiskDriveEnumerator(PVOID lpWmiServices)
{
	return AdkWMIQueryEnumeratorExW(lpWmiServices, L"SELECT * FROM Win32_DiskDrive");
}

/**************************************************************
 * AdkWMIEnumInstances
 *
 */
__inline
PVOID AdkWMIEnumInstances(PVOID lpEnumerator)
{
    IEnumWbemClassObject *Enumerator = (IEnumWbemClassObject *)lpEnumerator;
	IWbemClassObject	 *DriveObject = NULL;
    ULONG				 returned = 0;

    Enumerator->Next(WBEM_INFINITE, 1,&DriveObject, &returned);

    return DriveObject;
}

/**************************************************************
 * AdkWMIQueryStrInfoW
 *
 *
 */
__inline
BOOL AdkWMIQueryStrInfoW(PVOID lpWmiInstance,PWCHAR lpwzItem, PWCHAR lpwcValue)
{
	BOOL	bRet = FALSE;

	IWbemClassObject *DriveObject = (IWbemClassObject *)lpWmiInstance;

	xASSERT((lpwzItem));
	xASSERT((lpwcValue));

	VARIANT value;
	VariantInit(&value);

	HRESULT hres = DriveObject->Get(lpwzItem, 0, &value, NULL, NULL);

	if (SUCCEEDED(hres))
	{
		if (value.bstrVal)
		{
			wcscpy(lpwcValue, value.bstrVal);
			bRet = TRUE;
		}
	}
	
	VariantClear(&value);

	return bRet;
}

/**************************************************************
 * AdkWMIQueryUIntInfo
 *
 */
__inline
BOOL AdkWMIQueryUIntInfo(PVOID lpWmiInstance,PWCHAR lpwzItem, UINT *lpiValue)
{
	BOOL	bRet = FALSE;

	IWbemClassObject *DriveObject = (IWbemClassObject *)lpWmiInstance;

	xASSERT((lpwzItem));

	VARIANT value;
	VariantInit(&value);

	HRESULT hres = DriveObject->Get(lpwzItem, 0, &value, NULL, NULL);

	if (SUCCEEDED(hres))
	{
		*lpiValue = value.uintVal;
		bRet = TRUE;
	}

	VariantClear(&value);

	return bRet;
}

/**************************************************************
 * AdkWMIQueryLargeIntInfo
 *
 */
__inline
BOOL AdkWMIQueryLargeIntInfo(PVOID lpWmiInstance,PWCHAR lpwzItem, unsigned __int64 *lpliValue)
{
	BOOL	bRet = FALSE;

	IWbemClassObject *DriveObject = (IWbemClassObject *)lpWmiInstance;

	xASSERT((lpwzItem));

	VARIANT value;
	VariantInit(&value);

	HRESULT hres = DriveObject->Get(lpwzItem, 0, &value, NULL, NULL);

	if (SUCCEEDED(hres))
	{
		*lpliValue = VariantToUInt(value);
		bRet = TRUE;
	}

	VariantClear(&value);

	return bRet;
}

/**************************************************************
 * AdkWMIFreeInstance
 *
 */
__inline
VOID AdkWMIFreeInstance(PVOID lpInstance)
{
	IWbemClassObject *DriveObject = (IWbemClassObject *)lpInstance;
	DriveObject->Release();
	return;
}

/**************************************************************
 * AdkWMIFreeEnumerator
 *
 */
__inline
VOID AdkWMIFreeEnumerator(PVOID lpEnumerator)
{
	IEnumWbemClassObject *Enumerator = (IEnumWbemClassObject *)lpEnumerator;
	Enumerator->Release();
	return;
}

/**************************************************************
 * AdkWMIDestroy
 *
 */
__inline
BOOL AdkWMIDestroy(PVOID lpWmiServices)
{
	IWbemServices * Services = (IWbemServices *)lpWmiServices;

    if (Services != NULL) 
	{
        Services->Release();
        Services = NULL;
        CoUninitialize();
    }

    return TRUE;
}

#endif // _ADK_TUOJIE_WMI_H_