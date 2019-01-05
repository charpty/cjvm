#ifndef MOON_INS_STACK_H
#define MOON_INS_STACK_H

#include "runtime/class.h"
#include "runtime/thread.h"
#include "runtime/rcp.h"
#include "runtime/oop.h"
#include "interpreter/bytecode_stream.h"
#include "interpreter/bytecode_interpreter.h"

// 栈
// POP 87     0x57 将栈顶数值弹出（数值不能是long或double类型的）
// POP2 88    0x58 将栈顶的一个（long或double类型的）或两个数值弹出（其它）
// DUP 89     0x59 复制栈顶数值并将复制值压入栈顶
// DUP_X1 90  0x5a 复制栈顶数值并将两个复制值压入栈顶
// DUP_X2 91  0x5b 复制栈顶数值并将三个（或两个）复制值压入栈顶
// DUP2 92    0x5c 复制栈顶一个（long或double类型的)或两个（其它）数值并将复制值压入栈顶
// DUP2_X1 93 0x5d dup_x1指令的双倍版本
// DUP2_X2 94 0x5e dup_x2指令的双倍版本
// SWAP 95    0x5f 将栈最顶端的两个数值互换（数值不能是long或double类型的）

void insm_87(Frame *frame, ByteCodeStream *stream)
{
    // POP
    popVar(frame->operandStack);
    UPDATE_PC_AND_CONTINUE
}

void insm_88(Frame *frame, ByteCodeStream *stream)
{
    // POP2
    popVar(frame->operandStack);
    popVar(frame->operandStack);
    UPDATE_PC_AND_CONTINUE
}

void insm_89(Frame *frame, ByteCodeStream *stream)
{
    // DUP
    union Slot *x = popVar(frame->operandStack);
    pushVar(frame->operandStack, x);
    pushVar(frame->operandStack, x);
    UPDATE_PC_AND_CONTINUE
}

void insm_90(Frame *frame, ByteCodeStream *stream)
{
    // DUP_X1
    union Slot *x1 = popVar(frame->operandStack);
    union Slot *x2 = popVar(frame->operandStack);

    pushVar(frame->operandStack, x1);
    pushVar(frame->operandStack, x2);
    pushVar(frame->operandStack, x1);
    UPDATE_PC_AND_CONTINUE
}

void insm_91(Frame *frame, ByteCodeStream *stream)
{
    // DUP_X2
    union Slot *x1 = popVar(frame->operandStack);
    union Slot *x2 = popVar(frame->operandStack);
    union Slot *x3 = popVar(frame->operandStack);

    pushVar(frame->operandStack, x1);
    pushVar(frame->operandStack, x3);
    pushVar(frame->operandStack, x2);
    pushVar(frame->operandStack, x1);
    UPDATE_PC_AND_CONTINUE
}

void insm_92(Frame *frame, ByteCodeStream *stream)
{
    // DUP2
    union Slot *x1 = popVar(frame->operandStack);
    union Slot *x2 = popVar(frame->operandStack);

    pushVar(frame->operandStack, x2);
    pushVar(frame->operandStack, x1);
    pushVar(frame->operandStack, x2);
    pushVar(frame->operandStack, x1);
    UPDATE_PC_AND_CONTINUE
}

void insm_93(Frame *frame, ByteCodeStream *stream)
{
    // DUP2_X1
    union Slot *x1 = popVar(frame->operandStack);
    union Slot *x2 = popVar(frame->operandStack);
    union Slot *x3 = popVar(frame->operandStack);

    pushVar(frame->operandStack, x2);
    pushVar(frame->operandStack, x1);
    pushVar(frame->operandStack, x3);
    pushVar(frame->operandStack, x2);
    pushVar(frame->operandStack, x1);
    UPDATE_PC_AND_CONTINUE
}

void insm_94(Frame *frame, ByteCodeStream *stream)
{
    // DUP2_X2
    union Slot *x1 = popVar(frame->operandStack);
    union Slot *x2 = popVar(frame->operandStack);
    union Slot *x3 = popVar(frame->operandStack);
    union Slot *x4 = popVar(frame->operandStack);

    pushVar(frame->operandStack, x2);
    pushVar(frame->operandStack, x1);
    pushVar(frame->operandStack, x4);
    pushVar(frame->operandStack, x3);
    pushVar(frame->operandStack, x2);
    pushVar(frame->operandStack, x1);
    UPDATE_PC_AND_CONTINUE
}

void insm_95(Frame *frame, ByteCodeStream *stream)
{
    // SWAP
    union Slot *x1 = popVar(frame->operandStack);
    union Slot *x2 = popVar(frame->operandStack);

    pushVar(frame->operandStack, x1);
    pushVar(frame->operandStack, x2);
    UPDATE_PC_AND_CONTINUE
}

#endif
