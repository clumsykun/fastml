

#include <Python.h>
#include <assert.h>
#include "utils.h"


int test_unicode_is_pure_ascii()
{
    char *string1 = "上海abcaaabcaabcbca";
    char *string2 = "asdsada";
    char *string3 = NULL;

    assert(unicode_is_pure_ascii(string1) == 0);
    assert(unicode_is_pure_ascii(string2) == 1);
    assert(unicode_is_pure_ascii(string3) == -1);
    return 0;
}

int main(int argc, char *argv[])
{
    Py_Initialize();
    PyRun_SimpleString("print('Hello Python!')\n");
    test_unicode_is_pure_ascii();
    Py_Finalize();
    return 0;
}
