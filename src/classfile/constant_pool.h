#ifndef MOON_CONSTANT_POOL_H
#define MOON_CONSTANT_POOL_H

#include <stdlib.h>

#include "classfile/classreader.h"
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
    char *type;
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

static CPInfo *readConstantInfo(ClassReader *r, CP *cp)
{
    CPInfo *rs = (CPInfo *)malloc(sizeof(struct CPInfo));
    uint8_t tag = rs->tag = readUint8(r);
    if (tag == CONSTANT_Class)
    {
        // nameIndex
        // 存储class存储的位置索引
        rs->v1 = malloc(sizeof(uint16_t));
        *(uint16_t *)rs->v1 = readUint16(r);
    }
    else if (tag == CONSTANT_Fieldref)
    {
        // classIndex and nameAndTypeIndex
        rs->v1 = malloc(sizeof(uint16_t));
        rs->v2 = malloc(sizeof(uint16_t));
        *(uint16_t *)rs->v1 = readUint16(r);
        *(uint16_t *)rs->v2 = readUint16(r);
    }
    else if (tag == CONSTANT_Methodref)
    {
        // classIndex and nameAndTypeIndex
        rs->v1 = malloc(sizeof(uint16_t));
        rs->v2 = malloc(sizeof(uint16_t));
        *(uint16_t *)rs->v1 = readUint16(r);
        *(uint16_t *)rs->v2 = readUint16(r);
    }
    else if (tag == CONSTANT_InterfaceMethodref)
    {
        // classIndex and nameAndTypeIndex
        rs->v1 = malloc(sizeof(uint16_t));
        rs->v2 = malloc(sizeof(uint16_t));
        *(uint16_t *)rs->v1 = readUint16(r);
        *(uint16_t *)rs->v2 = readUint16(r);
    }
    else if (tag == CONSTANT_String)
    {
        // stringIndex
        rs->v1 = malloc(sizeof(uint16_t));
        *(uint16_t *)rs->v1 = readUint16(r);
    }
    else if (tag == CONSTANT_Integer)
    {
        // int32 value
        rs->v1 = malloc(sizeof(uint32_t));
        *(uint32_t *)rs->v1 = readUint32(r);
    }
    else if (tag == CONSTANT_Float)
    {
        // TODO float value
        rs->v1 = malloc(sizeof(uint32_t));
        *(uint32_t *)rs->v1 = readUint32(r);
    }
    else if (tag == CONSTANT_Long)
    {
        // int64 value
        rs->v1 = malloc(sizeof(uint64_t));
        *(uint64_t *)rs->v1 = readUint64(r);
    }
    else if (tag == CONSTANT_Double)
    {
        // TODO double value
        rs->v1 = malloc(sizeof(uint64_t));
        *(uint64_t *)rs->v1 = readUint64(r);
    }
    else if (tag == CONSTANT_NameAndType)
    {
        // nameIndex and descriptorIndex
        rs->v1 = malloc(sizeof(uint16_t));
        rs->v2 = malloc(sizeof(uint16_t));
        *(uint16_t *)rs->v1 = readUint16(r);
        *(uint16_t *)rs->v2 = readUint16(r);
    }
    else if (tag == CONSTANT_Utf8)
    {
        // make this C String,
        uint32_t len = (uint32_t)readUint16(r);
        char *x = readBytes(r, len);
        rs->v1 = (char *)malloc(len + 1);
        memset(rs->v1, 0, len + 1);
        memcpy(rs->v1, x, len);
        for (int i = 0; i < len; i++)
        {
            printf("char=%u\n", x[i]);
        }
        printf("len=%d, str=%s\n", len, rs->v1);
    }
    else if (tag == CONSTANT_MethodHandle)
    {
        // referenceKind and referenceIndex
        rs->v1 = malloc(sizeof(uint8_t));
        rs->v2 = malloc(sizeof(uint16_t));
        *(uint8_t *)rs->v1 = readUint8(r);
        *(uint16_t *)rs->v2 = readUint16(r);
    }
    else if (tag == CONSTANT_MethodType)
    {
        // descriptorIndex
        rs->v1 = malloc(sizeof(uint16_t));
        *(uint16_t *)rs->v1 = readUint32(r);
    }
    else if (tag == CONSTANT_InvokeDynamic)
    {
        // bootstrapMethodAttrIndex and nameAndTypeIndex
        rs->v1 = malloc(sizeof(uint16_t));
        rs->v2 = malloc(sizeof(uint16_t));
        *(uint16_t *)rs->v1 = readUint16(r);
        *(uint16_t *)rs->v2 = readUint16(r);
    }
    // assertExpress(0, "unknow tag: %d", tag);
    return rs;
}

static CP *readConstantPool(ClassReader *r)
{
    CP *rs = (CP *)malloc(sizeof(struct CP));
    int cpCount = readUint16(r);
    rs->len = cpCount;
    rs->infos = (CPInfo **)malloc(cpCount * sizeof(CPInfo *));

    // 常量池从下标1开始
    for (int i = 1; i < cpCount; i++)
    {
        rs->infos[i] = readConstantInfo(r, rs);
        // http://docs.oracle.com/javase/specs/jvms/se8/html/jvms-4.html#jvms-4.4.5
        // 这就是个数的特殊情况，读到long和double时，必须下一个元素是个空，以兼容老版本
        // 这是由于一个byte占常量池2个位置
        if (rs->infos[i]->tag == CONSTANT_Long || (rs->infos[i]->tag == CONSTANT_Double))
        {
            ++i;
            continue;
        }
    }
    return rs;
}

static char *getUtf8(CP *cp, uint16_t index)
{
    CPInfo *ci = cp->infos[index];
    return (char *)ci->v1;
}

// make this C string? hate '\0'
// use sds? miss some useful function
static char *getClassName(CP *cp, uint16_t index)
{
    return getUtf8(cp, index);
}

static NameAndType *getNameAndType(CP *cp, uint16_t index, char **type)
{
    struct NameAndType *rs = (NameAndType *)malloc(sizeof(struct NameAndType));
    CPInfo *ci = cp->infos[index];
    u_int16_t nameIndex = *(u_int16_t *)ci->v1;
    u_int16_t typeIndex = *(u_int16_t *)ci->v2;
    rs->name = getUtf8(cp, nameIndex);
    rs->type = getUtf8(cp, typeIndex);
    return rs;
}

#endif