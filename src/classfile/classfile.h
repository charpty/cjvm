#include <stdlib.h>
#include "constant_pool.h"
#include "member_info.h"
#include "attribute_info.h"

typedef struct attribute_info
{
    uint16_t attribute_name_index;
    uint32_t attribute_length;
    uint8_t *info;
} attribute_info;

typedef struct field_info
{
    uint16_t access_flags;
    uint16_t name_index;
    uint16_t descriptor_index;
    uint16_t attributes_count;
    attribute_info *attributes;
} field_info;

typedef struct method_info
{
    uint16_t access_flags;
    uint16_t name_index;
    uint16_t descriptor_index;
    uint16_t attributes_count;
    attribute_info *attributes;
} method_info;

typedef struct ClassFile
{
    uint32_t magic;
    uint16_t minor_version;
    uint16_t major_version;
    Cp *constant_pool;

    uint16_t access_flags;
    uint16_t this_class;
    uint16_t super_class;
    uint16_t interfaces_count;
    uint16_t *interfaces;
    uint16_t fields_count;

    MemberInfos *fields;
    MemberInfos *methods;
    AttributeInfos* attributes;
} ClassFile;
