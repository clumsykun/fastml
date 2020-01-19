

#include <Python.h>
#include <assert.h>
#include "utils.h"
#include "pyfunc.h"


int test_basic()
{
    PyObject *o, *j, *list = PyList_New(0);
    PyList_Append( list, PyLong_FromLong(0) );
    PyList_Append( list, PyLong_FromLong(0) );
    PyList_Append( list, PyLong_FromLong(0) );
    PyList_Append( list, PyLong_FromLong(0) );

    for (Py_ssize_t i = 0; i < 4; i++) {
        j = PyNumber_InPlaceAdd( PyList_GetItem(list, i), PyLong_FromLong(1) );
        print_obj(o);
        print_obj(j);
    }

    print_obj(list);
    return 0;
}

int test_str_cal_tfidf()
{
    PyObject *str_text1 = PyUnicode_FromString("日志 我在上海市居住了三年，我的编码是 123456。");
    PyObject *str_text2 = PyUnicode_FromString("我的编码是 123456。");
    PyObject *dict_keywords = PyDict_New();

    PyDict_SetItemString( dict_keywords, "日志", PyLong_FromLong(0) );
    PyDict_SetItemString( dict_keywords, "上海", PyLong_FromLong(1) );
    PyDict_SetItemString( dict_keywords, "上海市", PyLong_FromLong(2) );
    PyDict_SetItemString( dict_keywords, "居住", PyLong_FromLong(2) );
    PyDict_SetItemString( dict_keywords, "三年", PyLong_FromLong(3) );
    PyDict_SetItemString( dict_keywords, "我", PyLong_FromLong(4) );
    PyDict_SetItemString( dict_keywords, "在", PyLong_FromLong(5) );

    PyObject *list_corpus = PyList_New(0);

    PyList_Append(list_corpus, str_text1);
    PyList_Append(list_corpus, str_text2);

    PyObject *result;
    result = str_cal_tfidf(list_corpus, dict_keywords);
    print_obj(result);
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
