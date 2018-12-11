#include "runtime/frame.h"

void *getThis(struct LocalVars *vars)
{
    return getRef(vars, 0);
}

void setRef(struct LocalVars *vars, uint32_t index, void *ref)
{
    vars->vars[index]->ref = ref;
}

void *getRef(struct LocalVars *vars, uint32_t index)
{
    return vars->vars[index]->ref;
}

void setVar(struct LocalVars *vars, uint32_t index, union Slot *var)
{
    vars->vars[index] = var;
}
union Slot *getVar(struct LocalVars *vars, uint32_t index)
{
    return vars->vars[index];
}

void setInt(struct LocalVars *vars, uint32_t index, int32_t value)
{
    vars->vars[index]->num = value;
}

int32_t getInt(struct LocalVars *vars, uint32_t index)
{
    return vars->vars[index]->num;
}

void setLong(struct LocalVars *vars, uint32_t index, int64_t value)
{
    vars->vars[index]->num = (uint32_t)(value >> 32);
    vars->vars[index + 1]->num = (uint32_t)(value);
}

int64_t getLong(LocalVars *vars, uint32_t index)
{
    Slot *slot = vars->vars[index];
    return (int64_t)vars->vars[index]->num << 32 | (int64_t)vars->vars[index + 1]->num;
}

void setFloat(struct LocalVars *vars, uint32_t index, float value);
float getFloat(struct LocalVars *vars, uint32_t index);
void setDobule(struct LocalVars *vars, uint32_t index, double value);
double getDobule(struct LocalVars *vars, uint32_t index);

void pushRef(struct OperandStack *stack, void *ref)
{
    stack->slots[stack->size++]->ref = ref;
}

void *popRef(struct OperandStack *stack)
{
    return stack->slots[--stack->size]->ref;
}
void *topRef(struct OperandStack *stack)
{
    return stack->slots[stack->size - 1]->ref;
}
void pushVar(struct OperandStack *stack, union Slot *var)
{
    stack->slots[stack->size++] = var;
}

union Slot *popVar(struct OperandStack *stack)
{
    return stack->slots[--stack->size];
}

void pushBoolean(struct OperandStack *stack, int8_t value)
{
    stack->slots[stack->size++]->num = value;
}

int8_t popBoolean(struct OperandStack *stack)
{
    return (int8_t)(stack->slots[--stack->size]->num);
}
void pushInt(struct OperandStack *stack, int32_t value)
{
    stack->slots[stack->size++]->num = value;
}
int32_t popInt(struct OperandStack *stack)
{
    return stack->slots[--stack->size]->num;
}
void pushLong(struct OperandStack *stack, int64_t value);
int64_t popLong(struct OperandStack *stack);
void pushFloat(struct OperandStack *stack, float value);
float popFloat(struct OperandStack *stack);
void pushDouble(struct OperandStack *stack, double value);
double popDouble(struct OperandStack *stack);