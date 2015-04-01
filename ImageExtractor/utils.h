#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <QString>
#include <Windows.h>
#include <QFile>
#include <QTextStream>
#include <list>
#include <TlHelp32.h>
#include <QDomDocument>
#include <QApplication>
#include <QWidget>

namespace Utils
{
	inline std::wstring GetExePath()
	{
		WCHAR path[MAX_PATH] = {0};
		GetModuleFileNameW(NULL, path, MAX_PATH);
		*wcsrchr(path, '\\') = L'\0';
		return std::wstring(path);
	}

	inline QString wtoq(std::wstring w)
	{
		return QString::fromStdWString(w);
	}

	inline QString stoq(std::string s)
	{
		return QString::fromLocal8Bit(s.c_str());
	}

	inline QString utoq(std::string s)
	{
		return QString::fromUtf8(s.c_str());
	}

	inline std::wstring qtow(QString s)
	{
		return s.toStdWString();
	}

	inline std::string qtos(QString s)
	{
		return std::string(s.toLocal8Bit());
	}

	inline std::string qtou(QString s)
	{
		return std::string(s.toUtf8());
	}

	inline std::wstring AnsiToWide(std::string s)
	{
		WCHAR tmp[4096] = {0};
		MultiByteToWideChar(CP_ACP, 0, s.c_str(), -1, tmp, 4096);

		return std::wstring(tmp);
	}

	inline std::string WideToAnsi(std::wstring w)
	{
		char tmp[4096] = {0};
		WideCharToMultiByte(CP_ACP, 0, w.c_str(), -1, tmp, 4096, NULL, NULL);

		return std::string(tmp);
	}

	inline std::wstring Utf8ToWide(std::string s)
	{
		WCHAR tmp[4096] = {0};
		MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, tmp, 4096);

