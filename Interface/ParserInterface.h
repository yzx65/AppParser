#ifndef PARSERINTERFACE_H
#define PARSERINTERFACE_H

// SMS

#ifdef PARSE_EXPORTS
#define PARSE_API __declspec(dllexport)
#else
#define PARSE_API __declspec(dllimport)
#endif

struct SMS_Info
{
	std::wstring name;		// 名字
	std::wstring number;	// 电话号
	std::wstring time;		// 时间，如 2014-12-10 16:32
	std::wstring message;	// 短信内容
	bool isSend;			// 如果是接收到的短信 isSend = true
};

extern "C" PARSE_API bool SMS_Start(const wchar_t* dataPath);
extern "C" PARSE_API int SMS_GetRecordCount();
extern "C" PARSE_API SMS_Info* SMS_GetRecordAt(int index);
extern "C" PARSE_API bool SMS_Free();

struct CONTACT_Info
{
	std::wstring name;			// 名字
	std::wstring number;		// 电话号
	std::wstring email;			// 邮箱
	std::wstring address;		// 住址
	std::wstring profession;	// 公司职位
	std::wstring group;			// 组
};

extern "C" PARSE_API bool CONTACT_Start(const wchar_t* dataPath);
extern "C" PARSE_API int CONTACT_GetRecordCount();
extern "C" PARSE_API CONTACT_Info* CONTACT_GetRecordAt(int index);
extern "C" PARSE_API bool CONTACT_Free();

struct RECORD_Info
{
	std::wstring name;			// 名字
	std::wstring number;		// 电话号码
	std::wstring date;			// 通话时间
	std::wstring time;			// 通话时长
	std::wstring type;			// 通话类型
	std::wstring location;		// 手机所属地
};

extern "C" PARSE_API BOOL RECORD_Start(const wchar_t* dataPath);  
extern "C" PARSE_API DWORD RECORD_GetRecordCount();
extern "C" PARSE_API RECORD_Info* RECORD_GetRecordAt(int index);
extern "C" PARSE_API BOOL RECORD_Free();

#endif // PARSERINTERFACE_H