
#include <stdio.h>
#include <stdarg.h>
#include "log.h"

void logDebug(char *file, int line, char *format, ...)
{
    char buf[256] = {0};
    va_list list;
    va_start(list, format);
    vsprintf(buf, format, list);
    printf("%s:%d >> %s\n", file, line, buf);
    va_end(list);
}

void logError(char *file, int line, char *format, ...)
{
    char buf[256] = {0};
    va_list list;
    va_start(list, format);
    vsprintf(buf, format, list);
    printf("%s%s:%d >> %s\n", KRED, file, line, buf);
    va_end(list);
}