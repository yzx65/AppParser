#ifndef COMMON_DEF_H
#define COMMON_DEF_H

#include <Windows.h>

#define GUID_USB		{0xA5DCBF10, 0x6530, 0x11D2, {0x90, 0x1F, 0x00, 0xC0, 0x4F, 0xB9, 0x51, 0xED}}   //监听USB消息
#define GUID_ANDROID    {0xF72FE0D4, 0xCBCB, 0x407d, {0x88, 0x14, 0x9E, 0xD6, 0x73, 0xD0, 0xDD, 0x6B}}   //监听安卓设备信息


//上次断点状态
#define BREAK_POINT_APP     1
#define BREAK_POINT_BACKUP  2
#define BREAK_POINT_IMAGE   4

//系统应用对应标志位
//
#define SYSTEM_APP_SMS			0X00000001	//短信
#define SYSTEM_APP_CONTACT		0X00000002  //通讯录
#define SYSTEM_APP_CALENDAR		0X00000004	//日历
#define SYSTEM_APP_CALLHISTORY	0X00000008	//通话记录
#define SYSTEM_APP_EXPLORER		0X00000010	//浏览器
#define SYSTEM_APP_NOTES		0X00000020	//备忘录
#define SYSTEM_APP_RECORDINGS	0X00000040	//语音备忘录
#define SYSTEM_APP_MAIL         0X00000080	//邮件
#define SYSTEM_APP_MAP			0X00000100	//地图
#define SYSTEM_APP_KCHAIN       0X00000200	//密码信息
#define SYSTEM_APP_SETTINGS		0X00000400	//设置
#define SYSTEM_APP_PHOTOS		0X00000800	//照片
#define SYSTEM_APP_KEYBOARD		0X00001000	//键盘记录

#define LARGE_SIZE			1024 * 1024 * 1024
#define UNKNOWN_SIZE        -1
#define IMAGE_BLK_SIZE		1048576

#define INTERNAL_TOOLS_PATH		L""				//程序使用第三方工具的相对路径
#define MAX_DEV_COUNT			1				//最大设备连接数
#define BACKUP_PASS				"1"				//备份密码
#define MAX_ADB_OUTPUT			10240			//adb输出最大长度
#define MAX_EXT_FILTER_LEN		10240			//后缀名过滤长度

#define MAX_PACKET_SIZE	4194304		//无线取证每次发送的数据包最大大小
#define MAX_BLK_SIZE    16384		//无线取证每次发送的数据块的最大大小
#define SERVER_PORT		8080		//无线取证服务端端口
#define MAX_CONNECTION  50			//无线取证服务端最大连接数

#define MAX_FILE_PATH       512				
#define MAX_DEV_LEN			100
#define FILE_READ_SIZE		1024 * 1024 * 10
 
//
//硬盘使用情况
typedef struct _DISK_USAGE
{
	UINT64   ui64SysUsed;   //系统分区已用
	UINT64	 ui64SysTtl;    //系统分区总量
	UINT64	 ui64UserUsed;  //用户分区已用
	UINT64   ui64UserTtl;   //用户分区总量
}DISK_USAGE, *LPDISK_USAGE;

typedef struct _LAST_STATUS
{
	BOOL	  bPassRemain;              //IOS残留备份密码
	int		  iLastStaus;               //上次取证模式
	char	  szRemainArc[MAX_DEV_LEN]; //归档残留文件
	int		  iAppMode;                 //快速取证模式：遍历取证、归档取证
}LAST_STATUS, *LPLAST_STATUS;

enum DEV_TYPE
{
	DEV_TYPE_IOS = 1,
	DEV_TYPE_ANDROID
};

typedef struct _BASE_DEV_INFO 
{
	DEV_TYPE	devType;                        //设备类型：IOS,ANDROID
	char		szDevId[MAX_DEV_LEN];			//ios:udid  android:adb devices列出的标识
	char		szDevName[MAX_DEV_LEN];			//设备名称
	char		szDevModel[MAX_DEV_LEN];        //设备型号
	char		szNumber[MAX_DEV_LEN];          //设备号码
	char		szOSVersion[MAX_DEV_LEN];       //系统版本
	char		szSerialNum[MAX_DEV_LEN];       //设备序列号
	BOOL		bJailBroken;					//是否越狱或者ROOT
	char		szCpuArc[MAX_DEV_LEN];          //cpu架构
	DISK_USAGE	diskUsage;                      //存储使用情况
}BASE_DEV_INFO, *LPBASE_DEV_INFO;

//ios设备信息
//
typedef struct _IOS_DEV_INFO
{
	char				szColor[MAX_DEV_LEN];     //设备颜色
	BOOL				bBackupPass;              //是否有备份密码
}IOS_DEV_INFO, *LPIOS_DEV_INFO;


//安卓设备信息
//
typedef struct _ANDROID_DEV_INFO
{
	char				szManu[MAX_DEV_LEN];	  //制造厂商
	char				szRamSize[MAX_DEV_LEN];   //内存大小
	char				szPixel[MAX_DEV_LEN];     //屏幕分辨率 形如：1920 * 1080
}ANDROD_DEV_INFO, *LPANDROID_DEV_INFO;

