#include "FileIODevice.h"

namespace DIYV
{

FileIODevice::FileIODevice()
{
}

void FileIODevice::open(const std::string &fileName)
{
    _stream.open(fileName, std::ios::out | std::ios::app);
}

void FileIODevice::write(char c)
{
    _stream << c;
}

void FileIODevice::write(const char *str)
{
    _stream << str;
}

void FileIODevice::flush()
{
    _stream.flush();
}

bool FileIODevice::read(char &)
{
    return false;
}


}

