

#include <Python.h>
#include <assert.h>
#include "utils.h"
#include "pyfunc.h"


int test_basic()
{
    PyObject *str1 = PyUnicode_FromString("字符串1");
    PyObject *str2 = PyUnicode_FromString("字符串2");

    str1 = str2;
    print_obj(str1);
    print_obj(str2);

    return 0;
}

int test_str_extract_keyword()
{
    PyObject *str = PyUnicode_FromString("日志 我在上海市居住了三年，我的编码是 123456。");
    PyObject *dict = PyDict_New();

    PyDict_SetItemString( dict, "日志", PyLong_FromLong(0) );
    PyDict_SetItemString( dict, "上海", PyLong_FromLong(1) );
    PyDict_SetItemString( dict, "上海市", PyLong_FromLong(2) );
    PyDict_SetItemString( dict, "居住", PyLong_FromLong(2) );
    PyDict_SetItemString( dict, "三年", PyLong_FromLong(3) );
    PyDict_SetItemString( dict, "我", PyLong_FromLong(4) );
    PyDict_SetItemString( dict, "在", PyLong_FromLong(5) );

    PyObject *result;
    result = str_extract_keyword(str, dict);
    print_obj(result);

    return 0;
}

int test_str_cal_tfidf()
{
    return 0;
}

int test_str_reverse()
{
    PyObject *str = PyUnicode_FromString("阿森纳是冠军!arsenal is champion!");
    PyObject *str_rev = str_reverse(str);

    print_obj(str);
    print_obj(str_rev);
    return 0;
}

int main(int argc, char *argv[])
{
    Py_Initialize();

    /* test func */
    // test_basic();
    // test_str_extract_keyword();
    test_str_cal_tfidf();
    // test_str_reverse();

    Py_Finalize();
    return 0;
}
