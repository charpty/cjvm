#ifndef MOON_INS_REFERENCE_H
#define MOON_INS_REFERENCE_H

#include "runtime/class.h"
#include "runtime/thread.h"
#include "runtime/rcp.h"
#include "runtime/oop.h"
#include "interpreter/bytecode_stream.h"
#include "interpreter/bytecode_interpreter.h"

// 引用
// GETSTATIC 178       0xb2 获取指定类的静态域，并将其值压入栈顶
// PUTSTATIC 179       0xb3 为指定的类的静态域赋值
// GETFIELD 180        0xb4 获取指定类的实例域，并将其值压入栈顶
// PUTFIELD 181        0xb5 为指定的类的实例域赋值
// INVOKEVIRTUAL 182   0xb6 调用实例方法
// INVOKESPECIAL 183   0xb7 调用超类构造方法，实例初始化方法，私有方法
// INVOKESTATIC 184    0xb8 调用静态方法
// INVOKEINTERFACE 185 0xb9 调用接口方法
// INVOKEDYNAMIC 186   0xba 调用动态链接方法
// NEW 187             0xbb 创建一个对象，并将其引用值压入栈顶
// NEWARRAY 188        0xbc 创建一个指定原始类型（如int、float、char„„）的数组，并将其引用值压入栈顶
// ANEWARRAY 189       0xbd 创建一个引用型（如类，接口，数组）的数组，并将其引用值压入栈顶
// ARRAYLENGTH 190     0xbe 获得数组的长度值并压入栈顶
// ATHROW 191          0xbf 将栈顶的异常抛出
// CHECKCAST 192       0xc0 检验类型转换，检验未通过将抛出ClassCastException
// INSTANCEOF 193      0xc1 检验对象是否是指定的类的实例，如果是将1压入栈顶，否则将0压入栈顶
// MONITORENTER 194    0xc2 获得对象的monitor，用于同步方法或同步块
// MONITOREXIT 195     0xc3 释放对象的monitor，用于同步方法或同步块

void insm_178(Frame *frame, ByteCodeStream *stream)
{
    // GETSTATIC
    int16_t filedRefIndex = nextInt16(stream);
    IKlass *clazz = frame->method->clazz;
    MemberRef *fieldRef = (MemberRef *)getRCPInfo(clazz->constantPool, filedRefIndex)->data;
    Field *field = resloveFieldReference(fieldRef);
    if (!isClassInit(field->clazz))
    {
        initClass(field->clazz);
    }
    char *descriptor = field->descriptor;
    uint32_t index = field->slotIndex;
    Slots *slots = getStaticVars(field->clazz);

    char flag = descriptor[0];
    if (flag == 'Z' || flag == 'B' || flag == 'C' || flag == 'S' || flag == 'I')
    {
        pushInt(frame->operandStack, getSlotInt(slots, index));
    }
    else if (flag == 'F')
    {
        pushFloat(frame->operandStack, getSlotFloat(slots, index));
    }
    else if (flag == 'J')
    {
        pushLong(frame->operandStack, getSlotLong(slots, index));
    }
    else if (flag == 'D')
    {
        pushDouble(frame->operandStack, getSlotDouble(slots, index));
    }
    else if (flag == 'L')
    {
        pushRef(frame->operandStack, getSlotRef(slots, index));
    }
    else
    {
    }
    UPDATE_PC_AND_CONTINUE
}

void insm_180(Frame *frame, ByteCodeStream *stream)
{
    // GETFIELD
    int16_t filedRefIndex = nextInt16(stream);
    IKlass *clazz = frame->method->clazz;
    MemberRef *fieldRef = (MemberRef *)getRCPInfo(clazz->constantPool, filedRefIndex)->data;
    Field *field = resloveFieldReference(fieldRef);
    if (!isClassInit(field->clazz))
    {
        initClass(field->clazz);
    }
    char *descriptor = field->descriptor;
    uint32_t index = field->slotIndex;
    InstanceOOP *oop = (InstanceOOP *)popRef(frame->operandStack);
    Slots slots = getIntanceVars(oop);
    // TODO
    UPDATE_PC_AND_CONTINUE
}

void insm_183(Frame *frame, ByteCodeStream *stream)
{
    // INVOKESPECIAL
    int16_t methodRefIndex = nextInt16(stream);
    IKlass *clazz = frame->method->clazz;
    RCP *rcp = clazz->constantPool;
    MemberRef *methodRef = (MemberRef *)getRCPInfo(clazz->constantPool, methodRefIndex)->data;
    Method *method = resloveMethodReference(methodRef);

    if (method->name == "<init>" && clazz != method->clazz)
    {
        // java.lang.NoSuchMethodError
    }
    if (isMethodStatic(method))
    {
        // java.lang.IncompatibleClassChangeError
    }

    void *ref = getRefFromTop(frame->operandStack, method->argCount - 1);
    if (ref == NULL)
    {
        // java.lang.NullPointerException
    }

    if (isMethodProtected(method))
    {
        // java.lang.IllegalAccessError
    }

    Method *methodToBeInvoked = lookupMethodInClass(clazz, method);

    JThread *thread = frame->thread;
    Frame *newFrame = thread->createFrame(thread, methodToBeInvoked);
    pushFrame(thread, newFrame);

    uint32_t argSlotCount = method->argCount;
    if (argSlotCount > 0)
    {
        for (int i = argSlotCount - 1; i >= 0; i--)
        {
            union Slot *slot = popVar(newFrame->operandStack);
            setVar(newFrame->localVars, (uint32_t)i, slot);
        }
    }
}

void insm_187(Frame *frame, ByteCodeStream *stream)
{
    // NEW
    int16_t index = nextInt16(stream);
    IKlass *clazz = frame->method->clazz;
    char *className = ((ClassRef *)getRCPInfo(clazz->constantPool, index)->data)->classname;
    IKlass *refClass = resloveClassReference(clazz, className);
    if (!isClassInit(refClass))
    {
        initClass(refClass);
    }
    InstanceOOP *oop = newObject(refClass);
    pushRef(frame->operandStack, oop);
    UPDATE_PC_AND_CONTINUE
}

void insm_190(Frame *frame, ByteCodeStream *stream)
{
    // ARRAYLENGTH
    ArrayOOP *arrayRef = (ArrayOOP *)popRef(frame->operandStack);
    if (arrayRef == NULL)
    {
        // java.lang.NullPointerException
    }
    pushInt(frame->operandStack, arrayRef->length);

    UPDATE_PC_AND_CONTINUE
}

void insm_191(Frame *frame, ByteCodeStream *stream)
{
    // ATHROW
    void *exceptionRef = popRef(frame->operandStack);
    if (exceptionRef == NULL)
    {
        // java.lang.NullPointerException
    }
    // TODO
    UPDATE_PC_AND_CONTINUE
}

#endif
