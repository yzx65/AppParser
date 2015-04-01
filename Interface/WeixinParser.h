#ifndef _WEIXIN_PARSER_H
#define _WEIXIN_PARSER_H

#ifdef WEIXINPARSER_EXPORTS
#define WEIXIN_API  __declspec(dllexport)
#else
#define WEIXIN_API  __declspec(dllimport)
#endif

#include <Windows.h>
#include "datastructure.h"

//iType: 0-android 1-ios
//
WEIXIN_API bool WEIXIN_InitEntry(LPCWSTR lpwzCasePath, int iType, char *lpszImei=NULL);  
bool AndroidInitEntry(LPCWSTR lpwzCasePath);
bool IosInitEntry(LPCWSTR lpwzCasePath);

WEIXIN_API void WEIXIN_Free();

//返回账号列表，以"|"隔开
//
WEIXIN_API bool WEIXIN_GetAccountList(char *lpszAccounts, int iSize); 
WEIXIN_API bool WEIXIN_GetAccoutInfo(const std::string &account);

//获取指定账号的好友信息
//
WEIXIN_API FriendInfo* WEIXIN_GetFirstFriend(std::string &account);
WEIXIN_API FriendInfo* WEIXIN_GetNextFriend(std::string &account);

//获取指定两人、QQ群或讨论组的聊天记录
//account:要获取的账号 chatAccount:要获取聊天记录的QQ号、群号或者讨论组号 iType：要获取的聊天记录的类型 0-个人 1-群 2-讨论组
//
WEIXIN_API ChatHistory* WEIXIN_GetFirstChatHistory(std::string &account, std::string &chatAccount, int iType);
WEIXIN_API ChatHistory* WEIXIN_GetNextChatHistory(std::string &account, std::string &chatAccount, int iType);


#endif

