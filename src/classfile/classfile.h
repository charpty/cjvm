#ifndef MOON_CLASSFILE_H
#define MOON_CLASSFILE_H

#include <stdlib.h>
#include "classfile/attribute_info.h"
#include "classfile/constant_pool.h"
#include "classfile/member_info.h"

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
    struct MemberInfos *fields;
    // 各个方法的方法签名
    struct MemberInfos *methods;
    // 属性表，代码的字节码、异常表等大量信息都存在这里，比较复杂
    struct AttributeInfos *attributes;

    struct ClassFile *(*readAsClassFile)(ClassReader *r);
} ClassFile;

ClassFile *readAsClassFile(ClassReader *r);

#endif