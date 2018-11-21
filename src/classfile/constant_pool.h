#include <stdlib.h>
#include <classreader.h>
#include "assert.c"

const int CONSTANT_Class = 7;
const int CONSTANT_Fieldref = 9;
const int CONSTANT_Methodref = 10;
const int CONSTANT_InterfaceMethodref = 11;
const int CONSTANT_String = 8;
const int CONSTANT_Integer = 3;
const int CONSTANT_Float = 4;
const int CONSTANT_Long = 5;
const int CONSTANT_Double = 6;
const int CONSTANT_NameAndType = 12;
const int CONSTANT_Utf8 = 1;
const int CONSTANT_MethodHandle = 15;
const int CONSTANT_MethodType = 16;
const int CONSTANT_InvokeDynamic = 18;

typedef struct NameAndType
{
    char *name;
    u_int32_t nameLen;
    char *type;
    u_int32_t typeLen;
} NameAndType;

typedef struct CpInfo
{
    uint8_t tag;
    void *v1;
    void *v2;
} CpInfo;

typedef struct Cp
{
    int len;
    CpInfo **infos;
} Cp;

CpInfo *readConstantInfo(ClassReader *r, Cp *cp)
{
    CpInfo *rs = (CpInfo *)malloc(sizeof(struct CpInfo));
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
        // len and char*
        uint32_t len = (uint32_t)readUint16(r);
        uint32_t size;
        char *x = readBytes(r, len, &size);
        rs->v1 = malloc(sizeof(uint32_t));
        *(uint32_t *)rs->v1 = len;
        rs->v2 = x;
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
    assertExpress(0, "unknow tag: %d", tag);
    return NULL;
}

Cp *readConstantPool(ClassReader *r)
{
    Cp *rs = (Cp *)malloc(sizeof(struct Cp));

    int cpCount = readUint16(r);
    rs->infos = (CpInfo **)malloc(cpCount * sizeof(CpInfo *));

    for (int i = 0; i < cpCount; i++)
    {
        rs->infos[i] = readConstantInfo(r, rs);
        // http://docs.oracle.com/javase/specs/jvms/se8/html/jvms-4.html#jvms-4.4.5
        // 这就是个数的特殊情况，读到long和double时，必须下一个元素是个空，以兼容老版本
        // 这是由于一个byte占常量池2个位置
        if (rs->infos[i]->tag == CONSTANT_Long || (rs->infos[i]->tag = CONSTANT_Double))
        {
            i++;
            continue;
        }
    }
    return rs;
}

NameAndType *getNameAndType(Cp *cp, uint16_t index, char **type)
{
    struct NameAndType *rs = (NameAndType *)malloc(sizeof(struct NameAndType));
    CpInfo *ci = cp->infos[index];
    u_int16_t nameIndex = *(u_int16_t *)ci->v1;
    u_int16_t typeIndex = *(u_int16_t *)ci->v2;
    u_int32_t nameLen, typeLen;
    rs->name = getUtf8(cp, nameIndex, &nameLen);
    rs->nameLen = nameLen;
    rs->type = getUtf8(cp, typeIndex, &typeLen);
    rs->typeLen = typeLen;
    return rs;
}

// make this C string? hate '\0'
// use sds? miss some useful function
char *getClassName(Cp *cp, uint16_t index, u_int32_t *len)
{
    return getUtf8(cp, index, len);
}

char *getUtf8(Cp *cp, uint16_t index, u_int32_t *len)
{
    CpInfo *ci = cp->infos[index];
    *len = *(u_int32_t *)ci->v1;
    return (char *)ci->v2;
}
