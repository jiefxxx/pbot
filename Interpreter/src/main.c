#include <Python.h>
#include <stdio.h>
#include <unistd.h>
#include <dlfcn.h>
#include <dbus/dbus.h>

#define LIB_PATH "./lib"

static PyObject* Pyload_library(PyObject* self, PyObject* args){
	const char *lib_name;
	if (!PyArg_ParseTuple(args, "s", &lib_name))
		return NULL;
	
        PyMethodDef* (*getMethodDef)(void);
        char* (*getName)(void);
        
        char *error;
        void *handle;
        
        handle = dlopen (lib_name, RTLD_LAZY);
        if (!handle) {
            fputs (dlerror(), stderr);
            exit(1);
        }

        getMethodDef = dlsym(handle, "get_methodDef");
        if ((error = dlerror()) != NULL)  {
            fputs(error, stderr);
            exit(1);
        }
        
        getName = dlsym(handle, "get_name");
        if ((error = dlerror()) != NULL)  {
            fputs(error, stderr);
            exit(1);
        }
        
        printf("load_lib:%s\n",lib_name);
        Py_InitModule("test", methodDef());
        
	return Py_BuildValue("i", 0);
}

static PyMethodDef Interpreter[] = {
	{"load_library", Pyload_library, METH_VARARGS, "..."},
	{NULL, NULL, 0, NULL}        /* Sentinel */
};

int main(int argc, char *argv[]){
	/* Pass argv[0] to the Python interpreter */
	Py_SetProgramName(argv[0]);

	/* Initialize the Python interpreter.  Required. */
	Py_Initialize();
	
	PyObject *sys = PyImport_ImportModule("sys");
	PyObject *path = PyObject_GetAttrString(sys, "path");
	PyList_Append(path, PyUnicode_FromString("."));
	PyList_Append(path, PyUnicode_FromString(LIB_PATH));
	
	Py_InitModule("_run_time", Interpreter);
	
	FILE *fp = fopen ("test.py", "r+");
	PyRun_SimpleFile (fp, "test.py");
	
	Py_Finalize();
    	return 0;

}
