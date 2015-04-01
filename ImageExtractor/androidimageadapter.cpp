
#include "androidimageadapter.h"
#include "utils.h"

#include "ext2read.h"
#include "imageextractor.h"

#include <QtGui>


bool copy_file(QString &destfile, Ext2File *srcfile, char* buffer, int blksize)
{
	QTextCodec* codec = QTextCodec::codecForName("utf-8");
    lloff_t blocks, blkindex;
    QString qsrc;
    QString nullstr = QString::fromAscii("");
    QByteArray ba;
    int extra;
    int ret;

	qDebug() << destfile;

    QFile* filetosave = new QFile(destfile);

    if ( !filetosave->open(QIODevice::ReadWrite | QIODevice::Truncate) )
    {
        LOG("Error creating file %s.\n", srcfile->file_name.c_str());
        return false;
    }

    qsrc = codec->toUnicode(srcfile->file_name.c_str());
    blocks = srcfile->file_size / blksize;

    for( blkindex = 0; blkindex < blocks; blkindex++ )
    {
        ret = srcfile->partition->read_data_block(&srcfile->inode, blkindex, buffer);

        if( ret < 0 )
        {
            filetosave->close();
            return false;
        }

        filetosave->write( buffer, blksize );
    }

    extra = srcfile->file_size % blksize;

    if(extra)
    {
        ret = srcfile->partition->read_data_block(&srcfile->inode, blkindex, buffer);

        if(ret < 0)
        {
            filetosave->close();
            return false;
        }

        filetosave->write(buffer, extra);
    }

    filetosave->close();
    return true;
}

bool copy_folder(QString &path, Ext2File *parent)
{
	int blksize = parent->partition->get_blocksize();
	char* buffer = new char [blksize];
	memset(buffer, 0, blksize);

    QDir dir(path);
    QString filetosave;
    QString rootname = path;
    EXT2DIRENT *dirent;
    Ext2Partition *part = parent->partition;
    Ext2File *child;
    QByteArray ba;
    bool ret;

	QTextCodec* codec = QTextCodec::codecForName("utf-8");

    if ( !EXT2_S_ISDIR(parent->inode.i_mode) )
	{
		delete [] buffer;
        return false;
	}

    dir.mkdir(codec->toUnicode(parent->file_name.c_str()));

    dirent = part->open_dir(parent);

    while( (child = part->read_dir(dirent)) != NULL )
    {
        filetosave = rootname;
        filetosave.append(QString::fromAscii("/"));
        filetosave.append(codec->toUnicode(parent->file_name.c_str()));

        if( EXT2_S_ISDIR(child->inode.i_mode) )
        {
            ret = copy_folder(filetosave, child);
            continue;
        }

        else if( ! EXT2_S_ISREG(child->inode.i_mode) )
        {
            continue;
        }

		if ( child->file_name.empty() )
			break;

        filetosave.append(QString::fromAscii("/"));
        filetosave.append(codec->toUnicode(child->file_name.c_str()));
        ret = copy_file(filetosave, child, buffer, blksize);
    }

	delete [] buffer;
	
    return true;
}

void MergeImageFile(const std::wstring& imageFile, const std::wstring& outputPath)
{
	std::wstring imageName = wcsrchr(imageFile.c_str(), L'\\') + 1;

	int count = 0;

	for ( ; count < 10; ++count )
	{
		wchar_t fileName[MAX_PATH] = {0};
		wsprintfW(fileName, L"%s.00%d", imageFile.c_str(), count);

		if ( !Utils::FileExist(fileName) )
			break;
	}

	wchar_t cmd[1024] = {0};
	std::wstring files;

	for ( int i = 0; i < count; ++i )
	{
		wchar_t file[256] = {0};
		wsprintfW(file, L"%s.00%d", imageFile.c_str(), i);

		if ( i == count - 1 )
			files = files + std::wstring(L"\"") + file + std::wstring(L"\"");
		else
			files = files + std::wstring(L"\"") + file + std::wstring(L"\"") + L"+";
	}

	wsprintfW(cmd, L"cmd.exe /c copy /b %s \"%s\\%s\"", files.c_str(), outputPath.c_str(), imageName.c_str());

	if ( !Utils::FileExist(outputPath + L"\\" + imageName) )
		Utils::ExecuteProcessSync(cmd);
}

