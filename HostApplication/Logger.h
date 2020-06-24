#ifndef LOGGER_H
#define LOGGER_H

#include <stdarg.h>

namespace DIYV
{
    void log(const char* format, va_list ap);
}

#define LOG(text) log("%s %s\n", __FUNCTION__, text)

#endif // LOGGER_H
