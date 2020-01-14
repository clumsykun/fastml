#include "pyfunc.h"


PyObject * string_mapping(const char *source, PyObject *dict)
{

    PyObject *words, *obj;
    
    words = PyDict_Keys(dict);
    Py_ssize_t n_words = PyList_Size(words);
    // size_t size_souce = strlen(source);

    size_t i, size_word, max_size_word = 0;
    for (Py_ssize_t i = 0; i < n_words; i++) {
        obj = PyList_GetItem(words, i);
        if ( !PyUnicode_Check(obj) ) continue;

        size_word = PyUnicode_GetLength(obj);
        if (size_word > max_size_word)
            max_size_word = size_word;
    }

    /* 一个中文需要 3 个 char 字符 */
    char *tmp_char = malloc( (size_t)max_size_word * 3 * sizeof(char) );
    PyObject *code_list = PyList_New(0);

    i = 0;
    while (source[i] != '\0') {

        /* 是中文的情况 */
        if (source[i] < 0) {
            memset(tmp_char, 0, (size_t)max_size_word * 3 * sizeof(char) );
            memcpy(tmp_char, &source[i], 3*sizeof(char));

            /* 在这里将词语映射成代码 */

            PyList_Append(code_list, PyUnicode_FromString(tmp_char));
            i += 3;
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
