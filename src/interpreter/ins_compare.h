#ifndef MOON_INS_COMPARE_H
#define MOON_INS_COMPARE_H

#include "runtime/class.h"
#include "runtime/thread.h"
#include "runtime/rcp.h"
#include "runtime/oop.h"
#include "interpreter/bytecode_stream.h"
#include "interpreter/bytecode_interpreter.h"

// 比较
// LCMP 148      0x94 比较栈顶两long型数值大小，并将结果（1，0，-1）压入栈顶
// FCMPL 149     0x95 比较栈顶两float型数值大小，并将结果（1，0，-1）压入栈顶；当其中一个数值为“NaN”时，将-1压入栈顶
// FCMPG 150     0x96 比较栈顶两float型数值大小，并将结果（1，0，-1）压入栈顶；当其中一个数值为“NaN”时，将1压入栈顶
// DCMPL 151     0x97 比较栈顶两double型数值大小，并将结果（1，0，-1）压入栈顶；当其中一个数值为“NaN”时，将-1压入栈顶
// DCMPG 152     0x98 比较栈顶两double型数值大小，并将结果（1，0，-1）压入栈顶；当其中一个数值为“NaN”时，将1压入栈顶
// IFEQ 153      0x99 当栈顶int型数值等于0时跳转
// IFNE 154      0x9a 当栈顶int型数值不等于0时跳转
// IFLT 155      0x9b 当栈顶int型数值小于0时跳转
// IFGE 156      0x9c 当栈顶int型数值大于等于0时跳转
// IFGT 157      0x9d 当栈顶int型数值大于0时跳转
// IFLE 158      0x9e 当栈顶int型数值小于等于0时跳转
// IF_ICMPEQ 159 0x9f 比较栈顶两int型数值大小，当结果等于0时跳转
// IF_ICMPNE 160 0xa0 比较栈顶两int型数值大小，当结果不等于0时跳转
// IF_ICMPLT 161 0xa1 比较栈顶两int型数值大小，当结果小于0时跳转
// IF_ICMPGE 162 0xa2 比较栈顶两int型数值大小，当结果大于等于0时跳转
// IF_ICMPGT 163 0xa3 比较栈顶两int型数值大小，当结果大于0时跳转
// IF_ICMPLE 164 0xa4 比较栈顶两int型数值大小，当结果小于等于0时跳转
// IF_ACMPEQ 165 0xa5 比较栈顶两引用型数值，当结果相等时跳转
// IF_ACMPNE 166 0xa6 比较栈顶两引用型数值，当结果不相等时跳转

void insm_148(Frame *frame, ByteCodeStream *stream)
{
    // LCMP
    long v2 = popLong(frame->operandStack);
    long v1 = popLong(frame->operandStack);
    pushInt(frame->operandStack, v1 > v2 ? 1 : (v1 == v2 ? 0 : -1));
    UPDATE_PC_AND_CONTINUE
}

void insm_149(Frame *frame, ByteCodeStream *stream)
{
    // FCMPL
    float v2 = popFloat(frame->operandStack);
    float v1 = popFloat(frame->operandStack);

    // (include NaN) => pushInt(frame->operandStack, v1 > v2 ? 1 : (v1 == v2 ? 0 : (v1 < v2 ? -1 : -1)));
    pushInt(frame->operandStack, v1 > v2 ? 1 : (v1 == v2 ? 0 : -1));
    UPDATE_PC_AND_CONTINUE
}

void insm_151(Frame *frame, ByteCodeStream *stream)
{
    // DCMPL
    double v2 = popFloat(frame->operandStack);
    double v1 = popFloat(frame->operandStack);
    pushInt(frame->operandStack, v1 > v2 ? 1 : (v1 == v2 ? 0 : -1));
    UPDATE_PC_AND_CONTINUE
}

void insm_152(Frame *frame, ByteCodeStream *stream)
{
    // DCMPG
    float v2 = popFloat(frame->operandStack);
    float v1 = popFloat(frame->operandStack);
    pushInt(frame->operandStack, v1 < v2 ? -1 : (v1 == v2 ? 0 : 1));
    UPDATE_PC_AND_CONTINUE
}

void insm_158(Frame *frame, ByteCodeStream *stream)
{
    // IFLE
    int32_t v = popInt(frame->operandStack);
    int32_t offset = (int32_t)nextInt16(stream);
    if (v <= 0)
    {
        frame->nextPC = frame->thread->pc + offset;
    }
}

void insm_159(Frame *frame, ByteCodeStream *stream)
{
    // IF_ICMPEQ
    int32_t v2 = popInt(frame->operandStack);
    int32_t v1 = popInt(frame->operandStack);
    int32_t offset = (int32_t)nextInt16(stream);
    if (v1 == v2)
    {
        frame->nextPC = frame->thread->pc + offset;
    }
}

void insm_166(Frame *frame, ByteCodeStream *stream)
{
    // IF_ACMPNE
    void *r2 = popRef(frame->operandStack);
    void *r1 = popRef(frame->operandStack);
    int32_t offset = (int32_t)nextInt16(stream);
    if (r1 != r2)
    {
        frame->nextPC = frame->thread->pc + offset;
    }
}

#endif
