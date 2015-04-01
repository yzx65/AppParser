
#include "stdafx.h"
#include "androidimageadapter.h"
#include "utils.h"

#include "ext2read.h"

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

        filetosave.append(QString::fromAscii("/"));
        filetosave.append(codec->toUnicode(child->file_name.c_str()));
        ret = copy_file(filetosave, child, buffer, blksize);
    }

	delete [] buffer;
	
    return true;
}

void MergeImageFile(const std::wstring& imageFile)
{
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

	wsprintfW(cmd, L"cmd.exe /c copy /b %s \"%s\"", files.c_str(), imageFile.c_str());

	Utils::ExecuteProcessSync(cmd);
}

bool AndroidImageAdapter::ExtractImageFile(const std::wstring& imageFile)
{
	if ( !Utils::FileExist(imageFile)
		&& !Utils::FileExist(imageFile + L".000") )
		return false;

	std::wstring path = imageFile.substr(0, imageFile.rfind(L'\\'));

	if ( Utils::FileExist(path + L"\\data") )
		return false;

	if ( !Utils::FileExist(imageFile) )
		MergeImageFile(imageFile);

	Ext2Read parser;
	parser.add_loopback(Utils::WideToAnsi(imageFile).c_str());

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
		return false;


	if ( !EXT2_S_ISDIR(root->inode.i_mode) )
		return false;

	if ( root->onview )
		return false;

	Ext2Partition* partition = root->partition;
	EXT2DIRENT* dir = partition->open_dir(root);

	Ext2File* file = NULL;

	while( (file = partition->read_dir(dir)) != NULL )
	{
		if ( file->file_name == "data" )
			break;
	}

	partition->close_dir(dir);

	if ( file->file_name != "data" )
		return false;

	copy_folder(Utils::wtoq(path), file);

	std::wstring findStr = path + L"\\data\\*.*";
	WIN32_FIND_DATA fd = {0};

	HANDLE hf = FindFirstFile(findStr.c_str(), &fd);

	if ( INVALID_HANDLE_VALUE == hf )
		return false;

	do 
	{
		if ( 0 == wcscmp(fd.cFileName, L"..")
			|| 0 == wcscmp(fd.cFileName, L".") )
			continue;

		std::wstring src = path + L"\\data\\" + fd.cFileName;
		std::wstring dst = path + L"\\" + fd.cFileName;

		Utils::SHMove(src.c_str(), dst.c_str());

	} while ( FindNextFile(hf, &fd) );

	return true;
}