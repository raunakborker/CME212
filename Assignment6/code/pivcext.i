%module(docstring="Particle Image Velocimetry C Extension Module") pivcext

%header
%{
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <numpy/arrayobject.h>

#include "pivcext.h"
%}

%typemap(in,numinputs=0) int
%{
%}

%typemap(in) double *a
%{
    PyArrayObject *inputarraya = (PyArrayObject *)$input;
    arg1 = (double *)PyArray_DATA(inputarraya);
%}

%typemap(in) double *b
%{
    PyArrayObject *inputarrayb = (PyArrayObject *)$input;
    arg2 = (double *)PyArray_DATA(inputarrayb);
    arg3 = (int)PyArray_DIM(inputarrayb,0);
    arg4 = (int)PyArray_DIM(inputarrayb,1);
    if (PyArray_DIM(inputarraya,0)!=PyArray_DIM(inputarrayb,0) || PyArray_DIM(inputarraya,1)!=PyArray_DIM(inputarrayb,1))
    {
        PyErr_SetString(PyExc_TypeError,"Cannot cross correlate windows of different sizes.");
    	return NULL;
    }
%}

%typemap(out) double *
%{
  if ($1 == NULL)
  {
    return Py_None;
  }

  npy_intp dims[2] = {2*arg3-1, 2*arg4-1};
  PyObject *output = PyArray_SimpleNewFromData(2, dims, NPY_DOUBLE, (void *)$1);

  PyArray_ENABLEFLAGS((PyArrayObject *)output, NPY_ARRAY_OWNDATA);

  $result = output;
%}

%feature("autodoc", "XCorr(array data) -> cross correlation")
XCorr;

%include "pivcext.h"

%init
%{
    import_array();
%}

%pythoncode
%{
__version__ = "1.0.0"
%}