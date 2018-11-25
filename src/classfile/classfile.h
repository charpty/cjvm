#include <stdlib.h>
#include "constant_pool.h"
#include "member_info.h"
#include "attribute_info.h"
#include "classreader.c"

// 对应java中的public关键字
#define ACC_PUBLIC 0x0001
// 对应java中的final关键字
#define ACC_FINAL 0x0010
// 对应super关键字，用于在invokespecial时调用父类方法
#define ACC_SUPER 0x0020
// 接口与抽象类
#define ACC_INTERFACE 0x0200
#define ACC_ABSTRACT 0x0400
// JVM自用的标记
#define ACC_SYNTHETIC 0x1000
// 注解与枚举
#define ACC_ANNOTATION 0x2000
#define ACC_ENUM 0x4000

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

// 属性命名和oracle虚拟机规范尽量保持一直(规范中属性名都使用下划线，但结构体我习惯用驼峰形式)
// https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-4.html
typedef struct ClassFile
{
    // cafebabe
    uint32_t magic;
    // 编译该class时用的JDK版本号，如52代表JDK8
    uint16_t minor_version;
    uint16_t major_version;
    // 该文件的常量池，有些会成为运行时常量池的一部分
    CP *constant_pool;

    // 类的访问控制，有是否public、是否final、是否抽象等等
    uint16_t access_flags;
    // 指向CONSTANT_Class_info（class权限定名）的地址
    uint16_t this_class;
    // 指向父类CONSTANT_Class_info
    uint16_t super_class;
    // 只可以继承一个父类，但是可以实现多个接口
    uint16_t interfaces_count;
    uint16_t *interfaces;
    // 类中的各种属性，包括静态的和成员的
    uint16_t fields_count;
    MemberInfos *fields;
    // 各个方法的方法签名
    MemberInfos *methods;
    // 属性表，代码的字节码、异常表等大量信息都存在这里，比较复杂
    AttributeInfos *attributes;

    ClassFile *(*readAsClassFile)(ClassReader *r);
} ClassFile;

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