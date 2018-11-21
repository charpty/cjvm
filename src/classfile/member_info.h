#include <stdlib.h>
#include "attribute_info.h"

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
    Attribute attributes;
} MemberInfo;

typedef struct MemberInfos
{
    uint32_t size;
    MemberInfo *infos;
} MemberInfos;