#ifndef MOON_CLASS_READER_H
#define MOON_CLASS_READER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "classpath/classpath.h"

typedef struct ClassReader
{
    // 逐个字节读下去
    uint32_t position;
    uint32_t len;
    char *data;
} ClassReader;

static ClassReader *buildClassReader(SClass *scalss)
{
    ClassReader *rs = malloc(sizeof(ClassReader));
    rs->position = 0;
    rs->len = scalss->len;
    rs->data = scalss->bytes;
    return rs;
}

static uint8_t readUint8(ClassReader *r)
{
    return r->data[r->position++];
}

static uint16_t readUint16(ClassReader *r)
{
    return (uint16_t)r->data[r->position++] << 8 | (uint16_t)r->data[r->position++];
}

static uint32_t readUint32(ClassReader *r)
{
    uint32_t x1 = r->data[r->position++];
    uint32_t x2 = r->data[r->position++];
    uint32_t x3 = r->data[r->position++];
    uint32_t x4 = r->data[r->position++];
    // *(uint32_t *)(r->data + r->position);
    return x1 << 24 | x2 << 16 | x3 << 8 | x4;
}

static uint64_t readUint64(ClassReader *r)
{
    uint32_t x1 = r->data[r->position++];
    uint32_t x2 = r->data[r->position++];
    uint32_t x3 = r->data[r->position++];
    uint32_t x4 = r->data[r->position++];
    uint32_t hi = x1 << 24 | x2 << 16 | x3 << 8 | x4;
    x1 = r->data[r->position++];
    x2 = r->data[r->position++];
    x3 = r->data[r->position++];
    x4 = r->data[r->position++];
    uint32_t low = x1 << 24 | x2 << 16 | x3 << 8 | x4;
    // *(uint64_t *)(r->data + r->position);
    return (uint64_t)hi << 32 | (uint64_t)low;
}

static uint16_t *readUint16s(ClassReader *r, u_int16_t *size)
{
    uint16_t *rs = (uint16_t *)malloc((*size = readUint16(r)) * sizeof(u_int16_t));
    for (int i = 0; i < (*size); i++)
    {
        rs[i] = readUint16(r);
    }
    return rs;
}

static char *readBytes(ClassReader *r, u_int32_t n)
{
    char *rs = (char *)malloc(n * sizeof(char) + 1);
    memcpy(rs, r->data, n);
    r->position += n;
    return rs;
}

#endif