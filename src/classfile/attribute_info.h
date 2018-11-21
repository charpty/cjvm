// https://docs.oracle.com/javase/specs/jvms/se8/html/jvms-4.html#jvms-4.7
#include <stdlib.h>

typedef struct AttributeInfo
{

} AttributeInfo;

typedef struct AttributeInfos
{
    uint32_t size;
    AttributeInfo *infos;

} Attribute;