#ifndef pivcext_h
#define pivcext_h

#ifdef SWIG
%import "pivcext.i"
#endif /* SWIG */

 /* Function to compute cross correlation between matrices a and b */
double * XCorr(double *a, double *b, int n1, int n2);

#endif /* pivcext_h */
