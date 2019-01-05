#ifndef MOON_INS_LOAD_H
#define MOON_INS_LOAD_H

#include "runtime/class.h"
#include "runtime/thread.h"
#include "runtime/rcp.h"
#include "runtime/oop.h"
#include "interpreter/bytecode_stream.h"
#include "interpreter/bytecode_interpreter.h"

// 加载
// ILOAD 21   0x15 将指定的int型局部变量推送至栈顶
// LLOAD 22   0x16 将指定的long型局部变量推送至栈顶
// FLOAD 23   0x17 将指定的float型局部变量推送至栈顶
// DLOAD 24   0x18 将指定的double型局部变量推送至栈顶
// ALOAD 25   0x19 将指定的引用类型局部变量推送至栈顶
// ILOAD_0 26 0x1a 将第一个int型局部变量推送至栈顶
// ILOAD_1 27 0x1b 将第二个int型局部变量推送至栈顶
// ILOAD_2 28 0x1c 将第三个int型局部变量推送至栈顶
// ILOAD_3 29 0x1d 将第四个int型局部变量推送至栈顶
// LLOAD_0 30 0x1e 将第一个long型局部变量推送至栈顶
// LLOAD_1 31 0x1f 将第二个long型局部变量推送至栈顶
// LLOAD_2 32 0x20 将第三个long型局部变量推送至栈顶
// LLOAD_3 33 0x21 将第四个long型局部变量推送至栈顶
// FLOAD_0 34 0x22 将第一个float型局部变量推送至栈顶
// FLOAD_1 35 0x23 将第二个float型局部变量推送至栈顶
// FLOAD_2 36 0x24 将第三个float型局部变量推送至栈顶
// FLOAD_3 37 0x25 将第四个float型局部变量推送至栈顶
// DLOAD_0 38 0x26 将第一个double型局部变量推送至栈顶
// DLOAD_1 39 0x27 将第二个double型局部变量推送至栈顶
// DLOAD_2 40 0x28 将第三个double型局部变量推送至栈顶
// DLOAD_3 41 0x29 将第四个double型局部变量推送至栈顶
// ALOAD_0 42 0x2a 将第一个引用类型局部变量推送至栈顶
// ALOAD_1 43 0x2b 将第二个引用类型局部变量推送至栈顶
// ALOAD_2 44 0x2c 将第三个引用类型局部变量推送至栈顶
// ALOAD_3 45 0x2d 将第四个引用类型局部变量推送至栈顶
// IALOAD 46  0x2e 将int型数组指定索引的值推送至栈顶
// LALOAD 47  0x2f 将long型数组指定索引的值推送至栈顶
// FALOAD 48  0x30 将float型数组指定索引的值推送至栈顶
// DALOAD 49  0x31 将double型数组指定索引的值推送至栈顶
// AALOAD 50  0x32 将引用型数组指定索引的值推送至栈顶
// BALOAD 51  0x33 将boolean或byte型数组指定索引的值推送至栈顶
// CALOAD 52  0x34 将char型数组指定索引的值推送至栈顶
// SALOAD 53  0x35 将short型数组指定索引的值推送至栈顶

void insm_21(Frame *frame, ByteCodeStream *stream)
{
    // ILOAD
    pushInt(frame->operandStack, getInt(frame->localVars, nextInt8(stream)));
    UPDATE_PC_AND_CONTINUE
}

void insm_22(Frame *frame, ByteCodeStream *stream)
{
    // LLOAD
    pushLong(frame->operandStack, getLong(frame->localVars, nextInt8(stream)));
    UPDATE_PC_AND_CONTINUE
}

void insm_23(Frame *frame, ByteCodeStream *stream)
{
    // FLOAD
    pushFloat(frame->operandStack, getFloat(frame->localVars, nextInt8(stream)));
    UPDATE_PC_AND_CONTINUE
}

void insm_24(Frame *frame, ByteCodeStream *stream)
{
    // DLOAD
    pushDouble(frame->operandStack, getDouble(frame->localVars, nextInt8(stream)));
    UPDATE_PC_AND_CONTINUE
}

void insm_25(Frame *frame, ByteCodeStream *stream)
{
    // ALOAD
    pushRef(frame->operandStack, getRef(frame->localVars, nextInt8(stream)));
    UPDATE_PC_AND_CONTINUE
}

void insm_26(Frame *frame, ByteCodeStream *stream)
{
    // ILOAD_0
    pushInt(frame->operandStack, getInt(frame->localVars, 0));
    UPDATE_PC_AND_CONTINUE
}

// IALOAD 46  0x2e 将int型数组指定索引的值推送至栈顶
// LALOAD 47  0x2f 将long型数组指定索引的值推送至栈顶
// FALOAD 48  0x30 将float型数组指定索引的值推送至栈顶
// DALOAD 49  0x31 将double型数组指定索引的值推送至栈顶
// AALOAD 50  0x32 将引用型数组指定索引的值推送至栈顶
// BALOAD 51  0x33 将boolean或byte型数组指定索引的值推送至栈顶
// CALOAD 52  0x34 将char型数组指定索引的值推送至栈顶
// SALOAD 53  0x35 将short型数组指定索引的值推送至栈顶

void insm_51(Frame *frame, ByteCodeStream *stream)
{
    // BALOAD
    int32_t index = popInt(frame->operandStack);
    int8_t *arrRef = (int8_t *)popRef(frame->operandStack);
    pushInt(frame->operandStack, (int32_t)arrRef[index]);
    UPDATE_PC_AND_CONTINUE
}

#endif
