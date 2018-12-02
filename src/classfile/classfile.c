#include "classfile/classfile.h"
#include "util/util.h"

void checkMagic(uint32_t magic);
void checkClassVersion(uint16_t major_version, uint16_t minor_version);
struct CPInfo *readConstantInfo(struct ClassReader *r, CP *cp);
struct CP *readConstantPool(struct ClassReader *r);

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

void checkMagic(uint32_t magic)
{
    // check if 'cafebabe', not need in my cjvm
}

void checkClassVersion(uint16_t major_version, uint16_t minor_version)
{
    // check if class version is compatible, no need in my cjvm
}