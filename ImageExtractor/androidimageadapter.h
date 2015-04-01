#ifndef ANDROIDIMAGEADAPTER_H
#define ANDROIDIMAGEADAPTER_H

#include <string>

class WorkThread;
class AndroidImageAdapter
{
public:
	static bool ExtractImageFile(const std::wstring& srcPath, const std::wstring& dstPath, bool extractFile, WorkThread* worker = 0);
};

#endif // ANDROIDIMAGEADAPTER_H