#ifndef utils_h
#define utils_h

#include <Python.h>

#define print_obj(x) PyObject_Print(x, stdout, Py_PRINT_RAW);

#endif	/* utils_h */
