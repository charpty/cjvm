#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zip.h>
#include "util/util.h"
#include "classfile/classpath.h"

static char *path2classname(char *path);
static char *path2classname(char *path);
SClass *readUser(ClassPath *classPath, char *classname);
SClass *readExt(ClassPath *classPath, char *classname);
SClass *readBootStrap(ClassPath *classPath, char *classname);
SClass *readClass(ClassPath *classPath, char *classname);
static SClass *readClassInDir(char *dir, char *classname);
static SClass *readClassInJarDir(char *dir, char *classname);

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
    char *lib = "/jre/lib/";
    char *ext = "/jre/lib/ext/";
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

    char *userPath = cpPath;
    uint32_t lenuser = strlen(userPath);
    if (userPath[lenuser - 1] != '/')
    {
        userPath = malloc(lenuser + 2);
        memset(userPath, 0, lenuser + 2);
        memcpy(userPath, cpPath, lenuser);
        strcat(userPath, "/");
    }
    r->userPath = userPath;
    return r;
}

SClass *readClass(ClassPath *classPath, char *classname)
{
    SClass *r;
    if ((r = readBootStrap(classPath, classname)) != NULL)
        return r;
    else if ((r = readExt(classPath, classname)) != NULL)
        return r;
    else
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
    SClass *r = readClassInDir(classPath->userPath, classname);
    if (r == NULL)
    {
        r = readClassInJarDir(classPath->userPath, classname);
    }
    return r;
}

SClass *readClassInJar(char *jarPath, char *classname)
{
    int err;
    struct zip *z = zip_open(jarPath, 0, &err);
    // TODO I can't find err code >39 means in zip.h
    if (err != 0 && err < 39)
    {
        LOG_ERROR(__FILE__, __LINE__, "open jar file %s failed, error code is: %d", jarPath, err);
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

    struct SClass *r = (SClass *)malloc(sizeof(struct SClass));
    r->len = st.size;
    r->bytes = contents;
    r->name = classname;
    return r;
}

static char *classname2Path(char *classname)
{
    int len = strlen(classname);
    char *r = malloc(len + 1);
    memset(r, 0, len + 1);
    while (len--)
    {
        char *x = classname + len;
        if (classname[len] == '.' && strlen(x) != 5 && strcmp(x, ".class") != 0)
            r[len] = '/';
        else
            r[len] = classname[len];
    }
    return r;
}

static SClass *readClassInDir(char *dirPath, char *classname)
{
    SClass *r = NULL;
    int dlen = strlen(dirPath);
    XFiles *files = listDir(dirPath, ".class", 1);
    char *cpath = classname2Path(classname);
    for (int i = 0, size = files->len; i < size; i++)
    {
        XFile *f = files->files[i];
        char *path = f->path;
        char *xpath = path + dlen;
        if (strcmp(xpath, cpath) == 0)
        {
            XFile *f = readFile(path);
            r = malloc(sizeof(struct SClass));
            r->bytes = f->data;
            r->len = f->len;
            r->name = malloc(strlen(classname) + 1);
            memset(r->name, 0, strlen(classname) + 1);
            memcpy(r->name, classname, strlen(classname));
            return r;
        }
    }
    return r;
}

static SClass *readClassInJarDir(char *dir, char *classname)
{
    SClass *r = NULL;
    XFiles *files = listDir(dir, ".jar", 1);
    for (int i = 0, size = files->len; i < size; i++)
    {
        XFile *f = files->files[i];
        r = readClassInJar(f->path, classname);
        if (r != NULL)
        {
            return r;
        }
    }
    return r;
}
