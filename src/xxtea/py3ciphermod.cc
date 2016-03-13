

//~ What the hell is this
//#include "structmember.h"
#include "Python.h"
#include "py3ciphermod.h"
#include "cross.h"
#include "xxtea.h"

#define CipherModFunc(a) _CipherModFunc__##a

static PyObject *CipherModFunc(CompilingDate)(PyObject*)
{
    char buf[1024] = {0};
    if( sprintf_s(buf,sizeof(buf),"Compiled on %s:%s",__TIME__,__DATE__) < 0 )
    {
        Py_INCREF(Py_None);
        return Py_None;
    }
    return PyUnicode_FromString(buf);
}

typedef unsigned char *CipherFuncPtr(unsigned char *data, xxtea_long data_len, unsigned char *key, xxtea_long key_len, xxtea_long *ret_length);

static PyObject* __CipherBodyHandler(PyObject* args, CipherFuncPtr func)
{
    PyObject* buffer_in = NULL;
    const char *key = NULL;
    if(!PyArg_ParseTuple(args, "Os", &buffer_in, &key))
    {
        PyErr_SetString(PyExc_TypeError, "Need a bytes object(buffer) and a key(string)");
        return NULL;
    }
    if( ! PyBytes_Check(buffer_in) )
    {
        PyErr_SetString(PyExc_TypeError, "bytes only(as the first parameter)");
        return NULL;
    }
    //printf("Key is %s\n", key);
    char *dup_key = strdup(key);
    int size = PyBytes_Size(buffer_in);  //Possible loss. (but who cares)
    //printf("Buffer size is %d\n", size);
    const char *origin_buffer = PyBytes_AsString(buffer_in);
    unsigned char *input_buffer = (unsigned char*)malloc(size*sizeof(unsigned char));
    memcpy(input_buffer, origin_buffer, size*sizeof(char));
    xxtea_long out_length = 0;
    unsigned char *encrypted_buffer = func(input_buffer, size*sizeof(char), (unsigned char*)dup_key, strlen(dup_key), &out_length);
    //printf("Out length is %lu\n", out_length);
    PyObject *buffer_out = PyBytes_FromStringAndSize((char*)encrypted_buffer, out_length);
    free(input_buffer);
    free(encrypted_buffer);
    free(dup_key);
    return buffer_out;
}

static PyObject* CipherModFunc(Encrypt)(PyObject *self, PyObject *args){return __CipherBodyHandler(args, xxtea_encrypt);}
static PyObject* CipherModFunc(Decrypt)(PyObject*, PyObject *args){return __CipherBodyHandler(args, xxtea_decrypt);}

static PyMethodDef __Methods__[] = 
{
    {"CompileDate",(PyCFunction)CipherModFunc(CompilingDate), METH_NOARGS,"Version of compiling datetime."},
    {"encrypt",    (PyCFunction)CipherModFunc(Encrypt), METH_VARARGS, "Shove it to encrypted."},
    {"decrypt",    (PyCFunction)CipherModFunc(Decrypt), METH_VARARGS, "Shove it out to decrypted."},
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
        return m;
    }
    PyErr_SetString(PyExc_RuntimeError,"Init for CipherMod failed. God");
    return NULL;
}