#ifndef PYFUNC_H
#define PYFUNC_H

#include <Python.h>


#define print_obj(x) PyObject_Print(x, stdout, Py_PRINT_RAW); printf("\n");


#endif	/* PYFUNC_H */
