#include <stdio.h>
#include <stdlib.h>
#include "files.h"

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