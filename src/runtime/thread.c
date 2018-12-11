#include "runtime/thread.h"

struct JThread *createThread()
{
    struct JThread *thread = malloc(sizeof(struct JThread));
    thread->pc = 0;
    return thread;
}

void pushFrame(struct JThread *thread);
struct Frame *popFrame(struct JThread *thread);
struct Frame *currentFrame(struct JThread *thread);