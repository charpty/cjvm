#ifndef MOON_CLASSPATH_H
#define MOON_CLASSPATH_H

#include <stdlib.h>

/*
 * 将指定class文件加载到内存中
 * 
 * 启动类路径
 * 扩展类路径
 * 用户类路径 
 */
typedef struct ClassPath
{
    char *bootStrapPath;
    char *extPath;
    char *userPath;
    struct SClass *(*readClass)(struct ClassPath *classPath, char *classname);
} ClassPath;

typedef struct SClass
{
    uint32_t len;
    char *bytes;
    char *name;
} SClass;

ClassPath *buildClassPath(char *jrePath, char *cpPath);

SClass *readClass(ClassPath *classPath, char *classname);

#endif