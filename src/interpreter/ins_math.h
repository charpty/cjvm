#ifndef MOON_INS_MATH_H
#define MOON_INS_MATH_H

#include "runtime/class.h"
#include "runtime/thread.h"
#include "runtime/rcp.h"
#include "runtime/oop.h"
#include "interpreter/bytecode_stream.h"
#include "interpreter/bytecode_interpreter.h"

// 数学
// IADD 96   0x60 将栈顶两int型数值相加并将结果压入栈顶
// LADD 97   0x61 将栈顶两long型数值相加并将结果压入栈顶
// FADD 98   0x62 将栈顶两float型数值相加并将结果压入栈顶
// DADD 99   0x63 将栈顶两double型数值相加并将结果压入栈顶
// ISUB 100  0x64 将栈顶两int型数值相减并将结果压入栈顶
// LSUB 101  0x65 将栈顶两long型数值相减并将结果压入栈顶
// FSUB 102  0x66 将栈顶两float型数值相减并将结果压入栈顶
// DSUB 103  0x67 将栈顶两double型数值相减并将结果压入栈顶
// IMUL 104  0x68 将栈顶两int型数值相乘并将结果压入栈顶
// LMUL 105  0x69 将栈顶两long型数值相乘并将结果压入栈顶
// FMUL 106  0x6a 将栈顶两float型数值相乘并将结果压入栈顶
// DMUL 107  0x6b 将栈顶两double型数值相乘并将结果压入栈顶
// IDIV 108  0x6c 将栈顶两int型数值相除并将结果压入栈顶
// LDIV 109  0x6d 将栈顶两long型数值相除并将结果压入栈顶
// FDIV 110  0x6e 将栈顶两float型数值相除并将结果压入栈顶
// DDIV 111  0x6f 将栈顶两double型数值相除并将结果压入栈顶
// IREM 112  0x70 将栈顶两int型数值作取模运算并将结果压入栈顶
// LREM 113  0x71 将栈顶两long型数值作取模运算并将结果压入栈顶
// FREM 114  0x72 将栈顶两float型数值作取模运算并将结果压入栈顶
// DREM 115  0x73 将栈顶两double型数值作取模运算并将结果压入栈顶
// INEG 116  0x74 将栈顶int型数值取负并将结果压入栈顶
// LNEG 117  0x75 将栈顶long型数值取负并将结果压入栈顶
// FNEG 118  0x76 将栈顶float型数值取负并将结果压入栈顶
// DNEG 119  0x77 将栈顶double型数值取负并将结果压入栈顶
// ISHL 120  0x78 将int型数值左移位指定位数并将结果压入栈顶
// LSHL 121  0x79 将long型数值左移位指定位数并将结果压入栈顶
// ISHR 122  0x7a 将int型数值右（有符号）移位指定位数并将结果压入栈顶
// LSHR 123  0x7b 将long型数值右（有符号）移位指定位数并将结果压入栈顶
// IUSHR 124 0x7c 将int型数值右（无符号）移位指定位数并将结果压入栈顶
// LUSHR 125 0x7d 将long型数值右（无符号）移位指定位数并将结果压入栈顶
// IAND 126  0x7e 将栈顶两int型数值作“按位与”并将结果压入栈顶
// LAND 127  0x7f 将栈顶两long型数值作“按位与”并将结果压入栈顶
// IOR 128   0x80 将栈顶两int型数值作“按位或”并将结果压入栈顶
// LOR 129   0x81 将栈顶两long型数值作“按位或”并将结果压入栈顶
// IXOR 130  0x82 将栈顶两int型数值作“按位异或”并将结果压入栈顶
// LXOR 131  0x83 将栈顶两long型数值作“按位异或”并将结果压入栈顶
// IINC 132  0x84 将指定int型变量增加指定值

void insm_96(Frame *frame, ByteCodeStream *stream)
{
    // IADD
    int32_t x1 = popInt(frame->operandStack);
    int32_t x2 = popInt(frame->operandStack);
    pushInt(frame->operandStack, (x1 + x2));
    UPDATE_PC_AND_CONTINUE
}

void insm_105(Frame *frame, ByteCodeStream *stream)
{
    // LMUL
    int64_t x1 = popLong(frame->operandStack);
    int64_t x2 = popLong(frame->operandStack);
    pushLong(frame->operandStack, (x1 * x2));
    UPDATE_PC_AND_CONTINUE
}

void insm_125(Frame *frame, ByteCodeStream *stream)
{
    // LUSHR
    uint32_t offset = (uint32_t)popInt(frame->operandStack);
    int64_t x = popLong(frame->operandStack);
    pushInt(frame->operandStack, ((u_int64_t)x) >> offset);
    UPDATE_PC_AND_CONTINUE
}

void insm_126(Frame *frame, ByteCodeStream *stream)
{
    // IAND
    int32_t x1 = popInt(frame->operandStack);
    int32_t x2 = popInt(frame->operandStack);
    pushInt(frame->operandStack, (x1 & x2));
    UPDATE_PC_AND_CONTINUE
}

#endif
