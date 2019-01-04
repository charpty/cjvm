#ifndef MOON_RCP_H
#define MOON_RCP_H

#include "classfile/constant_pool.h"

#define RCP_CONSTANT_Class 7
#define RCP_CONSTANT_Fieldref 9
#define RCP_CONSTANT_Methodref 10
#define RCP_CONSTANT_InterfaceMethodref 11
#define RCP_CONSTANT_String 8
#define RCP_CONSTANT_Integer 3
#define RCP_CONSTANT_Float 4
#define RCP_CONSTANT_Long 5
#define RCP_CONSTANT_Double 6
#define RCP_CONSTANT_NameAndType 12
#define RCP_CONSTANT_Utf8 1
#define RCP_CONSTANT_MethodHandle 15
#define RCP_CONSTANT_MethodType 16
#define RCP_CONSTANT_InvokeDynamic 18

// https://docs.oracle.com/javase/specs/jvms/se11/html/jvms-5.html
// 在类加载时进行解析
typedef struct ClassRef
{
    char *classname;
} SymbolRef;

typedef struct MemberRef
{
    char *classname;
    char *name;
    char *descriptor;
} MemberRef;

typedef struct RCPInfo
{
    uint8_t type;
    void *data;
} RCPInfo;

// https://docs.oracle.com/javase/specs/jvms/se11/html/jvms-2.html#jvms-2.5.5
// 必须在运行时才解析的动态符号信息
typedef struct RCP
{
    u_int32_t size;
    RCPInfo **infos;
} RCP;

struct RCP *buildConstantPool(struct CP *cp)
{
    struct RCP *rcp = (RCP *)malloc(sizeof(struct RCP));
    rcp->size = cp->len;
    for (int i = 0, size = rcp->size; i < size; i++)
    {
        rcp->infos[i] = (RCPInfo *)malloc(sizeof(struct RCPInfo));
        rcp->infos[i]->type = cp->infos[i]->tag;
    }
    return rcp;
}

struct RCPInfo *getRCPInfo(struct RCP *rcp, uint32_t index)
{
    return rcp->infos[index];
}

#endif