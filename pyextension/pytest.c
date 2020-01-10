
#include <Python.h>
#include <stdio.h>
#include <stddef.h>

static PyObject *
test_dict()
{
    int if_contain;
    size_t num;
    PyObject *city = PyDict_New();
    PyDict_SetItemString(city, "shanghai", PyUnicode_FromString("china"));
    if_contain = PyDict_Contains(city, PyUnicode_FromString("shanghai"));
    PyDict_Clear(city);
    if_contain = PyDict_Contains(city, PyUnicode_FromString("shanghai"));
    return NULL;
}

int main(int argc, char *argv[])
{
    Py_Initialize();
    PyRun_SimpleString("print('Hello Python!')\n");
    test_dict();
    Py_Finalize();
    return 0;
}
