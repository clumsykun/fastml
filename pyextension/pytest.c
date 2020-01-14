

#include <Python.h>
#include <assert.h>
#include "utils.h"
#include "pyfunc.h"


int test_string_mapping(void)
{
    const char *source = "[日志] 我在上海居住了三年，我的编码是 123456。";
    PyObject *dict = PyDict_New();

    PyDict_SetItemString( dict, "日志", PyLong_FromLong(0) );
    PyDict_SetItemString( dict, "上海", PyLong_FromLong(1) );
    PyDict_SetItemString( dict, "居住", PyLong_FromLong(2) );
    PyDict_SetItemString( dict, "三年", PyLong_FromLong(3) );
    PyDict_SetItemString( dict, "我", PyLong_FromLong(4) );
    PyDict_SetItemString( dict, "在", PyLong_FromLong(5) );

    PyObject *result = string_mapping(source, dict);
    print_obj(result);
    return 0;
}


int main(int argc, char *argv[])
{
    Py_Initialize();
    // PyRun_SimpleString("print(Python Initialized! \n");
    test_string_mapping();
    Py_Finalize();
    return 0;
}
