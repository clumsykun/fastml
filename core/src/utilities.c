#include <Python.h>


PyObject *test_include(PyObject *in)
{
    PyDict_SetItemString(in, "shanghai", PyUnicode_FromString("China"));
    return in;
}
