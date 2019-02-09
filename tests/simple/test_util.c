#include <string.h>
#include <zip.h>
#include <stdio.h>

#include "../../src/util/util.h"

void testLog()
{
    LOG_DEBUG("path=%s already init %ld time by %s", "/a/b/c", 2l, "jack");
    LOG_INFO("we should get some sleep now, it's %s", "23:00");
    LOG_WARN("you should use right type: %d, but current is %s", 32, "33");
    LOG_ERROR(__FILE__, __LINE__, "module %s has %d %s", "order", 2, "unlink pay order");
}

void testAssertEquals()
{
    char *a = "bb";
    char *b = "bb";
    char *c = "cc";
    assertEquals(a, b, "%s is not equal b", "a");
    // assertEquals(a, c, "%s is not equal c", "a");
}

void testAssertExpress()
{
    assertExpress(0, "current version %d is ok", 52);
    // assertExpress(-1, "unknow tag: %d", 33);
}

void testReadJar()
{
    char *javaHome = getenv("JAVA_HOME");
    char *lib = "/jre/lib/rt.jar";
    int lenlib = strlen(javaHome) + strlen(lib) + 1;
    char *libPath = malloc(lenlib);
    memset(libPath, 0, lenlib);
    strcat(libPath, javaHome);
    strcat(libPath, lib);
    XFile *file = readFile(libPath);
    assertEquals("rt.jar", file->name, "read rt.jar's filename is not rt.jar: %s", file->name);
    assertExpress(file->len, "read rt.jar's size less than zero: %d", file->len);
}

void testListJavaHome()
{
    char *javaHome = getenv("JAVA_HOME");
    printf("JAVA_HOME is:%s\n", javaHome);

    XFiles *files = listDir(javaHome, ".jar", 1);
    printf("size is %d\n", files->len);
    int8_t exist = -1;
    for (int i = 0; i < files->len; i++)
    {
        XFile *f = files->files[i];
        // printf("jar file: %s \n", f->path);
        if (strcmp("rt.jar", f->name))
        {
            exist = 1;
        }
    }
    printf("exist=%d\n", exist);
    assertExpress(exist, "can not find rt.jar in dir: %s", javaHome);
}

void testDoubleFloatConvert()
{
    double a = 1.0;
    doubleToInt64(a);
}

int main(int argc, char const *argv[])
{
    /* log */
    testLog();
    /* assert */
    testAssertEquals();
    /* files */
    testListJavaHome();
    testReadJar();
    return 0;
}
