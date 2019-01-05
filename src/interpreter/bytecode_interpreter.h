#ifndef MOON_BYTECODE_INTERPRETER_H
#define MOON_BYTECODE_INTERPRETER_H

#include "runtime/class.h"
#include "runtime/thread.h"
#include "interpreter/bytecode_stream.h"

#define INS_METHOD(OP) insm_##OP
#define REGISTER_INS_METHOD(r, op) r->call[op] = INS_METHOD(op)

#define UPDATE_PC_AND_CONTINUE frame->nextPC = stream->pc;

// byte code interpreter
typedef struct BC_IPT
{
    // 对应205个指令，其opcode即数组下标
    void (*call[256])(Frame *frame, ByteCodeStream *stream);
} BC_IPT;

BC_IPT *buildByteCodeInterpreter();
int execute(BC_IPT *bcIpt, JThread *thread, Method *method);

#endif