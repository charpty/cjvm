#include "runtime/class.h"

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