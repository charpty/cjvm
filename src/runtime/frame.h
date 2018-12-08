#ifndef MOON_FRAME_Hdouble value);
#define MOON_FRAME_H

#include <stdlib.h>

typedef union LocalVar {
    int32_t num;
    void *ref;
} LocalVar;

typedef struct LocalVars
{
    // 保存代码执行过程中本地变量的值
    uint32_t size;
    union LocalVar **localVars;
} LocalVars;

typedef struct OperandStack
{
    // 只是模拟指令执行的栈，没有存储意义
    uint32_t size;
    // 模拟链表存储，使用数组存储有些浪费
    union LocalVar **vars;
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

void *getThis(struct LocalVars *vars);
void setRef(struct LocalVars *vars, uint32_t index, void *ref);
void *getRef(struct LocalVars *vars, uint32_t index);
void setVar(struct LocalVars *vars, uint32_t index, union LocalVar *var);
union LocalVar *getVar(struct LocalVars *vars, uint32_t index);
void setInt(struct LocalVars *vars, uint32_t index, int32_t value);
int32_t getInt(struct LocalVars *vars, uint32_t index);
void setLong(struct LocalVars *vars, uint32_t index, int64_t value);
int64_t getLongstruct(LocalVars *localVars, uint32_t index);
void setFloat(struct LocalVars *vars, uint32_t index, float value);
float getFloat(struct LocalVars *vars, uint32_t index);
void setDobule(struct LocalVars *vars, uint32_t index, double value);
double getDobule(struct LocalVars *vars, uint32_t index);

void pushRef(struct OperandStack *stack, void *ref);
void *popRef(struct OperandStack *stack);
void *topRef(struct OperandStack *stack);
void pushVar(struct OperandStack *stack, union LocalVar *var);
union LocalVar *popVar(struct OperandStack *stack);
void pushBoolean(struct OperandStack *stack, int8_t *value);
int8_t popBoolean(struct OperandStack *stack);
void popInt(struct OperandStack *stack, int32_t value);
int32_t popInt(struct OperandStack *stack);
void pushLong(struct OperandStack *stack, int64_t value);
int64_t popLong(struct OperandStack *stack);
void pushFloat(struct OperandStack *stack, float value);
float popFloat(struct OperandStack *stack);
void pushDouble(struct OperandStack *stack, double value);
double popDouble(struct OperandStack *stack);

#endif