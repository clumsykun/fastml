#include "pyfunc.h"

size_t CHN_SIZE = 3;  /* 一个中文需要 3 个 char 字符 */


PyObject * str_extract_keyword(const char *source, PyObject *keywords, bool use_code)
{
    PyObject *words, *obj, *keyword_list;
    size_t i, j, size_word, size_add, size_source, max_size_word = 0;
    Py_ssize_t n_words;
    char *tmp_word = NULL, *tmp_str = NULL;

    words        = PyDict_Keys(keywords);
    n_words      = PyList_Size(words);
    size_source  = strlen(source);
    keyword_list = PyList_New(0);

    if (n_words == 0)  /* 可能不是列表 */
        goto error;

    if (keyword_list == NULL)  /* 内存错误 */
        goto error;

    for (Py_ssize_t i = 0; i < n_words; i++) {
        obj = PyList_GetItem(words, i);
        if ( !PyUnicode_Check(obj) ) continue;

        size_word = (size_t)PyUnicode_GetLength(obj);
        if (size_word > max_size_word)
            max_size_word = (size_t)size_word;
    }

    tmp_word = malloc( (size_t)max_size_word * CHN_SIZE );
    tmp_str  = malloc( size_source );
    if (tmp_word == NULL)
        goto error;
    if (tmp_str == NULL)
        goto error;

    i = 0;
    while (i < size_source) {

        /* 是中文的情况 */
        if (source[i] < 0) {

            /* 初始化数据 */
            memset(tmp_word, 0, (size_t)max_size_word * CHN_SIZE);
            size_add = 0;  /* 向后位移数 */
            obj = NULL;

            while ( (size_add += CHN_SIZE) <= (size_t)max_size_word * CHN_SIZE) {

                if (i + size_add > size_source)  /* 防止内存越界 */
                    break;

                memcpy(tmp_word, &source[i], size_add);
                obj = PyDict_GetItemString(keywords, tmp_word);

                if (obj == NULL) continue;
                else break;  /* 查到值 */
            }

            if (obj == NULL)  /* 无效字符的情况 */
                i += CHN_SIZE;

            else {  /* 有效字符的情况 */
                if (use_code)
                    PyList_Append(keyword_list, obj);
                else
                    PyList_Append(keyword_list, PyUnicode_FromString(tmp_word));

                i += size_add;
            }
        }

        else {  /* 不是中文时，只截取数字，数字格式为 double */
            memset(tmp_str, 0, size_source);
            if (48 <= source[i] && source[i] <= 57) {
                j = 0;  /* 记录数字个数 */
                while (48 <= source[i + j] && source[i + j] <= 57) j++;
                memcpy(tmp_str, &source[i], j);
                PyList_Append( keyword_list, PyUnicode_FromString(tmp_str) );
                i += j;
            }
            else if ( (65 <= source[i] && source[i] <= 90) ||
                      (97 <= source[i] && source[i] <= 122) ) {
                j = 0;  /* 记录字母个数 */
                while ( (65 <= source[i + j] && source[i + j] <= 90) ||
                        (97 <= source[i + j] && source[i + j] <= 122) ) j++;
                memcpy(tmp_str, &source[i], j);
                PyList_Append( keyword_list, PyUnicode_FromString(tmp_str) );
                i += j;
            }
            else {  /* 无用字符 */
                i++;
            }
        }
    }

    free(tmp_word);
    free(tmp_str);
    return keyword_list;

error:
    if (tmp_word != NULL) free(tmp_word);
    if (tmp_str != NULL) free(tmp_str);
    Py_XDECREF(words);
    Py_XDECREF(obj);
    Py_XDECREF(keyword_list);
    return Py_None;
}
