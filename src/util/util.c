#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

#include "util.h"

void LOG_DEBUG(char *format, ...)
{
    char buf[256] = {0};
    va_list list;
    va_start(list, format);
    vsprintf(buf, format, list);
    printf(">> %s\n", buf);
    va_end(list);
}

void LOG_INFO(char *format, ...)
{
    char buf[256] = {0};
    va_list list;
    va_start(list, format);
    vsprintf(buf, format, list);
    printf("%s\n", buf);
    va_end(list);
}

void LOG_WARN(char *format, ...)
{
    char buf[256] = {0};
    va_list list;
    va_start(list, format);
    vsprintf(buf, format, list);
    printf("%s%s%s\n", KYEL, buf, KWHT);
    va_end(list);
}

void LOG_ERROR(char *file, int line, char *format, ...)
{
    char buf[256] = {0};
    va_list list;
    va_start(list, format);
    vsprintf(buf, format, list);
    printf("%s%s:%d >> %s%s\n", KRED, file, line, buf, KWHT);
    va_end(list);
}

void assertEquals(char *s, char *d, char *format, ...)
{
    if (strcmp(s, d) != 0)
    {
        char buf[256] = {0};
        va_list list;
        va_start(list, format);
        vsprintf(buf, format, list);
        va_end(list);
        LOG_ERROR(__FILE__, __LINE__, "%s, s is %s, d is %s", buf, s, d);
#ifndef MOON_TEST
        exit(1);
#endif
    }
}

XFile *readFile(char *filepath)
{
    struct XFile *r = malloc(sizeof(struct XFile));
    FILE *f = fopen(filepath, "r");
    char *buffer = 0;
    uint32_t len;
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

typedef struct XFileNode
{
    XFile *file;
    struct XFileNode *next;
} XFileNode;

typedef struct XFileList
{
    uint32_t len;
    XFileNode *head;
    XFileNode *current;
} XFileList;

static void _listDir(XFileList *r, char *dirPath, char *suffix, int recursive);

XFile **listDir(char *dir, char *suffix, int recursive, int *filesize)
{

    unsigned long slen = strlen(dir);
    char *cdir = dir;
    if (dir[slen - 1] == '/')
    {
        cdir = malloc(slen);
        memset(cdir, 0, slen);
        memcpy(cdir, dir, slen - 1);
    }
    struct XFileList *r = malloc(sizeof(struct XFileList));
    struct XFileNode *head = malloc(sizeof(struct XFileNode));

    r->head = head;
    r->current = head;
    r->len = 0;

    _listDir(r, cdir, suffix, recursive);
    unsigned long len = r->len;
    *filesize = len;

    XFile **files = malloc(sizeof(struct XFile) * len);
    int n = 0;

    XFileNode *prev;
    XFileNode *node = r->head;
    for (int n = 0; n < len; n++)
    {
        fflush(stdout);
        prev = node;
        node = node->next;
        files[n] = node->file;
        free(prev);
    }
    free(node);
    free(r);
    return files;
}

static void _listDir(XFileList *r, char *dir, char *suffix, int recursive)
{

    DIR *opened_dir;
    struct dirent *entry;
    if (!(opened_dir = opendir(dir)))
        return;

    while ((entry = readdir(opened_dir)) != NULL)
    {
        if (entry->d_type == DT_DIR)
        {
            char path[1024];
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            if (recursive)
            {
                _listDir(r, entry->d_name, suffix, recursive);
            }
        }
        else
        {
            char *s = strrchr(entry->d_name, '.');
            if (s == NULL || strcmp(s, suffix) != 0)
                continue;
            XFile *f = malloc(sizeof(struct XFile));
            int len = strlen(dir) + strlen(entry->d_name) + 2;
            f->path = malloc(len);
            memset(f->path, 0, len);
            strcat(f->path, dir);
            strcat(f->path, "/");
            strcat(f->path, entry->d_name);

            XFileNode *n = malloc(sizeof(struct XFileNode));
            n->file = f;
            r->current->next = n;
            r->len++;
            r->current = n;
        }
    }
    closedir(opened_dir);
}