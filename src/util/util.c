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
    printf("%s%s\n", KYEL, buf);
    va_end(list);
}

void LOG_ERROR(char *file, int line, char *format, ...)
{
    char buf[256] = {0};
    va_list list;
    va_start(list, format);
    vsprintf(buf, format, list);
    printf("%s%s:%d >> %s\n", KRED, file, line, buf);
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
        exit(1);
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

XFile **listDir(char *dirPath, char *suffix, int *filesize, int recursive)
{
    XFileList *r = malloc(sizeof(struct XFileList));

    _listDir(r, dirPath, suffix, recursive);
    unsigned long len = r->len;
    *filesize = len;

    XFile **files = malloc(sizeof(struct XFile) * len);
    int n = 0;

    XFileNode *node = r->head;
    for (; node != NULL;)
    {
        files[n++] = node->file;
        XFileNode *x = node;
        node = node->next;
        free(x);
    }
    free(r);
    return files;
}

static void _listDir(XFileList *r, char *dirPath, char *suffix, int recursive)
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
            XFile *f = malloc(sizeof(struct XFile));
            char *dash = "/";
            int len = strlen(dirPath) + strlen(entry->d_name) + 2;
            f->path = malloc(len);
            memset(f->path, 0, len);
            strcat(f->path, dirPath);
            strcat(f->path, dash);
            printf("%s\n", entry->d_name);
            strcat(f->path, entry->d_name);
            XFileNode *n = malloc(sizeof(struct XFileNode));
            r->current->next = n;
            r->len++;
            r->current = n;
        }
    }
    closedir(dir);
}
