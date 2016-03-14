

#include "Python.h"
#include "py3xxhashmod.h"
#include "../cross.h"
#include "xxhash.h"

#define XxhashModFunc(a) _XxhashModFunc__##a

static PyObject *XxhashModFunc(CompilingDate)(PyObject*) {
    char buf[1024] = {0};
    if( sprintf_s(buf,sizeof(buf),"Compiled on %s:%s",__TIME__,__DATE__) < 0 ) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    return PyUnicode_FromString(buf);
}

static PyObject* XxhashModFunc(DoXxhash)(PyObject *self, PyObject *args) {
    PyObject* buffer_in = NULL;
    unsigned int key = 0;
    if (!PyArg_ParseTuple(args, "OI", &buffer_in, &key)) {
        PyErr_SetString(PyExc_TypeError, "Need a bytes object(buffer) and a key(string)");
        return NULL;
    }
    if(!PyBytes_Check(buffer_in)) {
        PyErr_SetString(PyExc_TypeError, "bytes only(as the first parameter)");
        return NULL;
    }
    int lsize = PyBytes_Size(buffer_in);//TODO:Loss
    const char *origin_buffer = PyBytes_AsString(buffer_in);

    void* handle = XXH32_init(key);
    XXH32_update(handle, origin_buffer, lsize);
    unsigned int hex = XXH32_digest(handle);

    char outStr[BUFSIZ] = "";
    snprintf(outStr, sizeof(outStr), "%08x", hex);
    return PyUnicode_FromString(outStr);
}

static PyMethodDef __Methods__[] = {
    {"Date",    (PyCFunction)XxhashModFunc(CompilingDate), METH_NOARGS,"Version of compiling datetime."},
    {"xxhash",  (PyCFunction)XxhashModFunc(DoXxhash), METH_VARARGS, "Calculate the xxhash result for the bytes"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef _xxhash_v1mod = {
    PyModuleDef_HEAD_INIT,
    "pyxxhashv1mod",
    NULL,
    -1,
    __Methods__
};

PyMODINIT_FUNC PyInit_PyXxhashMod(void) {
    if (PyObject *m = PyModule_Create(&_xxhash_v1mod)) {
        return m;
    }
    PyErr_SetString(PyExc_RuntimeError,"Init for PyXxhashMod failed. God");
    return NULL;
}