		return std::wstring(tmp);
	}

	inline std::string Utf8ToGbk(std::string s)
	{
		return WideToAnsi(Utf8ToWide(s));
	}

	inline void CastChar(char* p, char charToCast)
	{		
		while ( *p != 0 )
		{
			if ( *p == charToCast )
				*p = 0;
			else
				++p;
		}
	}

	inline std::wstring FilterChar(std::wstring& s, wchar_t charToFilter)
	{
		WCHAR dst[100] = {0};

		const wchar_t* p = s.c_str();
		wchar_t* q = dst;

		while ( *p != L'\0' )
		{
			if ( *p != charToFilter )
				*q++ = *p;

			++p;
		}

		*q = L'\0';

		return std::wstring(dst);
	}

	inline bool FileExist(const std::wstring& path)
	{
		DWORD dwResult = GetFileAttributesW(path.c_str());

		if ( 0xFFFFFFFF == dwResult )
			return false;

		if ( INVALID_FILE_ATTRIBUTES == dwResult 
			&& ERROR_FILE_NOT_FOUND == GetLastError() )
			return false;

		return true;
	}

	inline std::list<std::string> SplitLines(std::string s, char spliter)
	{
		std::list<std::string> result;
		std::string::size_type pos = 0;

		if ( s[s.length()-1] != '|' )
			s.push_back('|');

		while ( std::string::npos != (pos = s.find(spliter)) )
		{
			result.push_back(s.substr(0, pos));
			s = s.substr(pos+1, s.length()-pos-1);
		}

		return result;
	}

	inline void __TRACE(const wchar_t* format, ...)
	{
#ifdef _TRACE_DEBUG
		va_list vlArgs;
		WCHAR tzText[4096];
		va_start(vlArgs, format);
		wvsprintf(tzText, format, vlArgs);
		OutputDebugString(tzText);
		va_end(vlArgs);
#endif
	}

	inline void __TRACE(const char* format, ...)
	{
#ifdef _TRACE_DEBUG
		va_list vlArgs;
		char* tzText = new char[1024*1024];
		va_start(vlArgs, format);
		vsprintf(tzText, format, vlArgs);
		OutputDebugStringA(tzText);
		va_end(vlArgs);
		delete [] tzText;
#endif
	}

	inline void InitStyle(QWidget* w)
	{
		QFile qss(Utils::wtoq(Utils::GetExePath() + L"\\common_style.qss"));

		if ( !qss.open(QIODevice::ReadOnly | QIODevice::Text) )
			return;

		QTextStream ts(&qss);
		w->setStyleSheet(ts.readAll());
	}

	inline bool SHMove(LPCWSTR from, LPCWSTR to)
	{
		SHFILEOPSTRUCT fileOp = {0};
		fileOp.wFunc = FO_MOVE;
		TCHAR newFrom[MAX_PATH];
		wcscpy(newFrom, from);
		newFrom[wcslen(from) + 1] = NULL;
		fileOp.pFrom = newFrom;
		WCHAR newTo[MAX_PATH];
		wcscpy(newTo, to);
		newTo[wcslen(to) + 1] = NULL;
		fileOp.pTo = newTo;
		fileOp.fFlags = FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_NOCONFIRMMKDIR;

		int result = SHFileOperation(&fileOp);

		return result == 0;
	}

	inline bool SHDel(LPCWSTR dir)
	{
		WCHAR wzTemp[MAX_PATH] = {0};
		wcscpy(wzTemp, dir);
		SHFILEOPSTRUCTW FileOp;
		FileOp.fFlags = FOF_SILENT | FOF_NOCONFIRMATION | FOF_NOERRORUI;
		FileOp.pFrom = wzTemp;
		FileOp.pTo = NULL;
		FileOp.wFunc = FO_DELETE;
		int result = SHFileOperationW(&FileOp);
		return result == 0;
	}

	inline void ExecuteProcessSync(wchar_t* parameters)
	{
		PROCESS_INFORMATION piProcInfo = {0}; 
		STARTUPINFO siStartInfo = {0};

		siStartInfo.wShowWindow = SW_HIDE;

		if ( !CreateProcessW(
			NULL,
			parameters, 
			NULL, 
			NULL,
			TRUE, 
			CREATE_NO_WINDOW, 
			NULL, 
			NULL,
			&siStartInfo, 
			&piProcInfo) )
		{
			Utils::__TRACE(L"[ExecuteProcessSync] CreateProcessW failed. [%d] [%s] \r\n", GetLastError(), parameters);
			return;
		}

		WaitForSingleObject(piProcInfo.hProcess, INFINITE);

		CloseHandle(piProcInfo.hProcess);
		CloseHandle(piProcInfo.hThread);
	}

	inline void ExtractPackage(const std::wstring& package)
	{
		SetCurrentDirectoryW(GetExePath().c_str());
		std::wstring lzma = GetExePath() + L"\\7z.exe";
		std::wstring path = package.substr(0, package.rfind('\\'));
		std::wstring packageName = wcsrchr(package.c_str(), L'\\') + 1;
		std::wstring tarName = packageName.substr(0, packageName.length()-3);
		std::wstring dirName = packageName.substr(0, packageName.length()-7);
		std::wstring tempPath = path + L"\\temp";
		std::wstring tempTar = tempPath + L"\\" + tarName;

		CreateDirectoryW(tempPath.c_str(), NULL);

		WCHAR cmd[1024] = {0};
		wsprintfW(cmd, L"\"%s\" x \"%s\" -o\"%s\"", lzma.c_str(), package.c_str(), tempPath.c_str());
		__TRACE(L"[ExtractPackage] %s\r\n", cmd);
		ExecuteProcessSync(cmd);
		//_wsystem(cmd);

		wsprintfW(cmd, L"\"%s\" x \"%s\" -o\"%s\"", lzma.c_str(), tempTar.c_str(), tempPath.c_str());
		__TRACE(L"[ExtractPackage] %s\r\n", cmd);
		ExecuteProcessSync(cmd);
		//_wsystem(cmd);

		std::wstring src = tempPath + L"\\data\\data\\" + dirName;
		std::wstring dst = path + L"\\" + dirName;

		SHMove(src.c_str(), dst.c_str());
		SHDel(tempPath.c_str());
	}

	inline bool FindProcess(LPCTSTR szProcessName, HANDLE& processHandle)
	{
		HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		PROCESSENTRY32W process = {0};
		process.dwSize = sizeof(PROCESSENTRY32W);
		Process32FirstW(hSnapShot, &process);

		bool bRet = FALSE;

		do
		{
			if ( 0 == wcscmp(process.szExeFile, szProcessName) )
			{
				processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, process.th32ProcessID);
				bRet = true;
				break;
			}

		} while ( Process32NextW(hSnapShot, &process) );

		CloseHandle(hSnapShot);
		return bRet;
	}

	inline QString GetConfigValue(const QString& nodeName, const QString& attribute)
	{
		QString config = Utils::wtoq(Utils::GetExePath() + L"\\config.xml");

		QFile xml(config);

		if ( !xml.open(QIODevice::ReadOnly | QIODevice::Text) )
			return "";

		QDomDocument doc;

		if ( !doc.setContent(&xml, false) )
			return "";

		QDomElement node = doc.documentElement().firstChildElement(nodeName);

		return node.attribute(attribute);
	}

	inline QString GetNodeValue(const QString& nodeName, const QString& attribute)
	{
		QString config = Utils::wtoq(Utils::GetExePath() + L"\\config.xml");

		QFile xml(config);

		if ( !xml.open(QIODevice::ReadOnly | QIODevice::Text) )
			return "";

		QDomDocument doc;

		if ( !doc.setContent(&xml, false) )
			return "";

		QDomElement node = doc.documentElement().firstChildElement("layout");
		QDomNodeList children = node.childNodes();

		for ( int i = 0; i < children.count(); ++i )
		{
			QDomElement item = children.at(i).toElement();

			if ( item.attribute("label") == nodeName )
				return item.attribute(attribute);

			QDomNodeList grandChildren = item.childNodes();

			for ( int j = 0; j < grandChildren.count(); ++j )
			{
				QDomElement item = grandChildren.at(j).toElement();

				if ( item.attribute("label") == nodeName )
					return item.attribute(attribute);
			}
		}

		return "";
	}

	inline bool HaveFlashDisk(std::wstring& path)
	{
		wchar_t rootPath[MAX_PATH] = L"C:\\";

		for ( WCHAR driver = L'a'; driver <= L'z'; ++driver )
		{
			rootPath[0] = driver;

			UINT ret = GetDriveTypeW(rootPath);

			if ( (ret == DRIVE_REMOVABLE || ret == DRIVE_FIXED )
				&& Utils::FileExist(std::wstring(rootPath) + L"mark") )
			{
				path = rootPath;
				return true;
			}
		}

		return false;
	}

}

#endif // UTILS_H