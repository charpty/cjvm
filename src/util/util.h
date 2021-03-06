#ifndef MOON_UTIL_H
#define MOON_UTIL_H

#include <stdlib.h>

/* log */

void LOG_DEBUG(char *format, ...);
void LOG_INFO(char *format, ...);
void LOG_WARN(char *format, ...);
void LOG_ERROR(char *file, int line, char *format, ...);

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"
#define KYEL "\x1B[33m"
#define KBLU "\x1B[34m"
#define KMAG "\x1B[35m"
#define KCYN "\x1B[36m"
#define KWHT "\x1B[37m"

/* assert */
void assertEquals(char *s, char *d, char *message, ...);
void assertExpress(int express, char *format, ...);

/* files */
typedef struct XFile
{
    // 文件路径：/tmp/cc.jar; /tmp/com/charpty/Test.class
    char *path;
    char *name;
    uint32_t len;
    char *data;
} XFile;

typedef struct XFiles
{
    uint32_t len;
    XFile **files;
} XFiles;

XFile *readFile(char *filepath);
XFiles *listDir(char *dir, char *suffix, int recursive);

/* misc */
int64_t doubleToInt64(double s);
int32_t floatToInt32(float s);

#endif