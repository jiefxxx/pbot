#ifndef CTEST_H
#define CTEST_H

static PyObject* test_fct(PyObject* self, PyObject* args);

PyMethodDef* get_methodDef();

static PyMethodDef test_methodes[] = {
	{"print_test", test_fct, METH_VARARGS, "..."},
	{NULL, NULL, 0, NULL}        /* Sentinel */
};

#endif
