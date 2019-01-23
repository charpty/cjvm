#ifndef MOON_CLASS_H
#define MOON_CLASS_H

#include <stdlib.h>
#include "rcp.h"

typedef union Slot {
    int32_t num;
    void *ref;
} Slot;

typedef union Slots {
    uint32_t num;
    Slot **vars;
} Slots;

typedef struct Field {
    struct IKlass *clazz;
    uint16_t accessFlags;
    char *name;
    char *descriptor;
    // 属性的初始化值（程序员赋的值）
    uint32_t rcpInfoIndex;
    // 属性值存储的位置，后续要设置属性的值就放到该位置即可
    uint32_t slotIndex;
} Field;

typedef struct Fields {
    uint32_t size;
    struct Field **fields;
} Fields;

typedef struct Method {
    struct IKlass *clazz;
    uint16_t accessFlags;
    char *name;
    char *descriptor;
    // 我们实现时就不对参数个数和栈深校验了
    uint32_t maxLocals;
    uint32_t maxStack;
    uint32_t argCount;
    char *code;
} Method;

typedef struct Methods {
    uint32_t size;
    struct Method **methods;
} Methods;

typedef struct Interfaces {
    uint32_t size;
    void *clazzArray;
} Interfaces;

typedef struct IKlass {
    uint16_t accessFlags;
    char *name;
    char *superClassName;
    Interfaces *interfaces;
    struct RCP *constantPool;
    Fields *fields;
    Methods *methods;
    struct ClassLoader *loader;
    struct IKlass *superClass;
    uint32_t instanceSlotCount;
    uint32_t staticSlotCount;
} IKlass;

// instanceMirroClass => java.lang.Class
typedef struct IMKlass {
    struct IKlass *clazz;
} IMKlass;

/* acessflags */
int8_t isClassPublic(IKlass *clazz);

int8_t isClassFinal(IKlass *clazz);

int8_t isClassSuper(IKlass *clazz);

int8_t isClassInterface(IKlass *clazz);

int8_t isClassProtected(IKlass *clazz);

int8_t isClassAbstract(IKlass *clazz);

int8_t isClassStatic(IKlass *clazz);

int8_t isClassSynthetic(IKlass *clazz);

int8_t isClassAnnotation(IKlass *clazz);

int8_t isClassEnum(IKlass *clazz);

int8_t isClassInit(IKlass *clazz);

int8_t isMethodFinal(Method *method);

int8_t isMethodProtected(Method *method);

int8_t isMethodAbstract(Method *method);

int8_t isMethodStatic(Method *method);

void initClass(IKlass *clazz);

char *getClassName(IKlass *clazz);

char *getClassField(IKlass *clazz, char *name, char *descriptor, uint8_t isStatic);

char *getClassMethod(IKlass *clazz, char *name, char *descriptor, uint8_t isStatic);

IMKlass *getInstanceMirrorClass(IKlass *clazz);

struct InstanceOOP *newObject(IKlass *clazz);

Slots *getStaticVars(IKlass *clazz);

void setSlotRef(Slots *slots, uint32_t index, void *ref);

void *getSlotRef(Slots *slots, uint32_t index);

void setSlotInt(Slots *slots, uint32_t index, int32_t value);

int32_t getSlotInt(Slots *slots, uint32_t index);

void setSlotLong(Slots *slots, uint32_t index, int64_t value);

int64_t getSlotLong(Slots *slots, uint32_t index);

void setSlotFloat(Slots *slots, uint32_t index, float value);

float getSlotFloat(Slots *slots, uint32_t index);

void setSlotDouble(Slots *slots, uint32_t index, double value);

double getSlotDouble(Slots *slots, uint32_t index);

Method *lookupMethodInClass(IKlass *clazz, Method *method);

struct IKlass *resolveClassReference(struct IKlass *clazz, char *str);

struct Field *resolveFieldReference(struct MemberRef *ref);

struct Method *resolveMethodReference(struct MemberRef *ref);

#endif