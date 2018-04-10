%module(docstring="Molecular Dynamics Simulation Module") moldyn

%include "std_vector.i"
%include "std_string.i"

%{
#define SWIG_FILE_WITH_INIT

#include "ParticleBox.hpp"
#include "swap.hpp"
%}

%include "ParticleBox.hpp"
%include "swap.hpp"

%template(ParticleBoxF) ParticleBox<float>;
%template(ParticleBoxD) ParticleBox<double>;
