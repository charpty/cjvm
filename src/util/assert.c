#include <stdlib.h>
#include <string.h>
#include "log.c"
#include "assert.h"

void assertEquals(char *s, char *d, char *format, ...)
{
    if (strcmp(s, d) != 0)
    {
        char buf[256] = {0};
        va_list list;
        va_start(list, format);
        vsprintf(buf, format, list);
        va_end(list);
        LOG_ERROR("%s, s is %s, d is %s", buf, s, d);
        exit(1);
    }
}

void assertExpress(int express, char *format, ...)
{
    if (!express)
    {
        char buf[256] = {0};
        va_list list;
        va_start(list, format);
        vsprintf(buf, format, list);
        va_end(list);
        LOG_ERROR("%s", buf);
        exit(1);
    }
}
