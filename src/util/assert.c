#include <stdlib.h>
#include <string.h>
#include "log.c"
#include "assert.h"

void assertEquals(char *s, char *d, char *message)
{
    if (strcmp(s, d) != 0)
    {
        LOG_ERROR("%s, s is %s, d is %s", message, s, d);
        exit(1);
    }
}
