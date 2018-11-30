#ifndef MOON_CLASS_READER_H
#define MOON_CLASS_READER_H

#include <stdlib.h>
#include <stdio.h>

typedef struct ClassReader
{
    // 逐个字节读下去
    uint32_t position;
    uint32_t len;
    unsigned char *data;
} ClassReader;

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

uint16_t *readUint16s(ClassReader *r, u_int16_t *size)
{
    uint16_t *rs = (uint16_t *)malloc((*size = readUint16(r)) * sizeof(u_int16_t));
    for (int i = 0; i < (*size); i++)
    {
        rs[i] = readUint16(r);
    }
    return rs;
}

char *readBytes(ClassReader *r, u_int32_t n, u_int32_t *size)
{
    char *rs = (char *)malloc(n * sizeof(char) + 1);
    memcpy(rs, r->data, n);
    r->position += n;
    *size = n;
    return rs;
}

#endif