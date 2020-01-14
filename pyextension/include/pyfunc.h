#ifndef PYFUNC_H
#define PYFUNC_H

#define PY_SSIZE_T_CLEAN
#include <Python.h>


#define print_obj(obj) PyObject_Print( ( (PyObject *)obj ), stdout, Py_PRINT_RAW ); printf("\n");

#define print_type_name(obj) printf("Python object type name: %s\n", ( (PyObject *)obj )->ob_type->tp_name);

#endif	/* PYFUNC_H */
