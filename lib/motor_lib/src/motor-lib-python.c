#include <motor_api/lib.h>
#include <Python.h>



static PyObject* set_motor_value_python(PyObject* self, PyObject* args){
	int ret,motor,val;
	PyObject* d;METH_NOARGS
	if (!PyArg_ParseTuple(args, "Oii", &d,&motor,&val))
		return NULL;
	struct ms_control* data;
	data = (struct ms_control*)PyLong_AsVoidPtr(d);
	ret=set_motor_value(data,motor,val);
	return Py_BuildValue("i", ret);
}
static PyObject* set_motor_rawValue_python(PyObject* self, PyObject* args){
	int ret,motor,val;
	PyObject* d;
	if (!PyArg_ParseTuple(args, "Oii", &d,&motor,&val))
		return NULL;
	struct ms_control* data;
	data = (struct ms_control*)PyLong_AsVoidPtr(d);
	ret=set_motor_rawValue(data,motor,val);
	return Py_BuildValue("i", ret);
}
static PyObject* set_motor_calMax_python(PyObject* self, PyObject* args){
	int ret,motor,val;
	PyObject* d;
	if (!PyArg_ParseTuple(args, "Oii", &d,&motor,&val))
		return NULL;
	struct ms_control* data;
	data = (struct ms_control*)PyLong_AsVoidPtr(d);
	ret=set_motor_calMax(data,motor,val);
	return Py_BuildValue("i", ret);
}
static PyObject* set_motor_calMin_python(PyObject* self, PyObject* args){
	int ret,motor,val;
	PyObject* d;
	if (!PyArg_ParseTuple(args, "Oii", &d,&motor,&val))
		return NULL;
	struct ms_control* data;
	data = (struct ms_control*)PyLong_AsVoidPtr(d);
	ret=set_motor_calMin(data,motor,val);
	return Py_BuildValue("i", ret);
}
static PyObject* get_motor_value_python(PyObject* self, PyObject* args){
	int ret,motor;
	PyObject* d;
	if (!PyArg_ParseTuple(args, "Oi", &d,&motor))
		return NULL;
	struct ms_control* data;
	data = (struct ms_control*)PyLong_AsVoidPtr(d);
	ret=get_motor_value(data,motor);
	return Py_BuildValue("i", ret);
}
static PyObject* get_motor_rawValue_python(PyObject* self, PyObject* args){
	int ret,motor,val;
	PyObject* d;
	if (!PyArg_ParseTuple(args, "Oi", &d,&motor))
		return NULL;
	struct ms_control* data;
	data = (struct ms_control*)PyLong_AsVoidPtr(d);
	ret=get_motor_rawValue(data,motor);
	return Py_BuildValue("i", ret);
}
static PyObject* get_motor_calMax_python(PyObject* self, PyObject* args){
	int ret,motor;
	PyObject* d;
	if (!PyArg_ParseTuple(args, "Oi", &d,&motor))
		return NULL;
	struct ms_control* data;
	data = (struct ms_control*)PyLong_AsVoidPtr(d);
	ret=get_motor_calMax(data,motor);
	return Py_BuildValue("i", ret);
}
static PyObject* get_motor_calMin_python(PyObject* self, PyObject* args){
	int ret,motor;
	PyObject* d;
	if (!PyArg_ParseTuple(args, "Oi", &d,&motor))
		return NULL;
	struct ms_control* data;
	data = (struct ms_control*)PyLong_AsVoidPtr(d);
	ret=get_motor_calMin(data,motor);
	return Py_BuildValue("i", ret);
}
static PyObject* dump_motor_python(PyObject* self, PyObject* args){
	int motor;
	PyObject* d;
	if (!PyArg_ParseTuple(args, "Oi", &d,&motor))
		return NULL;
	struct ms_control* data;
	data = (struct ms_control*)PyLong_AsVoidPtr(d);
	dump_motor(data,motor);
	return Py_BuildValue("i",0);
}
static PyObject* set_servo_value_python(PyObject* self, PyObject* args){
	int ret,servo,val;
	PyObject* d;
	if (!PyArg_ParseTuple(args, "Oii", &d,&servo,&val))
		return NULL;
	struct ms_control* data;
	data = (struct ms_control*)PyLong_AsVoidPtr(d);
	ret=set_servo_value(data,servo,val);
	return Py_BuildValue("i", ret);
}
static PyObject* set_servo_rawValue_python(PyObject* self, PyObject* args){
	int ret,servo,val;
	PyObject* d;
	if (!PyArg_ParseTuple(args, "Oii", &d,&servo,&val))
		return NULL;
	struct ms_control* data;
	data = (struct ms_control*)PyLong_AsVoidPtr(d);
	ret=set_servo_rawValue(data,servo,val);
	return Py_BuildValue("i", ret);
}
static PyObject* set_servo_calMax_python(PyObject* self, PyObject* args){
	int ret,servo,val;
	PyObject* d;
	if (!PyArg_ParseTuple(args, "Oii", &d,&servo,&val))
		return NULL;
	struct ms_control* data;
	data = (struct ms_control*)PyLong_AsVoidPtr(d);
	ret=set_servo_calMax(data,servo,val);
	return Py_BuildValue("i", ret);
}
static PyObject* set_servo_calMin_python(PyObject* self, PyObject* args){
	int ret,servo,val;
	PyObject* d;
	if (!PyArg_ParseTuple(args, "Oii", &d,&servo,&val))
		return NULL;
	struct ms_control* data;
	data = (struct ms_control*)PyLong_AsVoidPtr(d);
	ret=set_servo_calMin(data,servo,val);
	return Py_BuildValue("i", ret);
}
static PyObject* set_servo_degMax_python(PyObject* self, PyObject* args){
	int ret,servo,val;
	PyObject* d;
	if (!PyArg_ParseTuple(args, "Oii", &d,&servo,&val))
		return NULL;
	struct ms_control* data;
	data = (struct ms_control*)PyLong_AsVoidPtr(d);
	ret=set_servo_degMax(data,servo,val);
	return Py_BuildValue("i", ret);
}
static PyObject* set_servo_degMin_python(PyObject* self, PyObject* args){
	int ret,servo,val;
	PyObject* d;
	if (!PyArg_ParseTuple(args, "Oii", &d,&servo,&val))
		return NULL;
	struct ms_control* data;
	data = (struct ms_control*)PyLong_AsVoidPtr(d);
	ret=set_servo_degMin(data,servo,val);
	return Py_BuildValue("i", ret);
}
static PyObject* get_servo_value_python(PyObject* self, PyObject* args){
	int ret,servo,val;
	PyObject* d;
	if (!PyArg_ParseTuple(args, "Oi", &d,&servo))
		return NULL;
	struct ms_control* data;
	data = (struct ms_control*)PyLong_AsVoidPtr(d);
	ret=get_servo_value(data,servo);
	return Py_BuildValue("i", ret);
}
static PyObject* get_servo_rawValue_python(PyObject* self, PyObject* args){
	int ret,servo;
	PyObject* d;
	if (!PyArg_ParseTuple(args, "Oi", &d,&servo))
		return NULL;
	struct ms_control* data;
	data = (struct ms_control*)PyLong_AsVoidPtr(d);
	ret=get_servo_rawValue(data,servo);
	return Py_BuildValue("i", ret);
}
static PyObject* get_servo_calMax_python(PyObject* self, PyObject* args){
	int ret,servo;
	PyObject* d;
	if (!PyArg_ParseTuple(args, "Oi", &d,&servo))
		return NULL;
	struct ms_control* data;
	data = (struct ms_control*)PyLong_AsVoidPtr(d);
	ret=get_servo_calMax(data,servo);
	return Py_BuildValue("i", ret);
}
static PyObject* get_servo_calMin_python(PyObject* self, PyObject* args){
	int ret,servo;
	PyObject* d;
	if (!PyArg_ParseTuple(args, "Oi", &d,&servo))
		return NULL;
	struct ms_control* data;
	data = (struct ms_control*)PyLong_AsVoidPtr(d);
	ret=get_servo_calMin(data,servo);
	return Py_BuildValue("i", ret);
}
static PyObject* get_servo_degMax_python(PyObject* self, PyObject* args){
	int ret,servo;
	PyObject* d;
	if (!PyArg_ParseTuple(args, "Oi", &d,&servo))
		return NULL;
	struct ms_control* data;
	data = (struct ms_control*)PyLong_AsVoidPtr(d);
	ret=get_servo_degMax(data,servo);
	return Py_BuildValue("i", ret);
}
static PyObject* get_servo_degMin_python(PyObject* self, PyObject* args){
	int ret,servo;
	PyObject* d;
	if (!PyArg_ParseTuple(args, "Oi", &d,&servo))
		return NULL;
	struct ms_control* data;
	data = (struct ms_control*)PyLong_AsVoidPtr(d);
	ret=get_servo_degMin(data,servo);
	return Py_BuildValue("i", ret);
}
static PyObject* dump_servo_python(PyObject* self, PyObject* args){
	int servo;
	PyObject* d;
	if (!PyArg_ParseTuple(args, "Oi", &d,&servo))
		return NULL;
	struct ms_control* data;
	data = (struct ms_control*)PyLong_AsVoidPtr(d);
	dump_servo(data,servo);
	return Py_BuildValue("i",0);
}
static PyObject* get_controller_python(PyObject* self, PyObject* args){
	struct ms_control* data;
	data = get_controller();
	return Py_BuildValue("O", PyLong_FromVoidPtr(data));
}

