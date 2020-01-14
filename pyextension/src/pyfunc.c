#include "pyfunc.h"

size_t CHN_SIZE = 3;  /* 一个中文需要 3 个 char 字符 */


PyObject * string_mapping(const char *source, PyObject *dict)
{

    PyObject *words, *obj;
    size_t i, size_add, size_source, max_size_word = 0;
    Py_ssize_t size_word, n_words;

    words = PyDict_Keys(dict);
    n_words = PyList_Size(words);
    size_source = strlen(source);

    for (Py_ssize_t i = 0; i < n_words; i++) {
        obj = PyList_GetItem(words, i);
        if ( !PyUnicode_Check(obj) ) continue;

        size_word = PyUnicode_GetLength(obj);
        if (size_word > max_size_word)
            max_size_word = (size_t)size_word;
    }

    char *tmp_char = malloc((size_t)max_size_word * CHN_SIZE);
    PyObject *code_list = PyList_New(0);

    i = 0;
    while (i < size_source) {

        /* 是中文的情况 */
        if (source[i] < 0) {

            /* 初始化数据 */
            memset(tmp_char, 0, (size_t)max_size_word * CHN_SIZE);
            size_add = 0;  /* 向后位移数 */
            obj = NULL;

            while ( (size_add += CHN_SIZE) <= (size_t)max_size_word * CHN_SIZE) {

                if (i + size_add > size_source)  /* 防止内存越界 */
                    break;

                memcpy(tmp_char, &source[i], size_add);
                obj = PyDict_GetItemString(dict, tmp_char);

                if (obj == NULL) continue;
                else break;  /* 查到值 */
            }

            if (obj == NULL)  /* 无效字符的情况 */
                i += CHN_SIZE;
            else {  /* 有效字符的情况 */
                PyList_Append(code_list, PyUnicode_FromString(tmp_char));
                i += size_add;
            }
        }

        else {

            /* 不是中文时，只截取数字 */
            if (48 <= source[i] && source[i] <= 57) {
                PyList_Append( code_list, PyLong_FromLong( (long)atoi(&source[i]) ) );
                while ( 48 <= source[i] && source[i] <= 57 ) i++;
            }

            else i++;
        }
    }

    return code_list;
}
