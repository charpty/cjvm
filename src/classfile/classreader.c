#include <stdlib.h>
#include <stdio.h>
#include "classreader.h"

uint8_t readUint8(ClassReader *r)
{
    return r->data[r->position++];
}

uint16_t readUint16(ClassReader *r)
{

    return r->data[r->position++] << 8 | r->data[r->position++];
}

uint32_t readUint32(ClassReader *r)
{
    return *(uint32_t *)r;
}

uint64_t readUint64(ClassReader *r)
{
    return *(uint64_t *)r;
}

uint16_t *readUint16s(ClassReader *r, int *size)
{
    uint16_t len = readUint16(r);
    uint16_t *rs = malloc(len * sizeof(u_int16_t));
    for (int i = 0; i < len; i++)
    {
        rs[i] = readUint16(r);
    }
    return rs;
}

char *readBytes(ClassReader *r, u_int32_t n, int *size)
{
    char *rs = (char *)malloc(n * sizeof(char));
    memcpy(rs, r->data[r->position], n);
    r->position += n;
    return rs;
}
