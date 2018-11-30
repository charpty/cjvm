#include "classfile.h"

void checkMagic(uint32_t magic)
{
    // check if 'cafebabe', not need in my cjvm
}

void checkClassVersion(uint16_t major_version, uint16_t minor_version)
{
    // check if class version is compatible, no need in my cjvm
}

ClassFile *readAsClassFile(ClassReader *r)
{
    ClassFile *rs = (ClassFile *)malloc(sizeof(struct ClassFile));
    // 读取版本信息
    rs->magic = readUint32(r);
    checkMagic(rs->magic);
    rs->minor_version = readUint16(r);
    rs->major_version = readUint16(r);
    checkClassVersion(rs->major_version, rs->minor_version);
    // 读取常量池，动长
    struct CP *csp = readConstantPool(r);
    rs->constant_pool = csp;
    // 访问标志，是一个位图标记，记录了类的访问级别，类是否为final，是否是注解类型等等
    rs->access_flags = readUint16(r);
    // 当前类名在常量池中的索引
    rs->this_class = readUint16(r);
    // 当前类父类名在常量池中的索引
    rs->super_class = readUint16(r);
    // 读取该类实现的所有的接口
    rs->interfaces = readUint16s(r, &(rs->interfaces_count));
    // 读取当前类的属性，包括静态属性
    rs->fields = readMembers(r, csp);
    // 读取当前类的方法信息，包括静态方法
    rs->methods = readMembers(r, csp);
    // 读取剩余的不包含在方法或者字段里的其它属性表信息
    rs->attributes = readAttributes(r, csp);
    return rs;
}

CPInfo *readConstantInfo(ClassReader *r, CP *cp)
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

CP *readConstantPool(ClassReader *r)
{
    CP *rs = (CP *)malloc(sizeof(struct CP));
    int cpCount = readUint16(r);
    rs->infos = (CPInfo **)malloc(cpCount * sizeof(CPInfo *));

    for (int i = 0; i < cpCount; i++)
    {
        rs->infos[i] = readConstantInfo(r, rs);
        // http://docs.oracle.com/javase/specs/jvms/se8/html/jvms-4.html#jvms-4.4.5
        // 这就是个数的特殊情况，读到long和double时，必须下一个元素是个空，以兼容老版本
        // 这是由于一个byte占常量池2个位置
        if (rs->infos[i]->tag == CONSTANT_Long || (rs->infos[i]->tag = CONSTANT_Double))
        {
            ++i;
            continue;
        }
    }
    return rs;
}

NameAndType *getNameAndType(CP *cp, uint16_t index, char **type)
{
    struct NameAndType *rs = (NameAndType *)malloc(sizeof(struct NameAndType));
    CPInfo *ci = cp->infos[index];
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
char *getClassName(CP *cp, uint16_t index, u_int32_t *len)
{
    return getUtf8(cp, index, len);
}

char *getUtf8(CP *cp, uint16_t index, u_int32_t *len)
{
    CPInfo *ci = cp->infos[index];
    *len = *(u_int32_t *)ci->v1;
    return (char *)ci->v2;
}