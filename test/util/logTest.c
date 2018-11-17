#include "../../src/util/log.h"

void testLogError()
{
    LOG_ERROR("module %s has %d %s", "order", 2, "unlink pay order");
}

void testLogDebug()
{
    LOG_DEBUG("path=%s already init %ld time by %s", "/a/b/c", 2l, "jack");
}

int main(int argc, char const *argv[])
{
    testLogDebug();
    testLogError();
    return 0;
}
