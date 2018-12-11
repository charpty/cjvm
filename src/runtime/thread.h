#ifndef MOON_THREAD_H
#define MOON_THREAD_H

#include <stdlib.h>
#include "runtime/class.h"
#include "runtime/frame.h"

// https://docs.oracle.com/javase/specs/jvms/se11/html/jvms-2.html#jvms-2.6
typedef struct Stack
{
    uint32_t maxSize;
    uint32_t size;
    // 栈中存的都是一个又一个栈帧
    struct Frame *topFrame;
} Stack;

// Java11 Run-Time Data Areas: https://docs.oracle.com/javase/specs/jvms/se11/html/jvms-2.html#jvms-2.5
typedef struct JThread
{
    int pc;
    // 每个线程都私有一个Java虚拟机栈
    struct Stack stack;
    // 创建Frame的操作比较复杂多变
    struct Frame (*createFrame)(struct JThread *thread);
} JThread;

struct JThread *createThread();

void pushFrame(struct JThread *thread);
struct Frame *popFrame(struct JThread *thread);
struct Frame *currentFrame(struct JThread *thread);
#endif
