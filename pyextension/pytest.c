

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

int test_s_cal_tfidf()
{
    PyObject *s_text1 = PyUnicode_FromString("日志 我在上海市居住了三年，我的编码是 123456。");
    PyObject *s_text2 = PyUnicode_FromString("我的编码是 123456。");
    PyObject *s_text3 = PyUnicode_FromString("上海三年来生产总值为 XXX");
    PyObject *d_keywords = PyDict_New();

    PyDict_SetItemString( d_keywords, "日志", PyLong_FromLong(0) );
    PyDict_SetItemString( d_keywords, "上海", PyLong_FromLong(1) );
    PyDict_SetItemString( d_keywords, "上海市", PyLong_FromLong(2) );
    PyDict_SetItemString( d_keywords, "居住", PyLong_FromLong(2) );
    PyDict_SetItemString( d_keywords, "三年", PyLong_FromLong(3) );
    PyDict_SetItemString( d_keywords, "我", PyLong_FromLong(4) );
    PyDict_SetItemString( d_keywords, "在", PyLong_FromLong(5) );
    PyDict_SetItemString( d_keywords, "编码", PyLong_FromLong(5) );

    PyObject *l_corpus = PyList_New(0);

    PyList_Append(l_corpus, s_text1);
    PyList_Append(l_corpus, s_text2);
    PyList_Append(l_corpus, s_text3);

    PyObject *result;
    result = s_cal_tfidf(l_corpus, d_keywords);
    print_obj(result);
    return 0;
}

int test_s_reverse()
{
    PyObject *str = PyUnicode_FromString("阿森纳是冠军!arsenal is champion!");
    PyObject *s_rev = s_reverse(str);

    print_obj(str);
    print_obj(s_rev);
    return 0;
}

int main(int argc, char *argv[])
{
    Py_Initialize();

    /* test func */
    // test_basic();
    // test_s_extract_keyword();
    test_s_cal_tfidf();
    // test_s_reverse();

    Py_Finalize();
    return 0;
}
