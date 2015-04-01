#ifndef _QQ_PARSER_H
#define _QQ_PARSER_H

#ifdef QQPARSER_EXPORTS
#define QQ_API  __declspec(dllexport)
#else
#define QQ_API  __declspec(dllimport)
#endif

#include <Windows.h>
#include "datastructure.h"

//iType: 0-android 1-ios
//
QQ_API bool QQ_InitEntry(LPCWSTR lpwzCasePath, int iType, char *lpszImei=NULL);   

QQ_API void QQ_Free(); 

//返回账号列表，以"|"隔开
//
QQ_API bool QQ_GetAccountList(char *lpszAccounts, int iSize);

//获取账号信息
//
QQ_API bool QQ_GetAccoutInfo(const std::string &account);

//获取指定账号的好友信息
//
QQ_API FriendInfo* QQ_GetFirstFriend(std::string &account);
QQ_API FriendInfo* QQ_GetNextFriend(std::string &account);

//获取指定账号的分组信息
//
QQ_API GroupInfo* QQ_GetFirstGroup(std::string &account); 
QQ_API GroupInfo* QQ_GetNextGroup(std::string &account);

//获取指定账号的群信息
//
QQ_API TroopInfo* QQ_GetFirstTroop(std::string &account);
QQ_API TroopInfo* QQ_GetNextTroop(std::string &account);

//获取指定账号的讨论组信息
//
QQ_API DiscInfo* QQ_GetFirstDisc(std::string &account);
QQ_API DiscInfo* QQ_GetNextDisc(std::string &account);

//获取指定两人、QQ群或讨论组的聊天记录
//account:要获取的账号 chatAccount:要获取聊天记录的QQ号、群号或者讨论组号 iType：要获取的聊天记录的类型 0-个人 1-群 2-讨论组
//
QQ_API ChatHistory* QQ_GetFirstChatHistory(std::string &account, std::string &chatAccount, int iType);
QQ_API ChatHistory* QQ_GetNextChatHistory(std::string &account, std::string &chatAccount, int iType);

#endif