#include "interpreter/bytecode_interpreter.h"
#include "interpreter/ins_constant.h"

BC_IPT *buildByteCodeInterpreter()
{
    BC_IPT *r = malloc(sizeof(BC_IPT));
    REGISTER_INS_METHOD(r, 0);
    return r;
}

int execute(BC_IPT *bcIpt, JThread *thread, Method *method)
{
    Frame *frame = thread->createFrame(thread, method);
    pushFrame(thread, frame);
    ByteCodeStream *stream = (ByteCodeStream *)malloc(sizeof(ByteCodeStream));
    Frame *current;
    while ((current = currentFrame(thread)) != NULL)
    {
        thread->pc = frame->nextPC;
        stream->code = current->method->code;
        stream->pc = frame->nextPC;
        uint8_t opCode = readUint8(stream);
        // 在指令中实现对nextPC的设置
        (*bcIpt->call[opCode])(current, stream);
    }
}
