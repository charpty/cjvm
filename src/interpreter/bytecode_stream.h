#include <stdlib.h>

typedef struct ByteCodeStream
{
    char *code;
    int32_t pc;
} ByteCodeStream;

static uint8_t nextUint8(ByteCodeStream *s)
{
    return s->code[s->pc++];
}

static int8_t nextInt8(ByteCodeStream *s)
{
    int8_t x = *((int8_t *)s->code);
    s->pc++;
    return x;
}

static uint16_t nextUint16(ByteCodeStream *s)
{
    return (uint16_t)s->code[s->pc++] << 8 | (uint16_t)s->code[s->pc++];
}

static int16_t nextInt16(ByteCodeStream *s)
{
    return (int16_t)s->code[s->pc++] << 8 | (int16_t)s->code[s->pc++];
}

static int32_t nextInt32(ByteCodeStream *s)
{
    int8_t x1 = s->code[s->pc++];
    int8_t x2 = s->code[s->pc++];
    int8_t x3 = s->code[s->pc++];
    int8_t x4 = s->code[s->pc++];
    return (int32_t)x1 << 24 | (int32_t)x2 << 16 | (int32_t)x3 << 8 | (int32_t)x4;
}

static int32_t *nextInt32s(ByteCodeStream *s, u_int32_t size)
{
    int32_t *rs = (int32_t *)malloc(size * sizeof(int32_t));
    for (int i = 0; i < size; i++)
    {
        rs[i] = nextInt32(s);
    }
    return rs;
}

static void skipPadding(ByteCodeStream *s)
{

    while (s->pc % 4 != 0)
    {
        nextUint8(s);
    }
}