//
// Created by charpty on 2018/11/15.
//

/*
 * 将指定class文件加载到内存中
 * 
 * 启动类路径
 * 扩展类路径
 * 用户类路径 
 */

#include <stdio.h>;
#include <stdlib.h>;
#include "log.c";
#include "files.c";
#include <zip.h>

typedef struct ClassPath
{
    char *bootStrapPath;
    char *extPath;
    char *userPath;
    char *(*readClass)(ClassPath *classPath, char *classname);
} ClassPath;

typedef struct SClass
{
    char *bytes;
    char *name;
} SClass;

char *getJreDir(char *jrePath);

ClassPath *buildClassPath(char *jrePath, char *cpPath)
{
    struct ClassPath *r;
    r = malloc(sizeof(*r));
    if (r == NULL)
    {
        return NULL;
    }
    if (jrePath == NULL || strlen(jrePath) == 0)
    {
        jrePath = getenv("JAVA_HOME");
    }
    char *lib = "/jre/lib";
    char *ext = "/jre/lib/ext";
    int lenlib = strlen(jrePath) + strlen(lib) + 1;
    int lenext = strlen(jrePath) + strlen(ext) + 1;
    char *libPath = malloc(lenlib);
    char *extPath = malloc(lenext);
    memset(libPath, 0, lenlib);
    memset(extPath, 0, lenext);
    strcat(libPath, jrePath);
    strcat(libPath, lib);
    strcat(extPath, jrePath);
    strcat(extPath, ext);

    r->readClass = readClass;
    r->bootStrapPath = libPath;
    r->extPath = extPath;
    return r;
}

SClass *readClass(ClassPath *classPath, char *classname)
{
    SClass *r;
    if ((r = readBootStrap(classPath, classname) != NULL))
        return r;
    if ((r = readBootStrap(classPath, classname) != NULL))
        return r;
    return readUser(classPath, classname);
}

SClass *readBootStrap(ClassPath *classPath, char *classname)
{
    return readClassInJarDir(classPath->bootStrapPath, classname);
}

SClass *readExt(ClassPath *classPath, char *classname)
{
    // always return NULL right now...
    return NULL;
}

SClass *readUser(ClassPath *classPath, char *classname)
{
    return readClassInDir(classPath->userPath, classname);
}

char *getJreDir(char *jrePath)
{
}

SClass *readClassInJar(char *jarPath, char *classname)
{
    int err;
    struct zip *z = zip_open(jarPath, 0, &err);
    if (err != 0)
    {
        LOG_ERROR("open jar file %s failed, error code is: %d", jarPath, err);
        return NULL;
    }
    const char *name = classname;
    struct zip_stat st;
    zip_stat_init(&st);
    zip_stat(z, name, 0, &st);

    if (st.size <= 0)
        return NULL;
    char *contents = malloc(st.size);
    struct zip_file *f = zip_fopen(z, name, 0);
    zip_fread(f, contents, st.size);
    zip_fclose(f);
    zip_close(z);

    SClass *r = (SClass *)malloc(sizeof(struct SClass));
    r->bytes = contents;
    r->name = classname;
    return r;
}

static char *classname2Path(char *classname)
{
    return "";
}

static char *path2classname(char *path)
{
    return "";
}

static SClass *readClassInDir(char *dir, char *classname)
{
    SClass *r = NULL;
    int size;
    File **files = listDir(dir, ".class", &size, 1);
    char *cpath = classname2Path(classname);
    for (int i = 0; i < size; i++)
    {
        File *f = files[i];
        char *path = f->path;
        if (!strcmp(path, cpath))
        {
            File *f = readFile(path);
            r = malloc(sizeof(struct SClass));
            r->bytes = f->data;
            return r;
        }
    }
    return r;
}

static SClass *readClassInJarDir(char *dir, char *classname)
{
    SClass *r = NULL;
    int size;
    File **files = listDir(dir, ".jar", &size, 0);

    for (int i = 0; i < size; i++)
    {
        File *f = files[i];
        r = readClassInJar(f->path, classname);
        if (r != NULL)
        {
            return r;
        }
    }
    return r;
}
