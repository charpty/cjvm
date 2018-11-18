#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

#include "files.h"

#include "../../dep/adlist/adlist.c"

File *readFile(char *filepath)
{
    struct File *r = malloc(sizeof(struct File));
    FILE *f = fopen(filepath, "r");
    char *buffer = 0;
    long len;
    if (f)
    {
        fseek(f, 0, SEEK_END);
        len = ftell(f);
        fseek(f, 0, SEEK_SET);
        buffer = malloc(len);
        if (buffer)
        {
            fread(buffer, 1, len, f);
        }
        fclose(f);
    }
    r->data = buffer;
    r->len = len;
    return r;
}

static void _listDir(list *r, char *dirPath, char *suffix, int recursive);

File **listDir(char *dirPath, char *suffix, int *filesize, int recursive)
{
    list *r = listCreate();
    _listDir(r, dirPath, suffix, recursive);
    unsigned long len = r->len;
    *filesize = len;

    File **files = malloc(sizeof(struct File) * len);
    int n = 0;
    listIter *iter = listGetIterator(r, AL_START_HEAD);
    listNode *node;
    while ((node = listNext(iter)) != NULL)
    {
        files[n++] = node->value;
    }
    listReleaseIterator(iter);
    listRelease(r);
    return files;
}

static void _listDir(list *r, char *dirPath, char *suffix, int recursive)
{

    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(dirPath)))
        return;

    while ((entry = readdir(dir)) != NULL)
    {

        if (entry->d_type == DT_DIR)
        {
            char path[1024];
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            if (recursive)
                _listDir(r, entry->d_name, suffix, recursive);
        }
        else
        {
            char *s = strrchr(entry->d_name, '.');
            if (s && strcmp(s, suffix))
                continue;
            File *f = malloc(sizeof(struct File));
            char *dash = "/";
            int len = strlen(dirPath) + strlen(entry->d_name) + 2;
            f->path = malloc(len);
            memset(f->path, 0, len);
            strcat(f->path, dirPath);
            strcat(f->path, dash);
            printf("%s\n", entry->d_name);
            strcat(f->path, entry->d_name);
            
            listAddNodeTail(r, f);
        }
    }
    closedir(dir);
}
