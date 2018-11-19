#include <stdlib.h>

typedef struct ClassReader
{
    int position;
    unsigned char *data;
} ClassReader;

uint8_t readUint8(ClassReader *r);

uint16_t readUint16(ClassReader *r);

uint32_t readUint32(ClassReader *r);

uint64_t readUint64(ClassReader *r);

uint16_t *readUint16s(ClassReader *r, int *size);

char *readBytes(ClassReader *r, u_int32_t n, int *size);