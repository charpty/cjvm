#ifndef MOON_INS_CONTROL_H
#define MOON_INS_CONTROL_H

#include "runtime/class.h"
#include "runtime/thread.h"
#include "runtime/rcp.h"
#include "runtime/oop.h"
#include "interpreter/bytecode_stream.h"
#include "interpreter/bytecode_interpreter.h"

// 控制
// GOTO 167         0xa7 无条件跳转
// JSR 168          0xa8 跳转至指定16位offset位置，并将jsr下一条指令地址压入栈顶
// RET 169          0xa9 返回至局部变量指定的index的指令位置（一般与jsr，jsr_w联合使用）
// TABLESWITCH 170  0xaa 用于switch条件跳转，case值连续（可变长度指令）
// LOOKUPSWITCH 171 0xab 用于switch条件跳转，case值不连续（可变长度指令）
// IRETURN 172      0xac 从当前方法返回int
// LRETURN 173      0xad 从当前方法返回long
// FRETURN 174      0xae 从当前方法返回float
// DRETURN 175      0xaf 从当前方法返回double
// ARETURN 176      0xb0 从当前方法返回对象引用
// RETURN 177       0xb1 从当前方法返回void

void insm_167(Frame *frame, ByteCodeStream *stream)
{
    // GOTO
    int32_t offset = (int32_t)nextInt16(stream);
    frame->nextPC = frame->thread->pc + offset;
}

// func (self *TABLE_SWITCH) FetchOperands(reader *base.BytecodeReader) {
// 	reader.SkipPadding()
// 	self.defaultOffset = reader.ReadInt32()
// 	self.low = reader.ReadInt32()
// 	self.high = reader.ReadInt32()
// 	jumpOffsetsCount := self.high - self.low + 1
// 	self.jumpOffsets = reader.ReadInt32s(jumpOffsetsCount)
// }

// func (self *TABLE_SWITCH) Execute(frame *rtda.Frame) {
// 	index := frame.OperandStack().PopInt()

// 	var offset int
// 	if index >= self.low && index <= self.high {
// 		offset = int(self.jumpOffsets[index-self.low])
// 	} else {
// 		offset = int(self.defaultOffset)
// 	}

// 	base.Branch(frame, offset)
// }

void insm_170(Frame *frame, ByteCodeStream *stream)
{
    // TABLESWITCH
    skipPadding(stream);
    int32_t defaultOffset = nextInt32(stream);
    int32_t low = nextInt32(stream);
    int32_t high = nextInt32(stream);
    int32_t offsetCount = high - low + 1;
    int32_t *offsets = nextInt32s(stream, offsetCount);
    int32_t index = popInt(frame->operandStack);
    int32_t offset;
    if (index >= low && index <= high)
    {
        offset = offsets[index - low];
    }
    else
    {
        offset = defaultOffset;
    }
    frame->nextPC = frame->thread->pc + offset;
}

void insm_171(Frame *frame, ByteCodeStream *stream)
{
    // LOOKUPSWITCH
    skipPadding(stream);
    int32_t key = popInt(frame->operandStack);
    int32_t defaultOffset = nextInt32(stream);
    int32_t offsetCount = nextInt32(stream);
    int32_t *offsets = nextInt32s(stream, offsetCount);
    for (int i = 0; i < offsetCount; i = i + 2)
    {
        if (offsets[i] == key)
        {
            int32_t offset = offsets[i + 1];
            frame->nextPC = frame->thread->pc + offset;
            break;
        }
    }
}

void insm_172(Frame *frame, ByteCodeStream *stream)
{
    // IRETURN
    JThread *thread = frame->thread;
    Frame *currentFrame = popFrame(thread);
    Frame *invokerFrame = topFrame(thread);
    pushInt(invokerFrame->operandStack, popInt(currentFrame->operandStack));
    UPDATE_PC_AND_CONTINUE
}

#endif
