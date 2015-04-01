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
#include <zlib.h>

#include <time.h>

#pragma comment(lib, "zlib.lib")

#define CHUNK 16384

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

	inline QString GetConfigValue(const QString& parentNodeName, const QString& nodeName, const QString& attribute)
	{
		QString config = Utils::wtoq(Utils::GetExePath() + L"\\config.xml");

		QFile xml(config);

		if ( !xml.open(QIODevice::ReadOnly | QIODevice::Text) )
			return "";

		QDomDocument doc;

		if ( !doc.setContent(&xml, false) )
			return "";

		QDomElement node = doc.documentElement().firstChildElement(parentNodeName).firstChildElement(nodeName);

		return node.attribute(attribute);
	}

	inline QString GetConfigValue(
		const QString& parentNodeName, 
		const QString& nodeName, 
		const QString& attribute, 
		const QString& attributeValue,
		const QString& queryAttribute)
	{
		QString config = Utils::wtoq(Utils::GetExePath() + L"\\config.xml");

		QFile xml(config);

		if ( !xml.open(QIODevice::ReadOnly | QIODevice::Text) )
			return "";

		QDomDocument doc;

		if ( !doc.setContent(&xml, false) )
			return "";

		QDomElement node = doc.documentElement().firstChildElement(parentNodeName).firstChildElement(nodeName);

		while ( !node.isNull() )
		{
			if ( node.attribute(attribute) == attributeValue )
				return node.attribute(queryAttribute);

			node = node.nextSiblingElement(nodeName);
		}

		return "";
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

	typedef int (WINAPI *ZlibUncompress)(char *dest, ULONG *destLen, const char *source, ULONG sourceLen);

	inline int DecompressFile(FILE *source, FILE *dest)
	{
		int ret;
		unsigned have;
		z_stream strm;
		unsigned char in[CHUNK];
		unsigned char out[CHUNK];

		/* allocate inflate state */
		strm.zalloc = Z_NULL;
		strm.zfree = Z_NULL;
		strm.opaque = Z_NULL;
		strm.avail_in = 0;
		strm.next_in = Z_NULL;
		ret = inflateInit(&strm);
		if (ret != Z_OK)
			return ret;

		/* decompress until deflate stream ends or end of file */
		do {
			strm.avail_in = fread(in, 1, CHUNK, source);
			if (ferror(source)) {
				(void)inflateEnd(&strm);
				return Z_ERRNO;
			}
			if (strm.avail_in == 0)
				break;
			strm.next_in = in;

			/* run inflate() on input until output buffer not full */
			do {
				strm.avail_out = CHUNK;
				strm.next_out = out;
				ret = inflate(&strm, Z_NO_FLUSH);
				//assert(ret != Z_STREAM_ERROR);  /* state not clobbered */
				switch (ret) {
			case Z_NEED_DICT:
				ret = Z_DATA_ERROR;     /* and fall through */
			case Z_DATA_ERROR:
			case Z_MEM_ERROR:
				(void)inflateEnd(&strm);
				return ret;
				}
				have = CHUNK - strm.avail_out;
				if (fwrite(out, 1, have, dest) != have || ferror(dest)) {
					(void)inflateEnd(&strm);
					return Z_ERRNO;
				}
			} while (strm.avail_out == 0);

			/* done when inflate() says it's done */
		} while (ret != Z_STREAM_END);

		/* clean up and return */
		(void)inflateEnd(&strm);
		return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
	}

	inline void ExtractBackUp(const std::wstring& file)
	{
		if ( !FileExist(file) )
			return;

		SetCurrentDirectoryW(GetExePath().c_str());
		std::wstring lzma = L"7z";

		std::wstring path = file.substr(0, file.rfind('\\'));
		std::wstring backupFileName = wcsrchr(file.c_str(), L'\\') + 1;
		std::wstring temp = path + L"\\temp";
		std::wstring tarFile = temp + L"\\1.tar";
		std::wstring appDirName = backupFileName.substr(0, backupFileName.length()-3);
		std::wstring tempAppDir = temp + L"\\apps";
		std::wstring finalAppDir = path;
		std::wstring backupFile = file + L"_";

		CreateDirectoryW(temp.c_str(), NULL);

		FILE* inputFile = fopen(WideToAnsi(file).c_str(), "rb");
		FILE* outputFile = fopen(WideToAnsi(tarFile).c_str(), "wb");
		fseek(inputFile, 24, SEEK_SET);
		DecompressFile(inputFile, outputFile);
		fclose(inputFile);
		fclose(outputFile);

		WCHAR cmd[1024] = {0};
		wsprintfW(cmd, L"%s x \"%s\" -o\"%s\" -y", lzma.c_str(), tarFile.c_str(), temp.c_str());
		_wsystem(cmd);

		std::wstring findStr = tempAppDir + L"\\*.*";
		WIN32_FIND_DATA fd = {0};

		HANDLE hf = FindFirstFile(findStr.c_str(), &fd);

		do 
		{
			if ( std::wstring(fd.cFileName) == L".."
				|| std::wstring(fd.cFileName) == L"." )
				continue;

			std::wstring src = tempAppDir + L"\\" + fd.cFileName;
			SHMove(src.c_str(), finalAppDir.c_str());

		} while ( FindNextFile(hf, &fd) );

		FindClose(hf);

		SHDel(temp.c_str());
		MoveFile(file.c_str(), backupFile.c_str());
	}

	inline HANDLE LogStart()
	{
		struct tm today = {0};
		time_t ltime;

		WCHAR timeStr[1024] = {0};

		_time64(&ltime); 
		_localtime64_s(&today, &ltime);

		wsprintfW(timeStr, L"%.4d-%.2d-%.2d %.2d;%.2d;%.2d",
			today.tm_year+1900, today.tm_mon+1, today.tm_mday,
			today.tm_hour, today.tm_min, today.tm_sec);

		std::wstring logDir = GetExePath() + L"\\Log";
		CreateDirectoryW(logDir.c_str(), NULL);

		std::wstring logFile = logDir + L"\\" + timeStr + L".log";

		HANDLE hf = CreateFile(logFile.c_str(), FILE_GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		char header[2] = {0xFF, 0xFE};
		DWORD written = 0;
		WriteFile(hf, header, 2, &written, NULL);

		return hf;

	}

	inline void Log(HANDLE hLogFile, const wchar_t* format, ...)
	{
		va_list vlArgs;
		WCHAR tzText[4096] = {0};
		va_start(vlArgs, format);
		wvsprintf(tzText, format, vlArgs);
		
		DWORD written = 0;
		SetFilePointer(hLogFile, 0, 0, FILE_END);
		WriteFile(hLogFile, tzText, wcslen(tzText)*2, &written, NULL);

		va_end(vlArgs);
	}

	inline void LogEnd(HANDLE hLogFile)
	{
		if ( INVALID_HANDLE_VALUE != hLogFile )
			CloseHandle(hLogFile);
	}
}

#endif // UTILS_H