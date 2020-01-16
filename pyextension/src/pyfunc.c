#include "pyfunc.h"

size_t CHN_SIZE = 3;  /* 一个中文需要 3 个 char 字符 */


PyObject * str_extract_keyword(PyObject *str, PyObject *keywords, bool use_code)
{
    PyObject *words, *obj, *keyword_list;
    Py_ssize_t i, size_word, size_add, max_size_word = 0;
    wchar_t *source;
    Py_ssize_t n_words, size_source;


    source       = PyUnicode_AsWideCharString(str, &size_source);
    words        = PyDict_Keys(keywords);
    n_words      = PyList_Size(words);
    keyword_list = PyList_New(0);

    if (n_words == 0)  /* 可能不是列表 */
        goto error;

    if (keyword_list == NULL)  /* 内存错误 */
        goto error;

    for (i = 0; i < n_words; i++) {
        obj = PyList_GetItem(words, i);
        if ( !PyUnicode_Check(obj) ) continue;

        size_word = PyUnicode_GetLength(obj);
        if (size_word > max_size_word)
            max_size_word = size_word;
    }



    i = 0;
    while (i < size_source) {

        /* 初始化数据 */
        size_add = 0;  /* 向后位移数 */
        obj      = NULL;

        while (++size_add <= max_size_word) {

            if (i + size_add > size_source)  /* 防止内存越界 */
                break;

            obj = PyDict_GetItem( keywords, PyUnicode_FromWideChar(&source[i], size_add) );

            if (obj == NULL) continue;
            else break;  /* 查到值 */
        }

        if (obj == NULL)  /* 无效字符的情况 */
            i++;

        else {  /* 有效字符的情况 */
            if (use_code)
                PyList_Append(keyword_list, obj);
            else
                PyList_Append( keyword_list, PyUnicode_FromWideChar(&source[i], size_add) );

            i += size_add;
        }

    }

    return keyword_list;

error:
    Py_XDECREF(words);
    Py_XDECREF(obj);
    Py_XDECREF(keyword_list);
    return Py_None;
}
