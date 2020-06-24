#ifndef _DISPLAYIODEVICE_
#define _DISPLAYIODEVICE_

#include <modm/io/iostream.hpp>

namespace DIYV
{
template <typename T>
class DisplayIODevice : public modm::IODevice
{
public:
    DisplayIODevice(T& device) : _device(device) {}

    virtual
    ~DisplayIODevice() = default;

    /// Write a single character
    virtual void
    write(char c)
    {
        _device << c;
    }

    virtual inline void
    write(const char* str)
    {
        _device.setCursor(0,50);
        char c;
        while ( (c = *str++) ) write(c);
    }

    virtual void
    flush()
    {
        write("                         ");
    }

    virtual bool
    read(char&){ return false; };

private:
    T& _device;
};
}

#endif