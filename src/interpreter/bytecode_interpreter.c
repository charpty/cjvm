#include "interpreter/bytecode_interpreter.h"

int execute(JThread *thread, Method *method)
{
    Frame *frame = thread->createFrame(thread, method);
    pushFrame(thread, frame);
    ByteCodeStream *stream = (ByteCodeStream *)malloc(sizeof(ByteCodeStream));
    Frame *current;

    while ((current = currentFrame(thread)) != NULL)
    {
        stream->code = current->method->code;
        stream->pc = 0;

        
    }
}
