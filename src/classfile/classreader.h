#define u1 unsigned char
#define u2 unsigned short
#define u4 unsigned int

typedef struct cp_info
{
    u1 tag;
    u1 *info;
} cp_info;

typedef struct attribute_info
{
    u2 attribute_name_index;
    u4 attribute_length;
    u1 *info;
} attribute_info;

typedef struct field_info
{
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    attribute_info *attributes;
} field_info;

typedef struct method_info
{
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    attribute_info *attributes;
} method_info;

typedef struct ClassFile
{
    u4 magic;
    u2 minor_version;
    u2 major_version;
    u2 constant_pool_count;
    cp_info *constant_pool;
    u2 access_flags;
    u2 this_class;
    u2 super_class;
    u2 interfaces_count;
    u2 *interfaces;
    u2 fields_count;
    field_info *fields;
    u2 methods_count;
    method_info *methods;
    u2 attributes_count;
    attribute_info *attributes;
} ClassFile;