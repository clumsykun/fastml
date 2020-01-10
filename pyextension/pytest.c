
#include "pyfunc.h"

int test_string_findall()
{
    char *source = "上海abcaaabcaabcbca";
    char *target = "上海";

    PyObject *result = string_findall(source, target);
    return 0;
}

int main(int argc, char *argv[])
{
    Py_Initialize();
    PyRun_SimpleString("print('Hello Python!')\n");
    test_string_findall();
    Py_Finalize();
    return 0;
}
