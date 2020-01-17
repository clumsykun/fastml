#include "pyfunc.h"

size_t CHN_SIZE = 3;  /* 一个中文需要 3 个 char 字符 */

/* 使用`向前`、`向后`两种方法来提取关键字，返回字数更多的方法结果
 * 如果两种结果的字数一致，则返回权重高的方法结果
 */
PyObject *str_extract_keyword(PyObject *obj_unicode, PyObject *dict_keywords)
{
    PyObject *keywords, *forward, *backward, *rv, *_obj;
    wchar_t *unicode;
    Py_ssize_t size_unicode, max_len_keywords, n_keywords, n_forward, n_backward;
    Py_ssize_t i, _size, _move;
    double w_forward, w_backward;

    keywords     = PyDict_Keys(dict_keywords);
    forward      = PyList_New(0);
    backward     = PyList_New(0);
    rv           = NULL;
    _obj         = NULL;
    unicode      = PyUnicode_AsWideCharString(obj_unicode, &size_unicode);
    n_keywords   = PyList_Size(keywords);
    n_forward    = 0;  /* `向前`方法获取关键字字数（不是词数） */
    n_backward   = 0;  /* `向后`方法获取关键字字数（不是词数） */
    w_forward    = 0;
    w_backward   = 0;

    if (n_keywords == 0)  /* 可能不是列表 */
        goto error;

    if (forward == NULL)  /* 内存错误 */
        goto error;

    max_len_keywords = 0;  /* 字典中词语的最大长度 */
    for (i = 0; i < n_keywords; i++) {
        _obj = PyList_GetItem(keywords, i);
        if ( !PyUnicode_Check(_obj) )
            continue;

        _size = PyUnicode_GetLength(_obj);
        if (_size > max_len_keywords)
            max_len_keywords = _size;
    }

    /* 使用`向前`方法获取关键字 */
    i = 0;
    while (i < size_unicode) {

        /* 初始化数据 */
        _move = 0;  /* 向后位移数 */
        _obj  = NULL;

        while (++_move <= max_len_keywords) {
            if (i + _move > size_unicode)  /* 防止内存越界 */
                break;

            _obj = PyDict_GetItem( dict_keywords,
                                   PyUnicode_FromWideChar(&unicode[i],
                                                          _move) );
            if (_obj == NULL) continue;
            else break;  /* 查到值 */
        }

        if (_obj == NULL)  /* 无效字符的情况 */
            i++;

        else {  /* 有效字符的情况 */
            PyList_Append( forward,
                           PyUnicode_FromWideChar(&unicode[i],
                                                  _move) );
            w_forward += PyFloat_AsDouble(_obj);
            n_forward += _move;
            i         += _move;
        }
    }

    /* 使用`向后`方法获取关键字 */
    i = size_unicode;
    while (i >= 0 ) {

        /* 初始化数据 */
        _move = 0;  /* 向前位移数 */
        _obj  = NULL;

        while (++_move <= max_len_keywords) {
            if (i - _move < 0)  /* 防止内存越界 */
                break;

            _obj = PyDict_GetItem( dict_keywords,
                                   PyUnicode_FromWideChar(&unicode[i - _move],
                                                          _move) );
            if (_obj == NULL) continue;
            else break;  /* 查到值 */
        }

        if (_obj == NULL)
            i--;

        else {
            PyList_Insert( backward,
                           0,
                           PyUnicode_FromWideChar(&unicode[i - _move],
                                                  _move) );

            w_backward += PyFloat_AsDouble(_obj);
            n_backward += _move;
            i          -= _move;
        }
    }

    if (n_forward > n_backward)
        rv = forward;

    else if (n_backward > n_forward)
        rv = backward;

    /* 两种方法的字数一致时，取权重高的方法
     * 如果权重也相同，则使用 `向前` 方法
     */
    else
        rv = (w_forward >= w_backward) ? forward : backward;

    return rv;

error:
    Py_XDECREF(keywords);
    Py_XDECREF(_obj);
    Py_XDECREF(forward);
    Py_XDECREF(backward);
    Py_XDECREF(rv);
    return Py_None;
}

PyObject *str_cal_tfidf(PyObject *obj_unicode, PyObject *dict_keywords)
{
    PyObject *rv;

    rv = Py_None;
    return rv;
}

PyObject *str_reverse(PyObject *obj_unicode)
{
    wchar_t *unicode, tmp;
    Py_ssize_t size_unicode, idx_max, idx_stop;

    unicode  = PyUnicode_AsWideCharString(obj_unicode, &size_unicode);
    idx_max  = size_unicode - 1;
    idx_stop = (Py_ssize_t)ceil( (double)size_unicode / 2 );

    for (Py_ssize_t i = 0; i < idx_stop; i++) {
        tmp = unicode[i];
        unicode[i] = unicode[idx_max-i];
        unicode[idx_max-i] = tmp;
    }

    return PyUnicode_FromWideChar(unicode, size_unicode);
}