static PyObject* send_action_python(PyObject* self, PyObject* args){
	int action;
	PyObject* d;
	if (!PyArg_ParseTuple(args, "Oi", &d,&action))
		return NULL;
	struct ms_control* data;
	data = (struct ms_control*)PyLong_AsVoidPtr(d);
	send_action(data,action);
	return Py_BuildValue("i",0);
}

/*  define functions in module */
static PyMethodDef MotorMethods[] =
{
	
	{"get_controller", get_controller_python, METH_NOARGS, "..."},
	
	{"send_action", send_action_python, METH_VARARGS, "..."},
	
	{"dump_motor", dump_motor_python, METH_VARARGS, "..."},
	{"set_motor_value", set_motor_value_python, METH_VARARGS, "..."},
	{"set_motor_rawValue", set_motor_rawValue_python, METH_VARARGS, "..."},
	{"set_motor_calMax", set_motor_calMax_python, METH_VARARGS, "..."},
	{"set_motor_calMin", set_motor_calMin_python, METH_VARARGS, "..."},
	{"get_motor_value", get_motor_value_python, METH_VARARGS, "..."},
	{"get_motor_rawValue", get_motor_rawValue_python, METH_VARARGS, "..."},
	{"get_motor_calMax", get_motor_calMax_python, METH_VARARGS, "..."},
	{"get_motor_calMin", get_motor_calMin_python, METH_VARARGS, "..."},
	
	{"dump_servo", dump_servo_python, METH_VARARGS, "..."},
	{"set_servo_value", set_servo_value_python, METH_VARARGS, "..."},
	{"set_servo_rawValue", set_servo_rawValue_python, METH_VARARGS, "..."},
	{"set_servo_calMax", set_servo_calMax_python, METH_VARARGS, "..."},
	{"set_servo_calMin", set_servo_calMin_python, METH_VARARGS, "..."},
	{"set_servo_degMax", set_servo_degMax_python, METH_VARARGS, "..."},
	{"set_servo_degMin", set_servo_degMin_python, METH_VARARGS, "..."},
	{"get_servo_value", get_servo_value_python, METH_VARARGS, "..."},
	{"get_servo_rawValue", get_servo_rawValue_python, METH_VARARGS, "..."},
	{"get_servo_calMax", get_servo_calMax_python, METH_VARARGS, "..."},
	{"get_servo_calMin", get_servo_calMin_python, METH_VARARGS, "..."},
	{"get_servo_degMax", get_servo_degMax_python, METH_VARARGS, "..."},
	{"get_servo_degMin", get_servo_degMin_python, METH_VARARGS, "..."},
	
	{NULL, NULL, 0, NULL}
};

PyMethodDef* get_methodDef(void){
	return MotorMethods;
}

/* module initialization 
PyMODINIT_FUNC initmotor_api(void){
	(void) Py_InitModule("motor_api", MotorMethods);
}*/
