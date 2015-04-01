/********************************************************************
 * Module:									(BuildNum:0001-20111111)
 *       AdkKernel32.h
 *
 * Author:
 *		DING ZHAOKUN(dzkad@hotmail.com)
 *
 * Notes:
 *		对应于Kernel32.h，提供一些便利的函数
 *
 * Functions:
 *
 *		1. 下列函数在创建命名对象时，如果没有指定属性，则使用最低权限的ACL，这样每个进程都可以访问EVENT/MUTEX
 *			AdkCreateEventA(W)
 *			AdkCreateMutexA(W)
 *
 *
 */

#ifndef __ADK_KERNEL32_H__
#define __ADK_KERNEL32_H__

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

#ifndef  __KERNEL__

/**************************************************************
 * AdkCreateEventA
 *
 */
INLINE
HANDLE AdkCreateEventA(LPSECURITY_ATTRIBUTES lpEventAttributes,
					   BOOL					 bManualReset,
					   BOOL					 bInitialState,
					   LPCSTR				 lpszName)
{
	SECURITY_DESCRIPTOR		sd; 
	SECURITY_ATTRIBUTES		sa; 

	if (lpEventAttributes == NULL && lpszName)
	{
		InitializeSecurityDescriptor(&sd,   SECURITY_DESCRIPTOR_REVISION); 
		SetSecurityDescriptorDacl(&sd,   TRUE,   (PACL)NULL,   FALSE); 

		sa.nLength = sizeof(SECURITY_ATTRIBUTES); 
		sa.bInheritHandle = TRUE; 
		sa.lpSecurityDescriptor = &sd; 

		lpEventAttributes = &sa;
	}

	return CreateEventA(lpEventAttributes, bManualReset, bInitialState, lpszName);
}

/**************************************************************
 * AdkCreateEventW
 *
 */
INLINE
HANDLE AdkCreateEventW(LPSECURITY_ATTRIBUTES lpEventAttributes,
					   BOOL					 bManualReset,
					   BOOL					 bInitialState,
					   LPCWSTR				 lpwzName)
{
	SECURITY_DESCRIPTOR		sd; 
	SECURITY_ATTRIBUTES		sa; 

	if (lpEventAttributes == NULL && lpwzName)
	{
		InitializeSecurityDescriptor(&sd,   SECURITY_DESCRIPTOR_REVISION); 
		SetSecurityDescriptorDacl(&sd,   TRUE,   (PACL)NULL,   FALSE); 

		sa.nLength = sizeof(SECURITY_ATTRIBUTES); 
		sa.bInheritHandle = TRUE; 
		sa.lpSecurityDescriptor = &sd; 

		lpEventAttributes = &sa;
	}

	return CreateEventW(lpEventAttributes, bManualReset, bInitialState, lpwzName);
}

/**************************************************************
 * AdkCreateMutexA
 *
 */
INLINE
HANDLE AdkCreateMutexA(LPSECURITY_ATTRIBUTES lpMutexAttributes,
					   BOOL					 bInitialOwner,
					   LPCSTR				 lpszName)
{
	SECURITY_DESCRIPTOR		sd; 
	SECURITY_ATTRIBUTES		sa; 

	if (lpMutexAttributes == NULL && lpszName)
	{
		InitializeSecurityDescriptor(&sd,   SECURITY_DESCRIPTOR_REVISION); 
		SetSecurityDescriptorDacl(&sd,   TRUE,   (PACL)NULL,   FALSE); 

		sa.nLength = sizeof(SECURITY_ATTRIBUTES); 
		sa.bInheritHandle = TRUE; 
		sa.lpSecurityDescriptor = &sd; 

		lpMutexAttributes = &sa;
	}

	return CreateMutexA(lpMutexAttributes, bInitialOwner, lpszName);
}

/**************************************************************
 * AdkCreateMutexW
 *
 */
INLINE
HANDLE AdkCreateMutexW(LPSECURITY_ATTRIBUTES lpMutexAttributes,
					   BOOL					 bInitialOwner,
					   LPCWSTR				 lpwzName)
{
	SECURITY_DESCRIPTOR		sd; 
	SECURITY_ATTRIBUTES		sa; 

	if (lpMutexAttributes == NULL && lpwzName)
	{
		InitializeSecurityDescriptor(&sd,   SECURITY_DESCRIPTOR_REVISION); 
		SetSecurityDescriptorDacl(&sd,   TRUE,   (PACL)NULL,   FALSE); 

		sa.nLength = sizeof(SECURITY_ATTRIBUTES); 
		sa.bInheritHandle = TRUE; 
		sa.lpSecurityDescriptor = &sd; 

		lpMutexAttributes = &sa;
	}

	return CreateMutexW(lpMutexAttributes, bInitialOwner, lpwzName);
}


//----------------------------------------------------------------
// Surport UNICODE And ANSI Compile Options
//
#ifdef UNICODE

#define AdkCreateEvent		AdkCreateEventW
#define AdkCreateMutex		AdkCreateMutexW

#else

#define AdkCreateEvent		AdkCreateEventA
#define AdkCreateMutex		AdkCreateMutexA

#endif // !UNICODE


#endif // ! __KERNEL__

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __ADK_DEBUG_H__

/*
 *
 *		1. First Version (0001-20111111)
 *
 *****************************************************************************/