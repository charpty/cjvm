#include "../../src/util/assert.c"

void testAsserEquals()
{
    char *a = "bb";
    char *b = "bb";
    char *c = "cc";
    assertEquals(a, b, "%s is not equal b", "a");
    assertEquals(a, c, "%s is not equal c", "a");
}

int main(int argc, char const *argv[])
{
    testAsserEquals();
    return 0;
}
