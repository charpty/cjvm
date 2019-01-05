#ifndef MOON_RCP_H
#define MOON_RCP_H

#include "classfile/constant_pool.h"
#include "runtime/class.h"

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

struct InstanceOOP *resloveStringReference(IKlass *clazz, char *str)
{
    return NULL;
}

struct IMKlass *resloveClassReference(IKlass *clazz, char *str)
{
    return NULL;
}

#endif