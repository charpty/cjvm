#ifndef MOON_CLASS_H
#define MOON_CLASS_H

#include <stdlib.h>
#include "rcp.h"

typedef struct Field
{

} Field;

typedef struct Fields
{

} Fields;

typedef struct Method
{

} Method;

typedef struct Methods
{

} Methods;

typedef struct Classes
{

} Classes;

typedef struct Interfaces
{

} Interfaces;

typedef struct Class
{
    uint16_t accessFlags;
    char *name;
    char *superClassName;
    Interfaces *interfaces;
    RCP *constantPool;
    Fields *fields;
    Methods *methods;
    struct ClassLoader *loader;
    struct Class *superClass;
    uint32_t instanceSlotCount;
    uint32_t staticSlotCount;
} Class;

/* acessflags */
int8_t isPublic(Class *clazz);
int8_t isFinal(Class *clazz);
int8_t isSuper(Class *clazz);
int8_t isInterface(Class *clazz);
int8_t isProtected(Class *clazz);
int8_t isAbstract(Class *clazz);
int8_t isStatic(Class *clazz);
int8_t isSynthetic(Class *clazz);
int8_t isAnnotation(Class *clazz);
int8_t isEnum(Class *clazz);

char *getName();

#endif