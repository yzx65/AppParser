#ifndef ANDROIDIMAGEADAPTER_H
#define ANDROIDIMAGEADAPTER_H

#include <string>

class AndroidImageAdapter
{
public:
	static bool ExtractImageFile(const std::wstring& imageFile);
};

#endif // ANDROIDIMAGEADAPTER_H