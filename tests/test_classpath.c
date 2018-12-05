#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>

#include "util/util.h"
#include "classfile/classpath.h"

void assertClassMagic(SClass *sclass)
{
    printf("class name=: %s\n", sclass->name);
    char *bytes = sclass->bytes;
    // cafebabe
    printf("%x\n", bytes[0]);
    printf("%x\n", bytes[1]);
    printf("%x\n", bytes[2]);
    printf("%x\n", bytes[3]);

    uint32_t magic = (uint8_t)bytes[0] << 24 | (uint8_t)bytes[1] << 16 | (uint8_t)bytes[2] << 8 | (uint8_t)bytes[3];
    char magicStr[9];
    sprintf(magicStr, "%X", magic);
    printf("magic=%s\n", magicStr);
    assertEquals("CAFEBABE", magicStr, "scalass=%s magic code is not CAFEBABE: %X", sclass->name, magic);
}

void testReadObjectClass()
{
    ClassPath *classPath = buildClassPath(NULL, "/Users/charpty");
    struct SClass *sclass = readClass(classPath, "java/lang/Object.class");

    if (sclass == NULL)
    {
        LOG_ERROR(__FILE__, __LINE__, "can not find class: %s", "java/lang/Object.class");
        exit(1);
    }
    assertClassMagic(sclass);
}

void testReadMySimpleClass(char *userdir)
{
    char *userpath = malloc(strlen(userdir) + 2);
    memset(userpath, 0, strlen(userdir) + 2);
    strcat(userpath, userdir);
    strcat(userpath, "/");
    ClassPath *classPath = buildClassPath(NULL, userpath);
    struct SClass *sclass = readClass(classPath, "MySimple.class");

    if (sclass == NULL)
    {
        LOG_ERROR(__FILE__, __LINE__, "can not find class: MySimple.class");
        exit(1);
    }
    assertClassMagic(sclass);
}

int main(int argc, char const *argv[])
{
    testReadObjectClass();

    char *cpath = malloc(strlen(argv[0]));
    memcpy(cpath, argv[0], strlen(argv[0]));
    char *cdir = dirname(cpath);
    printf("current dir=%s\n", cdir);
    testReadMySimpleClass(cdir);
    return 0;
}
