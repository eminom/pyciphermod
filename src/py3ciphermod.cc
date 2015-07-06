

//~ What the hell is this
//#include "structmember.h"
#include "Python.h"
#include "py3ciphermod.h"
#include "cross.h"

#define CipherModFunc(a) _CipherModFunc__##a

//~
// extern PyTypeObject Py3_Fixed16Type;

static PyObject *CipherModFunc(CompilingDate)(PyObject *self)
{

    char buf[1024] = {0};
    if( sprintf_s(buf,sizeof(buf),"Compiled on %s:%s",__TIME__,__DATE__) < 0 )
    {
        Py_INCREF(Py_None);
        return Py_None;
    }
    return PyUnicode_FromString(buf);
}

static PyMethodDef __Methods__[] = 
{
    {"CompileDate",(PyCFunction)CipherModFunc(CompilingDate), METH_NOARGS,"Version of compiling datetime."},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

static struct PyModuleDef _cipher_v1mod = {
    PyModuleDef_HEAD_INIT,
    "cipherv1mod",
    NULL,
    -1,
    __Methods__
};

//The name shall comply with the setup module
//And this method is exported.
PyMODINIT_FUNC PyInit_CipherMod(void)
{
    if (PyObject *m = PyModule_Create(&_cipher_v1mod))
    {
        // Create a new type exception
        // RapperExc = PyErr_NewException("Rapv1.Excetpion",NULL,NULL);
        // Py_INCREF(RapperExc);
        // PyModule_AddObject(m,"RapError",RapperExc);  
            /*Appear as the module global name, checked by dir(r1lan)*/
        // Py_INCREF(&Py3_Fixed16Type);
        // PyModule_AddObject(m,"Fixed16",(PyObject*)&Py3_Fixed16Type);
        return m;
    }
    PyErr_SetString(PyExc_RuntimeError,"Init for CipherMod failed. God");
    return NULL;
}


