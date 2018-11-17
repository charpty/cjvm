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

typedef struct ClassPath
{
    char *bootStrapPath;
    char *extPath;
    char *userPath;
    char *(*readClass)(char *classname);
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
    r->readClass = readClass;
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
    char *javaHome = getenv("JAVA_HOME");
    if (NULL == (FD = opendir(in_dir)))
    {
        fprintf(stderr, "Error : Failed to open input directory - %s\n", strerror(errno));
        fclose(common_file);

        return 1;
    }
    while ((in_file = readdir(FD)))
    {
        if (!strcmp(in_file->d_name, "."))
            continue;
        if (!strcmp(in_file->d_name, ".."))
            continue;
        if (strcmp(in_file->d_name, classname))
        {
            continue;
        }
        entry_file = fopen(in_file->d_name, "r");
        if (entry_file == NULL)
        {
            fprintf(stderr, "Error : Failed to open  file - %s\n", strerror(errno));
            fclose(common_file);

            return 1;
        }

        while (fgets(buffer, BUFSIZ, entry_file) != NULL)
        {
            /* Use fprintf or fwrite to write some stuff into common_file*/
        }

        /* When you finish with the file, close it */
        fclose(entry_file);
    }
}

SClass *readExt(ClassPath *classPath, char *classname)
{
    // always return NULL right now...
    return NULL;
}

SClass *readUser(ClassPath *classPath, char *classname)
{
}

char *getJreDir(char *jrePath)
{
}

int main(int argc, char const *argv[])
{
    return 0;
}
