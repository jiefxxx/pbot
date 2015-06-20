#include <Python.h>
#include "lib_test.h"

static PyObject* test_fct(PyObject* self, PyObject* args){
	const char *lib_name;
	if (!PyArg_ParseTuple(args, "s", &lib_name))
		return NULL;
	printf("%s\n",lib_name);
	return Py_BuildValue("i", 0);
}

PyMethodDef* get_methodDef(void){
	return test_methodes;
}
