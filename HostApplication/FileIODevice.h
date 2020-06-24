#ifndef FILEIODEVICE_H
#define FILEIODEVICE_H

#include <modm/io/iodevice.hpp>

#include <string>
#include <fstream>

namespace DIYV
{

class FileIODevice : public modm::IODevice
{
public:
    FileIODevice();

    void open(const std::string& fileName);

    virtual ~FileIODevice() = default;

    /// Write a single character
    void write(char c) override;

    virtual void write(const char* str) override;

    void flush() override;

    bool read(char&) override;;

private:
    std::fstream _stream;
};

}
#endif // FILEIODEVICE_H
