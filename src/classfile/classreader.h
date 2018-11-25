#ifndef MOON_CLASS_READER_H
#define MOON_CLASS_READER_H

#include <stdlib.h>

typedef struct ClassReader
{
    // 逐个字节读下去
    uint32_t position;
    uint32_t len;
    unsigned char *data;
} ClassReader;

uint8_t readUint8(ClassReader *r);

uint16_t readUint16(ClassReader *r);

uint32_t readUint32(ClassReader *r);

uint64_t readUint64(ClassReader *r);

uint16_t *readUint16s(ClassReader *r, u_int32_t *size);

char *readBytes(ClassReader *r, u_int32_t n, u_int32_t *size);

#endif