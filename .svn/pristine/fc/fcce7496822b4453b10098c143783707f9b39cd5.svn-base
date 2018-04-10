%module(docstring="Molecular Dynamics Simulation Module") moldyn

%include "exception.i"
%include "std_except.i"
%include "std_string.i"
%include "std_vector.i"

%exception{
	try{
		$action
	}
	catch (const std::runtime_error &e) {
	      SWIG_exception(SWIG_RuntimeError, e.what());
	}
}

%{
#define SWIG_FILE_WITH_INIT

#include "ParticleBox.hpp"
#include "swap.hpp"
%}

%include "ParticleBox.hpp"
%include "swap.hpp"

%template(ParticleBoxF) ParticleBox<float>;
%template(ParticleBoxD) ParticleBox<double>;
