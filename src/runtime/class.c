#include <stdlib.h>
#include "sds.h"

typedef struct GCP
{

} GCP;

typedef struct Fields
{

} Fields;

typedef struct Methods
{

} Methods;

typedef struct Classes
{

} Classes;

typedef struct Class
{
    uint16_t accessFlags;
    char *name;
    char *superClassName;
    char **interfaceNames;
    GCP *constantPool;
    Fields *fields;
    Methods *methods;
    // loader            *ClassLoader
    // superClass        *Class
    // Classes *interfaces;
    uint32_t instanceSlotCount;
    uint32_t staticSlotCount;
} Class;