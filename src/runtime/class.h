#ifndef MOON_CLASS_H
#define MOON_CLASS_H

#include <stdlib.h>
#include "rcp.h"

typedef struct Field
{
    uint16_t accessFlags;
    char *name;
    char *descriptor;
    // 属性的初始化值（程序员赋的值）
    uint32_t rcpInfoIndex;
    // 属性值存储的位置，后续要设置属性的值就放到该位置即可
    uint32_t slotIndex;
} Field;

typedef struct Fields
{
    uint32_t size;
    struct Field **fields;
} Fields;

typedef struct Method
{
    uint16_t accessFlags;
    char *name;
    char *descriptor;
    // 我们实现时就不对参数个数和栈深校验了
    uint32_t maxLocals;
    uint32_t maxStack;
    uint32_t argCount;
    char *code;
} Method;

typedef struct Methods
{
    uint32_t size;
    struct Method **methods;
} Methods;

typedef struct Interfaces
{
    uint32_t size;
    struct IKlass classes;
} Interfaces;

typedef struct IKlass
{
    uint16_t accessFlags;
    char *name;
    char *superClassName;
    Interfaces *interfaces;
    RCP *constantPool;
    Fields *fields;
    Methods *methods;
    struct ClassLoader *loader;
    struct IKlass *superClass;
    uint32_t instanceSlotCount;
    uint32_t staticSlotCount;
} IKlass;

/* acessflags */
int8_t isPublic(IKlass *clazz);
int8_t isFinal(IKlass *clazz);
int8_t isSuper(IKlass *clazz);
int8_t isInterface(IKlass *clazz);
int8_t isProtected(IKlass *clazz);
int8_t isAbstract(IKlass *clazz);
int8_t isStatic(IKlass *clazz);
int8_t isSynthetic(IKlass *clazz);
int8_t isAnnotation(IKlass *clazz);
int8_t isEnum(IKlass *clazz);

char *getName(IKlass *clazz);
char *getField(IKlass *clazz, char *name, char *descriptor, uint8_t isStatic);
char *getMethod(IKlass *clazz, char *name, char *descriptor, uint8_t isStatic);

#endif