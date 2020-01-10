#ifndef PYFUNC_H
#define PYFUNC_H

#include <Python.h>


#define print_obj(x) PyObject_Print(x, stdout, Py_PRINT_RAW);

PyObject *string_findall(char *source, char *target);


#endif	/* PYFUNC_H */
