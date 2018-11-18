#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zip.h>
#include "../../src/util/log.c"
#include "../../src/util/files.c"
#include "../../dep/sds/sds.c"

void printClassHead(char *classStream);

void testReadLibDir(char *libPath, char *classname)
{
    printf("%s:%s\n", libPath, classname);

    int size;

    File **files = listDir(libPath, ".jar", &size, 0);
    printf("size is %d\n", size);
    for (int i = 0; i < size; i++)
    {
        File *f = files[i];
        printf("jar file: %s \n", f->path);
    }
}

void testReadJar(char *jarPath, char *classname)
{
    printf("%s\n", jarPath);
    int err = 0;
    struct zip *z = zip_open(jarPath, 0, &err);
    //Search for the file of given name
    if (err != 0)
    {
        LOG_ERROR("open jar file %s failed, error code is: %d", jarPath, err);
        return;
    }
    const char *name = classname;
    struct zip_stat st;
    zip_stat_init(&st);
    zip_stat(z, name, 0, &st);

    if (st.size <= 0)
    {
        LOG_ERROR("jar file %s has no class which name is %s", jarPath, classname);
        return;
    }

    //Alloc memory for its uncompressed contents
    char *contents = malloc(st.size);

    printf("%lld", st.size);
    //Read the compressed file
    struct zip_file *f = zip_fopen(z, name, 0);
    zip_fread(f, contents, st.size);
    zip_fclose(f);

    //And close the archive
    zip_close(z);

    //Do something with the contents
    printClassHead(contents);
    //delete allocated memory
    free(contents);

    printf("%s\n", jarPath);
}

void testReadClassFile(char *classfile)
{
    printf("%s\n", classfile);
    struct File *f = readFile(classfile);
    printClassHead(f->data);
}

void printClassHead(char *classStream)
{
    char x[5] = {0};
    memcpy(x, classStream, 4);
    // cafebabe
    printf("%x\n", classStream[0]);
    printf("%x\n", classStream[1]);
    printf("%x\n", classStream[2]);
    printf("%x\n", classStream[3]);
}

int main(int argc, char const *argv[])
{
    // testReadJar("/Users/charpty/test.jar", "com/ifugle/EdasConfig.class");
    // testReadClassFile("/Users/charpty/Test.class");

    testReadLibDir(sdscat(sdsnew(getenv("JAVA_HOME")), "/jre/lib"), "cc");
    return 0;
}
