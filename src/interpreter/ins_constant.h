#ifndef MOON_INS_CONSTANT_H
#define MOON_INS_CONSTANT_H

#include "runtime/class.h"
#include "runtime/thread.h"
#include "runtime/rcp.h"
#include "runtime/oop.h"
#include "interpreter/bytecode_stream.h"
#include "interpreter/bytecode_interpreter.h"

// 常量
// NOP 0         0x00 什么都不做
// ACONST_NULL 1 0x01 将null推送至栈顶
// ICONST_M1 2   0x02 将int型-1推送至栈顶
// ICONST_0 3    0x03 将int型0推送至栈顶
// ICONST_1 4    0x04 将int型1推送至栈顶
// ICONST_2 5    0x05 将int型2推送至栈顶
// ICONST_3 6    0x06 将int型3推送至栈顶
// ICONST_4 7    0x07 将int型4推送至栈顶
// ICONST_5 8    0x08 将int型5推送至栈顶
// LCONST_0 9    0x09 将long型0推送至栈顶
// LCONST_1 10   0x0a 将long型1推送至栈顶
// FCONST_0 11   0x0b 将float型0推送至栈顶
// FCONST_1 12   0x0c 将float型1推送至栈顶
// FCONST_2 13   0x0d 将float型2推送至栈顶
// DCONST_0 14   0x0e 将double型0推送至栈顶
// DCONST_1 15   0x0f 将double型1推送至栈顶
// BIPUSH 16     0x10 将单字节的常量值（-128~127）推送至栈顶
// SIPUSH 17     0x11 将一个短整型常量值（-32768~32767）推送至栈顶
// LDC 18        0x12 将int，float或String型常量值从常量池中推送至栈顶
// LDC_W 19      0x13 将int，float或String型常量值从常量池中推送至栈顶（宽索引）
// LDC2_W 20     0x14 将long或double型常量值从常量池中推送至栈顶（宽索引）

void insm_0(Frame *frame, ByteCodeStream *stream)
{
    // NOP
    UPDATE_PC_AND_CONTINUE
}

void insm_1(Frame *frame, ByteCodeStream *stream)
{
    // ACONST_NULL
    pushRef(frame->operandStack, NULL);
    UPDATE_PC_AND_CONTINUE
}

void insm_2(Frame *frame, ByteCodeStream *stream)
{
    // ICONST_M1
    pushInt(frame->operandStack, -1);
    UPDATE_PC_AND_CONTINUE
}

void insm_3(Frame *frame, ByteCodeStream *stream)
{
    // ICONST_0
    pushInt(frame->operandStack, 0);
    UPDATE_PC_AND_CONTINUE
}

void insm_4(Frame *frame, ByteCodeStream *stream)
{
    // ICONST1
    pushInt(frame->operandStack, 1);
    UPDATE_PC_AND_CONTINUE
}

void insm_5(Frame *frame, ByteCodeStream *stream)
{
    // ICONST_2
    pushInt(frame->operandStack, 2);
    UPDATE_PC_AND_CONTINUE
}
void insm_6(Frame *frame, ByteCodeStream *stream)
{
    // ICONST_3
    pushInt(frame->operandStack, 3);
    UPDATE_PC_AND_CONTINUE
}

void insm_7(Frame *frame, ByteCodeStream *stream)
{
    // ICONST_4
    pushInt(frame->operandStack, 4);
    UPDATE_PC_AND_CONTINUE
}

void insm_8(Frame *frame, ByteCodeStream *stream)
{
    // ICONST_5
    pushInt(frame->operandStack, 5);
    UPDATE_PC_AND_CONTINUE
}

void insm_9(Frame *frame, ByteCodeStream *stream)
{
    // LCONST_0
    pushLong(frame->operandStack, 0);
    UPDATE_PC_AND_CONTINUE
}

void insm_10(Frame *frame, ByteCodeStream *stream)
{
    // LCONST_1
    pushLong(frame->operandStack, 1);
    UPDATE_PC_AND_CONTINUE
}

void insm_11(Frame *frame, ByteCodeStream *stream)
{
    // FCONST_0
    pushFloat(frame->operandStack, 0);
    UPDATE_PC_AND_CONTINUE
}

void insm_12(Frame *frame, ByteCodeStream *stream)
{
    // FCONST_1
    pushFloat(frame->operandStack, 1);
    UPDATE_PC_AND_CONTINUE
}

void insm_13(Frame *frame, ByteCodeStream *stream)
{
    // FCONST_2
    pushFloat(frame->operandStack, 2);
    UPDATE_PC_AND_CONTINUE
}

void insm_14(Frame *frame, ByteCodeStream *stream)
{
    // DCONST_0
    pushDouble(frame->operandStack, 0);
    UPDATE_PC_AND_CONTINUE
}

void insm_15(Frame *frame, ByteCodeStream *stream)
{
    // DCONST_1
    pushDouble(frame->operandStack, 1);
    UPDATE_PC_AND_CONTINUE
}

void insm_16(Frame *frame, ByteCodeStream *stream)
{
    // BIPUSH
    int32_t x = (int32_t)nextInt8(stream);
    pushInt(frame->operandStack, x);
    UPDATE_PC_AND_CONTINUE
}

void insm_17(Frame *frame, ByteCodeStream *stream)
{
    // SIPUSH
    int32_t x = （int32_t）nextInt16(stream);
    pushInt(frame->operandStack, x);
    UPDATE_PC_AND_CONTINUE
}

void insm_18(Frame *frame, ByteCodeStream *stream)
{
    // LDC
    uint8_t index = nextUint8(stream);
    RCP *rcp = frame->method->clazz->constantPool;
    RCPInfo *rcpInfo = getRCPInfo(rcp, (uint32_t)index);

    if (rcpInfo->type == CONSTANT_Integer)
    {
        pushInt(frame->operandStack, *(int32_t *)rcpInfo->data);
    }
    else if (rcpInfo->type == CONSTANT_Float)
    {
        pushFloat(frame->operandStack, *(float *)rcpInfo->data);
    }
    else if (rcpInfo->type == CONSTANT_String)
    {
        InstanceOOP *oop = resloveStringReference(frame->method->clazz, (char *)rcpInfo->data);
        pushRef(frame->operandStack, oop);
    }
    else if (rcpInfo->type == CONSTANT_Class)
    {
        IKlass *clazz = resloveClassReference(frame->method->clazz, (char *)rcpInfo->data);
        pushRef(frame->operandStack, getInstaceMirroClass(clazz));
    }
    else
    {
        // Method Type | Method Handler
        // TODO
    }
    UPDATE_PC_AND_CONTINUE
}

void insm_19(Frame *frame, ByteCodeStream *stream)
{
    // LDC_W
    // TODO
}

void insm_20(Frame *frame, ByteCodeStream *stream)
{
    // LDC2_W
    // TODO
}

#endif