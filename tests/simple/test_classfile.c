#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>

#include "classfile/classfile.h"

void printSimpleClassFile(ClassFile *cf)
{
    CP *cp = cf->constant_pool;
    printf("magic=%X\n", cf->magic);
    printf("major_version=%hu\n", cf->major_version);
    printf("minor_version=%hu\n", cf->minor_version);
    printf("constant_pool->len=%d\n", cf->constant_pool->len);
    printf("cf->this_class index=%d\n", cf->this_class);
    printf("this class=%s\n", getName(cp, cf->this_class));
    printf("cf->interfaces_count=%d\n", cf->interfaces_count);
    printf("cf->fields->size=%d\n", cf->fields->size);
    printf("cf->methods->size=%d\n", cf->methods->size);
}

void assertSimpleClassFile(ClassFile *cf)
{
    CP *cp = cf->constant_pool;
    char *classname = getName(cp, cf->this_class);
    assertEquals("MySimple", getName(cp, cf->this_class), "read MySimple.class, but name is: %s", classname);
}

void testReadSimpleClass(char *userdir)
{
    char *userpath = malloc(strlen(userdir) + 2);
    memset(userpath, 0, strlen(userdir) + 2);
    strcat(userpath, userdir);
    strcat(userpath, "/");
    ClassPath *classPath = buildClassPath(NULL, userpath);
    SClass *sclass = readClass(classPath, "MySimple.class");
    printf("class name= %s\n", sclass->name);
    printf("class len= %d\n", sclass->len);
    char *bytes = sclass->bytes;

    ClassReader *r = buildClassReader(sclass);
    ClassFile *classfile = readAsClassFile(r);

    assertSimpleClassFile(classfile);
    printSimpleClassFile(classfile);
}

int main(int argc, char const *argv[])
{
    char *cpath = malloc(strlen(argv[0]));
    memcpy(cpath, argv[0], strlen(argv[0]));
    char *cdir = dirname(cpath);
    printf("current dir=%s\n", cdir);

    testReadSimpleClass(cdir);
    return 0;
}
