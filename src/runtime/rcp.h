#ifndef MOON_RCP_H
#define MOON_RCP_H

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
    RCPInfo **info;
} RCP;

struct RCP *buildConstantPool(struct IKlass *clazz);
struct RCPInfo *getRCPInfo(struct RCP *rcp);

#endif