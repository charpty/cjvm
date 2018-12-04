#ifndef MOON_MEMBER_INFO_H
#define MOON_MEMBER_INFO_H

#include <stdlib.h>
#include "classfile/attribute_info.h"
#include "classfile/constant_pool.h"

typedef struct MemberInfo
{
    // 访问控制符，是否静态，是否公开等
    uint16_t accessFlags;
    // 方法名|字段名在常量池中索引
    uint16_t nameIndex;
    // 描述符字符串
    // https://docs.oracle.com/javase/specs/jvms/se8/html/jvms-4.html#jvms-4.3.2
    uint16_t descriptorIndex;
    // 属性表，方法代码存在属性表中
    AttributeInfos *attributes;
} MemberInfo;

typedef struct MemberInfos
{
    uint32_t size;
    MemberInfo **infos;
} MemberInfos;

static MemberInfos *readMembers(struct ClassReader *r, struct CP *cp)
{
    uint16_t memberCount = readUint16(r);
    MemberInfos *rs = malloc(sizeof(MemberInfos));
    MemberInfo **infos = malloc(sizeof(MemberInfo*) * memberCount);
    rs->size = memberCount;
    for (int i = 0; i < memberCount; i++)
    {
        infos[i] = malloc(sizeof(MemberInfo));
        infos[i]->accessFlags = readUint16(r);
        infos[i]->nameIndex = readUint16(r);
        infos[i]->descriptorIndex = readUint16(r);
        infos[i]->attributes = readAttributes(r, cp);
    }
    rs->infos = infos;
    return rs;
}

#endif