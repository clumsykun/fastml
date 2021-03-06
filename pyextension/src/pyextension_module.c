// #define NPY_NO_DEPRECATED_API NPY_1_8_API_VERSION

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <numpy/ndarraytypes.h>
#include <numpy/arrayobject.h>
#include "pyfunc.h"
#include "utils.h"


/** ====================================================================================================
 * function
 **/

static PyObject *
pyextension_test(PyObject *self, PyObject *args)
{
    /* 用来保存从 python 传入的参数 */
    PyObject *X_from_python = NULL;

    if (!PyArg_ParseTuple (args, "O", &X_from_python))
        return NULL;

    /**
     * 使用 Py_Array_FROM_OTF 将输入数据转化为 PyArrayObject。
     * OTF 的意思应该是 Object Type Flags（瞎猜的）。
     * 注意：Py_Array_FROM_OTF 宏会使用另一个宏 PyArray_FromAny。
     * 任何使用 PyArray_FromAny 宏的，都会增加对象的低层引用，
     * 因此要使用 Py_DECREF 来减少该对象的引用。
     **/
    PyArrayObject *X_numpy = (PyArrayObject *)PyArray_FROM_OTF(
        X_from_python,      /* 传入数据 */
        NPY_DOUBLE,         /* numpy 的数据类型 */
        NPY_ARRAY_IN_ARRAY  /* flag?? */
    );

    if (X_numpy == NULL) return NULL;

    /* 获取长度 */
    npy_intp X_len = PyArray_SIZE(X_numpy);

    /* 获取 numpy 数组数据 buffer 的指针 */
    double *X_np_data = (double *) PyArray_DATA (X_numpy);

    puts("\npython 端的数据 X");
    print_obj(X_from_python);

    puts("\nX 转化为 ndarray 后的数据");
    for (npy_intp i = 0; i < X_len; i++) {
        fprintf(stdout, "%5.3f\t", X_np_data[i]);
        fflush(stdout);
    }

    /* 分配一个数组的内存 */
    double *X_carray = malloc(X_len * sizeof (double));
    if (X_carray == NULL) goto fail;

    for (npy_intp i = 0; i < X_len; i++)
        X_carray[i] = (double) i * i;

    /* 为刚分配的数组建立一个 ndarray wrapper */
    int nd = 2;
    npy_intp dims[] = {2, 3};
    PyObject *out = PyArray_SimpleNewFromData(
        nd,          /* 维度数 */
        dims,        /* 各维长度 */
        NPY_DOUBLE,  /* 数据类型 */
        X_carray     /* 数组数据 */
    );

    double *X_ca_data = PyArray_DATA((PyArrayObject *)out);
    puts("\n新建数组中的数据");
    for (npy_intp i = 0; i < X_len; i++) {
        fprintf(stdout, "%5.3f\t", X_ca_data[i]);
        fflush(stdout);
    }
    printf("\n");

    /**
     * 计算
     **/

    /* 返回的数据 */
    PyObject *val = Py_BuildValue ("O", out);

    /**
     * 释放内存后，在 python 端 val 的 ndarray 变量可用，
     * 但数据已不可用
     **/

    free(X_carray);
    Py_DECREF (X_numpy);
    return val;

fail:  /* 错误 */
    Py_DECREF (X_numpy);
    return NULL;
}

static PyObject *
pyextension_s_is_pure_ascii(PyObject *self, PyObject *args)
{
    PyObject *s_text;
    if ( !PyArg_ParseTuple(args, "O!", &PyUnicode_Type, &s_text) )
        return NULL;

    switch ( s_is_pure_ascii( PyUnicode_AsUTF8(s_text) ) ) {

        case 0:
            return Py_False;

        case 1:
            return Py_True;

        default:
            PyErr_SetString(PyExc_ValueError, "字符串内容错误！");
            return NULL;
    }
}

static PyObject *
pyextension_s_extract_keyword(PyObject *self, PyObject *args)
{
    PyObject *s_text, *d_keywords;
    if ( !PyArg_ParseTuple(args,
                           "O!O!",
                           &PyUnicode_Type, &s_text,
                           &PyDict_Type, &d_keywords) )
        return NULL;

    return s_extract_keyword(s_text, d_keywords);
}

static PyObject *
pyextension_s_cal_tfidf(PyObject *self, PyObject *args)
{
    PyObject *s_text, *obj_keywords;
    if ( !PyArg_ParseTuple(args,
                           "O!O!",
                           &PyUnicode_Type, &s_text,
                           &PyDict_Type, &obj_keywords) )
        return NULL;

    return s_cal_tfidf(s_text, obj_keywords);
}

static PyObject *
pyextension_s_reverse(PyObject *self, PyObject *args)
{
    PyObject *s_text;
    if ( !PyArg_ParseTuple(args, "O!", &PyUnicode_Type, &s_text) )
        return NULL;

    return s_reverse(s_text);
}

/** ====================================================================================================
 * Module Define
 **/

static PyMethodDef
pyextension_methods[] = {
    {"test",                pyextension_test,                METH_VARARGS, "test func"},
    {"s_is_pure_ascii",   pyextension_s_is_pure_ascii,   METH_VARARGS, "param: s_text"},
    {"s_extract_keyword", pyextension_s_extract_keyword, METH_VARARGS, "param: s_text, d_keywords"},
    {"s_cal_tfidf",       pyextension_s_cal_tfidf,       METH_VARARGS, "param: s_text, d_keywords"},
    {"s_reverse",         pyextension_s_reverse,         METH_VARARGS, "param: s_text"},
    {NULL, NULL, 0, NULL},
};


static PyModuleDef
pyextension_module = { 
    PyModuleDef_HEAD_INIT,
    "pyextension",
    NULL,
    -1,
    pyextension_methods,
    NULL,
    NULL,
    NULL,
    NULL,
};


/* PyMODINIT_FUNC 最后定义 */

PyMODINIT_FUNC
PyInit_pyextension(void)
{
    PyObject *module;
    module = PyModule_Create(&pyextension_module);
    if (!module) {
        return NULL;  /* 防止错误 */
    }

    import_array();

    return module;
}
