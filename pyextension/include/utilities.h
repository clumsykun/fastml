#ifndef utilities_h
#define utilities_h

#include <Python.h>

#define print_obj(x) PyObject_Print((PyObject *)x, stdout, Py_PRINT_RAW); printf("\n")

PyObject *test_include(PyObject *in);

#endif	/* utilities_h */
