#include "Logger.h"

#include <stdio.h>

namespace DIYV
{

void log(const char *format, va_list ap)
{
    auto logFile = fopen("HostApplication.log", "a");
    vfprintf(logFile, format, ap);
    fclose(logFile);
}

}

