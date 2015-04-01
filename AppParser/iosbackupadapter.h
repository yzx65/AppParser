
#ifndef IOSBACKUPADAPTER_H
#define IOSBACKUPADAPTER_H

/*!
\brief
	Used to separate the ios 'Backup' directory to a new device
*/
class IosBackupAdapter
{
public:
	static void SeparateDir(const std::wstring& dataDir);
	static bool UnBackup(const std::wstring& appDir, const std::string& password = "");
	static void GenerateKeyChain(const std::wstring& appDir);
};

#endif // IOSBACKUPADAPTER_H