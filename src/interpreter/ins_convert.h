#ifndef MOON_INS_CONVERT_H
#define MOON_INS_CONVERT_H

#include "runtime/class.h"
#include "runtime/thread.h"
#include "runtime/rcp.h"
#include "runtime/oop.h"
#include "interpreter/bytecode_stream.h"
#include "interpreter/bytecode_interpreter.h"

// 转换
// I2L 133 0x85 将栈顶int型数值强制转换成long型数值并将结果压入栈顶
// I2F 134 0x86 将栈顶int型数值强制转换成float型数值并将结果压入栈顶
// I2D 135 0x87 将栈顶int型数值强制转换成double型数值并将结果压入栈顶
// L2I 136 0x88 将栈顶long型数值强制转换成int型数值并将结果压入栈顶
// L2F 137 0x89 将栈顶long型数值强制转换成float型数值并将结果压入栈顶
// L2D 138 0x8a 将栈顶long型数值强制转换成double型数值并将结果压入栈顶
// F2I 139 0x8b 将栈顶float型数值强制转换成int型数值并将结果压入栈顶
// F2L 140 0x8c 将栈顶float型数值强制转换成long型数值并将结果压入栈顶
// F2D 141 0x8d 将栈顶float型数值强制转换成double型数值并将结果压入栈顶
// D2I 142 0x8e 将栈顶double型数值强制转换成int型数值并将结果压入栈顶
// D2L 143 0x8f 将栈顶double型数值强制转换成long型数值并将结果压入栈顶
// D2F 144 0x90 将栈顶double型数值强制转换成float型数值并将结果压入栈顶
// I2B 145 0x91 将栈顶int型数值强制转换成byte型数值并将结果压入栈顶
// I2C 146 0x92 将栈顶int型数值强制转换成char型数值并将结果压入栈顶
// I2S 147 0x93 将栈顶int型数值强制转换成short型数值并将结果压入栈顶

void insm_133(Frame *frame, ByteCodeStream *stream)
{
    // I2L
    int32_t x = popInt(frame->operandStack);
    pushLong(frame->operandStack, (int64_t)x);
    UPDATE_PC_AND_CONTINUE
}

void insm_143(Frame *frame, ByteCodeStream *stream)
{
    // D2L
    double x = popDouble(frame->operandStack);
    pushLong(frame->operandStack, (int64_t)x);
    UPDATE_PC_AND_CONTINUE
}

#endif
