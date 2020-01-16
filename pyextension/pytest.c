

#include <Python.h>
#include <assert.h>
#include "utils.h"
#include "pyfunc.h"


int test_basic()
{
    PyObject *str = PyUnicode_FromString("这是一个字符串string123。");
    Py_ssize_t size_source;
    wchar_t *source = PyUnicode_AsWideCharString(str, &size_source);

    source[0] = source[1];

    print_obj(str);

    PyObject *dict = PyDict_New();

    return 0;
}

int test_str_extract_keyword(void)
{
    PyObject *str = PyUnicode_FromString("abc[日志] 我在上海居住了三年，我的编码是 123456。");
    PyObject *dict = PyDict_New();

    PyDict_SetItemString( dict, "日志", PyLong_FromLong(0) );
    PyDict_SetItemString( dict, "上海", PyLong_FromLong(1) );
    PyDict_SetItemString( dict, "居住", PyLong_FromLong(2) );
    PyDict_SetItemString( dict, "三年", PyLong_FromLong(3) );
    PyDict_SetItemString( dict, "我", PyLong_FromLong(4) );
    PyDict_SetItemString( dict, "在", PyLong_FromLong(5) );

    PyObject *result;
    result = str_extract_keyword(str, dict, false);
    print_obj(result);
    result = str_extract_keyword(str, dict, true);
    print_obj(result);

    return 0;
}


int main(int argc, char *argv[])
{
    Py_Initialize();
    // test_basic();
    test_str_extract_keyword();

    Py_Finalize();
    return 0;
}
