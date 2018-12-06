#ifndef MOON_THREAD_H
#define MOON_THREAD_H

#include <stdlib.h>
#include "runtime/class.h"

typedef struct LocalVars
{
} LocalVars;

typedef struct OperandStack
{
    uint32_t size;
} OperandStack;

typedef struct Frame
{
    // 栈中桢通过链表形式连接
    Frame *lower;
    // 本地变量表
    LocalVars *localVars;
    // 操作数栈
    OperandStack *operandStack;
    // 所属线程
    struct Thread *thread;
    // 当前帧所在方法
    struct Method *method;
    // 下一个执行指令位置
    int nextPC;
} Frame;

typedef struct Stack
{

} Stack;

typedef struct Thread
{
    int pc;

} Thread;

#endif