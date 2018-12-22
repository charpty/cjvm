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
        exit(1);
    }
}

void assertExpress(int express, char *format, ...)
{
    if (express <= 0)
    {
        char buf[256] = {0};
        va_list list;
        va_start(list, format);
        vsprintf(buf, format, list);
        va_end(list);
        LOG_ERROR(__FILE__, __LINE__, "express is %d", express);
        exit(express);
    }
}

static char *_next(const char *str, char *value)
{
    /*
     * Unicode符号范围     |        UTF-8编码方式
     * (十六进制)        |              （二进制）
     * ----------------------+---------------------------------------------
     * 0000 0000-0000 007F | 0xxxxxxx
     * 0000 0080-0000 07FF | 110xxxxx 10xxxxxx
     * 0000 0800-0000 FFFF | 1110xxxx 10xxxxxx 10xxxxxx
     * 0001 0000-0010 FFFF | 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
     * 
     * 严 -> U+4e25  -> e4 b8 a5
     */
    return NULL;
}

char *utf8ToUnicode(char *utf8Str, uint32_t len)
{
    return NULL;
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
    char *s = strrchr(filepath, '/');

    uint32_t nameLen = strlen(s) - 1;
    r->name = malloc(nameLen + 1);
    r->name[nameLen] = '\0';
    memcpy(r->name, s + 1, nameLen);
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

XFiles *listDir(char *dir, char *suffix, int recursive)
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
    uint32_t len = r->len;
    XFiles *rs = malloc(sizeof(struct XFiles));
    XFile **files = malloc(sizeof(struct XFile) * len);
    int n = 0;

    XFileNode *prev;
    XFileNode *node = r->head;
    for (int n = 0; n < len; n++)
    {
        prev = node;
        node = node->next;
        files[n] = node->file;
        free(prev);
    }
    free(node);
    free(r);
    rs->files = files;
    rs->len = len;
    return rs;
}

static void _listDir(XFileList *r, char *dir, char *suffix, int recursive)
{

    DIR *opened_dir;
    struct dirent *entry;
    if (!(opened_dir = opendir(dir)))
        return;

    while ((entry = readdir(opened_dir)) != NULL)
    {
        char *d_name = entry->d_name;
        if (entry->d_type == DT_DIR)
        {
            if (strcmp(d_name, ".") == 0 || strcmp(d_name, "..") == 0)
                continue;
            if (recursive)
            {
                char path[512];
                sprintf(path, "%s/%s", dir, d_name);
                _listDir(r, path, suffix, recursive);
            }
        }
        else
        {
            char *s = strrchr(d_name, '.');
            if (s == NULL || strcmp(s, suffix) != 0)
                continue;
            XFile *f = malloc(sizeof(struct XFile));
            uint32_t dlen = strlen(d_name) + 1;
            uint32_t len = strlen(dir) + strlen(d_name) + 2;
            f->path = malloc(len);
            f->name = malloc(dlen);
            memset(f->path, 0, len);
            memset(f->name, 0, dlen);
            strcat(f->path, dir);
            strcat(f->path, "/");
            strcat(f->path, d_name);
            strcat(f->name, d_name);

            XFileNode *n = malloc(sizeof(struct XFileNode));
            n->file = f;
            r->current->next = n;
            r->len++;
            r->current = n;
        }
    }
    closedir(opened_dir);
}

union idouble {
    double d;
    int64_t i;
};

union ifloat {
    float f;
    int32_t i;
};

int64_t doubleToInt64(double s)
{
    // TODO
    union idouble r = {.d = s};
    return r.i;
}

int32_t floatToInt32(float s)
{
    // TODO
    union ifloat r = {.f = s};
    return r.i;
}
