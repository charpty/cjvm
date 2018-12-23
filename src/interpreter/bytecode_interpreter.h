#ifndef MOON_BYTECODE_INTERPRETER_H
#define MOON_BYTECODE_INTERPRETER_H
#include "runtime/class.h"
#include "runtime/thread.h"
#include "interpreter/bytecode_stream.h"

// byte code interpreter
typedef struct BC_IPT
{
    void (*ins_execute[256])(Frame *frame, ByteCodeStream stream);
} BC_IPT;

int execute(JThread *thread, Method *method);

#endif