std::list<std::wstring> GetImageList(const std::wstring& srcPath)
{
	WIN32_FIND_DATA fd = {0};

	std::wstring findStr = srcPath + L"\\*.000";

	HANDLE hf = FindFirstFile(findStr.c_str(), &fd);

	std::list<std::wstring> result;

	if ( INVALID_HANDLE_VALUE == hf )
		return result;
	do 
	{
		std::wstring fileName = fd.cFileName;

		if ( fileName == L"StorageImage.000" )
			continue;
		
		result.push_back(fileName.substr(0, fileName.length()-4));

	} while ( FindNextFile(hf, &fd) );

	FindClose(hf);

	return result;
}

bool AndroidImageAdapter::ExtractImageFile(const std::wstring& srcPath, const std::wstring& dstPath, bool extractFile, WorkThread* worker)
{
	std::list<std::wstring> imageList = GetImageList(srcPath);

	if ( worker )
		worker->SetStatus(Utils::stoq("正在合并镜像文件 ..."));

	for ( std::list<std::wstring>::iterator it = imageList.begin();
		  it != imageList.end();
		  ++it )
	{
		MergeImageFile(srcPath + L"\\" + *it, dstPath);
	}

	if ( !extractFile )
		return true;

	if ( worker )
		worker->SetStatus(Utils::stoq("正在释放镜像文件 ..."));

	bool ret = false;

	for ( std::list<std::wstring>::iterator it = imageList.begin();
		it != imageList.end();
		++it )
	{
		Ext2Read parser;
		parser.add_loopback(Utils::WideToAnsi(dstPath + L"\\" + *it).c_str());

		std::list<Ext2Partition *> parts = parser.get_partitions();

		Ext2File* root = NULL;

		for ( std::list<Ext2Partition*>::iterator it = parts.begin();
			  it != parts.end();
			  ++it )
		{
			Ext2Partition* partition = (*it);

			if ( !partition->get_root() )
				continue;

			root = partition->get_root();
		}

		if ( NULL == root )
			continue;


		if ( !EXT2_S_ISDIR(root->inode.i_mode) )
			continue;

		if ( root->onview )
			continue;

		Ext2Partition* partition = root->partition;
		EXT2DIRENT* dir = partition->open_dir(root);

		Ext2File* file = NULL;

		while( (file = partition->read_dir(dir)) != NULL )
		{
			if ( file->file_name == "data" )
				break;
		}

		partition->close_dir(dir);

		if ( !file || file->file_name != "data" )
			continue;

		if ( copy_folder(Utils::wtoq(dstPath), file) )
			ret = true;

		std::wstring findStr = dstPath + L"\\data\\*.*";
		WIN32_FIND_DATA fd = {0};

		HANDLE hf = FindFirstFile(findStr.c_str(), &fd);

		if ( INVALID_HANDLE_VALUE == hf )
			continue;

		do 
		{
			if ( 0 == wcscmp(fd.cFileName, L"..")
				|| 0 == wcscmp(fd.cFileName, L".") )
				continue;

			std::wstring src = dstPath + L"\\data\\" + fd.cFileName;
			std::wstring dst = dstPath + L"\\" + fd.cFileName;

			Utils::SHMove(src.c_str(), dst.c_str());

		} while ( FindNextFile(hf, &fd) );
	}

	if ( worker && !ret )
		worker->SetInformation(Utils::stoq("未找到 data 目录\r\n导出镜像内文件失败"));

	return ret;
}