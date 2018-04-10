from distutils.core import setup, Extension
import numpy

sources = ['pivcext.i','pivcext.c']
include_dirs = [numpy.get_include()]

_pivcext = Extension('_pivcext',
                     sources=sources,
                     include_dirs=include_dirs,
                     extra_compile_args=["-O3"])

setup(name='pivcext',
      ext_modules=[_pivcext])
