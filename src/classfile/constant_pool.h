#ifndef MOON_CONSTANT_POOL_H
#define MOON_CONSTANT_POOL_H

#include <stdlib.h>

#include "classreader.h"
#include "util/util.h"

#define CONSTANT_Class 7
#define CONSTANT_Fieldref 9
#define CONSTANT_Methodref 10
#define CONSTANT_InterfaceMethodref 11
#define CONSTANT_String 8
#define CONSTANT_Integer 3
#define CONSTANT_Float 4
#define CONSTANT_Long 5
#define CONSTANT_Double 6
#define CONSTANT_NameAndType 12
#define CONSTANT_Utf8 1
#define CONSTANT_MethodHandle 15
#define CONSTANT_MethodType 16
#define CONSTANT_InvokeDynamic 18

typedef struct NameAndType
{
    char *name;
    u_int32_t nameLen;
    char *type;
    u_int32_t typeLen;
} NameAndType;

typedef struct CPInfo
{
    uint8_t tag;
    // 常量池里存着各种各样类型的信息
    void *v1;
    void *v2;
} CPInfo;

// 用Cp表示class里的常量池，运行期的常量池则用GCP来表示，更亲切
typedef struct CP
{
    uint32_t len;
    CPInfo **infos;
} CP;

#endif