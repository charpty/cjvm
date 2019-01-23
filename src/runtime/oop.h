#ifndef MOON_OOP_H
#define MOON_OOP_H

#include "runtime/class.h"

typedef struct OOP
{

} OOP;

typedef struct InstanceOOP
{

} InstanceOOP;

typedef struct ArrayOOP
{
    uint32_t length;
} ArrayOOP;

Slots getInstanceVars(InstanceOOP *object);

struct InstanceOOP *resolveStringReference(struct IKlass *clazz, char *str);


#endif