typedef  struct DEV_INFO
{
	BASE_DEV_INFO	baseDevInfo;
	union
	{
		IOS_DEV_INFO	iosDevInfo;
		ANDROD_DEV_INFO androidDevInfo;
	}unDevInfo;
}DEV_INFO, *LPDEV_INFO;

//案例信息
//
typedef struct _CASE_INFO 
{
	WCHAR wzDirPath[MAX_PATH];       //案例路径

	char  szName[MAX_DEV_LEN];       //案例名称
	char  szDevModel[MAX_DEV_LEN];   //设备型号
	char  szAddress[MAX_DEV_LEN];    //取证地点
	char  szTime[MAX_DEV_LEN];       //取证时间
	char  szDevNum[MAX_DEV_LEN];     //设备号码
	char  szId[MAX_DEV_LEN];         //身份证号
	char  szRemark[MAX_DEV_LEN];     //备注
}CASE_INFO, *LPCASE_INFO;

//
//第三方应用信息
#define APP_UNFIN      0
#define APP_BIN_START  1
#define APP_BIN_FIN    2
#define APP_DATA_START 3
#define APP_DATA_FIN   4

typedef struct _APP_INFO 
{
	int			iPriority;           //优先级， 0：系统应用 1：重要应用 2：其他应用
	int			iSubPriority;        //对于系统应用，是系统应用标志位；对于重要应用，是重要应用的子优先级
	bool        bSelected;           //已勾选
	int			iState;				 //0-未完成，1-应用程序已完成， 2-数据已完成

	char		szAppID[50];				//应用ID
	char		szAppName[30];				//应用名称
	char		szAppVersion[30];			//应用版本
	char		szMain[MAX_DEV_LEN];        //程序入口
	char		szDataDir[MAX_DEV_LEN];		//数据路径
	char		szAppDir[MAX_DEV_LEN];		//应用路径
	char        szAccount[50];				//购买帐号
	char		szBuyDate[30];				//购买日期
	INT64		i64DocSize;					//文档大小
	INT64		i64AppSize;					//应用大小

	char		*lpszIconData;    //图标数据
	UINT64		u64IconSize;      //图标数据大小
}APP_INFO, *LPAPP_INFO;

//
//文件拷贝过滤
typedef struct _APP_COPY_FILTER
{
	bool		bCopyApp;           //拷贝应用
	bool        bLargeFileFilter;   //按文件大小过滤
	UINT64		u64LargeSize;       //最大获取文件
	bool        bExtFilter;         //按扩展名类型过滤
	char		szExt[MAX_EXT_FILTER_LEN]; //扩展名类型。形如：*.txt;*.doc;
}APP_COPY_FILTER, *LPAPP_COPY_FILTER;

//
//文件信息
typedef struct _FILE_INFO   
{
	char	 szAppID[MAX_DEV_LEN];			//文件所属应用ID
	char	 szAppName[MAX_DEV_LEN];		//文件所属应用名称
	char	 szFilePath[MAX_FILE_PATH];		//文件路径
	WCHAR	 wzDstFile[MAX_FILE_PATH];		//目标文件路径
	int		 iPermission;					//安卓文件访问权限
	UINT64   u64Size;						//文件大小
	time_t   modifyTime;					//文件最后修改日期
}FILE_INFO, *LPFILE_INFO;


//
//过滤出的文件信息
typedef struct _FILTERED_FILE_IFNO 
{
	FILE_INFO		fileInfo;       //文件基本信息
	int				iType;			//0表示大文件，1表示扩展名文件
	int				iRow;           //该文件在界面tablewidget中对应的行数
	bool			bSelected;      //是否勾选
	bool			bComplete;      //是否获取完成
}FILTERED_FILE_IFNO, *LPFILTERED_FILE_IFNO;


//
//分区信息
#define IMAGE_NOT_SELECTED  0   //未选择
#define IMAGE_FINISHED		1   //已完成
#define IMAGE_BREAKPOINT    2	//断点
#define IMAGE_NOT_START     3	//选择但未开始
#define IMAGE_ERROR         -1  //失败

typedef struct _VOLUME_INFO
{
	char	szDirPath[MAX_DEV_LEN];   //目录路径
	char	szDevPath[MAX_DEV_LEN];   //设备路径
	char	szType[MAX_DEV_LEN];	  //文件系统类型
	UINT64	u64TtlSize;				  //分区总大小
	UINT64  u64UsedSize;			  //分区已使用大小

	int     iState;                   //镜像状态
	int     iRow;
	WCHAR	wzImgPath[MAX_FILE_PATH]; //镜像文件路径
}VOLUME_INFO, *LPVOLUME_INFO;


//
//回调函数

//传递设备基本信息，如名称、型号等
typedef void (WINAPI *LPFNDISPLAYBASEINFO)(DEV_INFO devInfo);

//更新应用获取状态
typedef void(WINAPI *LPFNUPDATEACQUIRESTATE)(LPWSTR lpwzCurApp, DWORD dwType);

//传递第三方应用信息给主界面
typedef void (WINAPI *LPFNADDTHIRDAPP)(APP_INFO appInfo);

//更新归档残留状态
typedef void (WINAPI *LPFNSETARCREMAIN)(char *lpszAppId);

#endif