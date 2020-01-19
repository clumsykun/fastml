#include "pyfunc.h"

size_t CHN_SIZE = 3;  /* 一个中文需要 3 个 char 字符 */

/* 使用`向前`、`向后`两种方法来提取关键字，返回字数更多的方法结果
 * 如果两种结果的字数一致，则返回权重高的方法结果
 * 
 * param:
 *     str_text[str]: 待处理文本
 *     dict_keywords[dict]: 词典
 * return:
 *     rv[list]: keywords list
 */
PyObject *str_extract_keyword(PyObject *str_text, PyObject *dict_keywords)
{
    PyObject *keywords, *forward, *backward, *rv, *_obj;
    wchar_t *text;
    Py_ssize_t size_text, max_len_keywords, n_keywords, n_forward, n_backward;
    Py_ssize_t i, _size, _move;
    double w_forward, w_backward;

    keywords     = PyDict_Keys(dict_keywords);
    forward      = PyList_New(0);
    backward     = PyList_New(0);
    rv           = NULL;
    _obj         = NULL;
    text      = PyUnicode_AsWideCharString(str_text, &size_text);
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
    while (i < size_text) {

        /* 初始化数据 */
        _move = 0;  /* 向后位移数 */
        _obj  = NULL;

        while (++_move <= max_len_keywords) {
            if (i + _move > size_text)  /* 防止内存越界 */
                break;

            _obj = PyDict_GetItem( dict_keywords,
                                   PyUnicode_FromWideChar(&text[i],
                                                          _move) );
            if (_obj == NULL) continue;
            else break;  /* 查到值 */
        }

        if (_obj == NULL)  /* 无效字符的情况 */
            i++;

        else {  /* 有效字符的情况 */
            PyList_Append( forward,
                           PyUnicode_FromWideChar(&text[i],
                                                  _move) );
            w_forward += PyFloat_AsDouble(_obj);
            n_forward += _move;
            i         += _move;
        }
    }

    /* 使用`向后`方法获取关键字 */
    i = size_text;
    while (i >= 0 ) {

        /* 初始化数据 */
        _move = 0;  /* 向前位移数 */
        _obj  = NULL;

        while (++_move <= max_len_keywords) {
            if (i - _move < 0)  /* 防止内存越界 */
                break;

            _obj = PyDict_GetItem( dict_keywords,
                                   PyUnicode_FromWideChar(&text[i - _move],
                                                          _move) );
            if (_obj == NULL) continue;
            else break;  /* 查到值 */
        }

        if (_obj == NULL)
            i--;

        else {
            PyList_Insert( backward,
                           0,
                           PyUnicode_FromWideChar(&text[i - _move],
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

PyObject *str_cal_tfidf(PyObject *list_corpus, PyObject *dict_keywords)
{
    PyObject *rv, *list_keywords_texts, *dict_keywords_cnt;
    PyObject *o1, *o2, *o3, *o4;
    Py_ssize_t size_corpus;

    list_keywords_texts = PyList_New(0);
    dict_keywords_cnt   = PyDict_New();
    o1                  = NULL;
    o2                  = NULL;
    o3                  = NULL;
    o4                  = NULL;
    rv                  = NULL;
    size_corpus         = PyList_Size(list_corpus);

    for (Py_ssize_t i = 0; i < PyList_Size(list_corpus); i++) {
        o1 = PyList_GetItem(list_corpus, i);  /* text */
        o2 = str_extract_keyword(o1, dict_keywords);  /* keywords list */

        for (Py_ssize_t j = 0; j < PyList_Size(o2); j++) {
            o3 = PyList_GetItem(o2, j);  /* keyword */
            o4 = PyDict_GetItem(dict_keywords_cnt, o3);  /* cnt */

            if (o4 == NULL)  /* 还未计数 */
                PyDict_SetItem( dict_keywords_cnt, o3, PyLong_FromLong(1) );
            else
                PyDict_SetItem( dict_keywords_cnt,
                                o3,
                                PyNumber_Add( o4, PyLong_FromLong(1) ) );
        }
    }

    PyDict_Keys(dict_keywords_cnt);


    print_obj(dict_keywords_cnt);
    rv = Py_None;
    return rv;
}

PyObject *str_reverse(PyObject *str_text)
{
    wchar_t *text, tmp;
    Py_ssize_t size_text, idx_max, idx_stop;

    text  = PyUnicode_AsWideCharString(str_text, &size_text);
    idx_max  = size_text - 1;
    idx_stop = (Py_ssize_t)ceil( (double)size_text / 2 );

    for (Py_ssize_t i = 0; i < idx_stop; i++) {
        tmp = text[i];
        text[i] = text[idx_max-i];
        text[idx_max-i] = tmp;
    }

    return PyUnicode_FromWideChar(text, size_text);
}
