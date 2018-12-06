#ifndef MOON_CLASSLOADER_H
#define MOON_CLASSLOADER_H

#include "classpath.h"

typedef struct ClassLoader
{
    ClassPath *classpath;
    // loaded class map
} ClassLoader;

#endif