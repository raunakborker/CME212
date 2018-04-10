#include <stdio.h>
#include <stdlib.h>

#include "pivcext.h"

double * XCorr(double *a, double *b, int n1, int n2)
{
  int i, j, k, l, k_begin, k_end, l_begin, l_end;
  int Rn2 = 2*n2-1;
  double acc;
  long unsigned int sizeR = (long unsigned int)((2*n1-1)*(2*n2-1));

  double *R = (double *)malloc(sizeR*sizeof(double));
  
  if (R == NULL)
    {
      return R;
    }
  
  for (i=-(n1-1); i<n1; i++)
    {
      for (j=-(n2-1); j<n2; j++)
	{
	  acc = 0.0;

	  if (i<=0)
	    {
	      k_begin = 0;
	      k_end = n1-1 + i;
	    }
	  else
	    {
	      k_begin = i - 0;
	      k_end = n1-1;
	    }
	  
	  if (j<=0)
	    {
	      l_begin = 0;
	      l_end = n2-1 + j;
	    }
	  else
	    {
	      l_begin = j - 0;
	      l_end = n2-1;
	    }

	  for (k=k_begin; k<=k_end; k++)
	    {
	      for (l=l_begin; l<=l_end; l++)
		{
		  acc = acc + (a[k*n2 + l]*b[(k-i)*n2 + (l-j)]);
		}
	    }

	  R[(i + (n1-1))*Rn2 + (j + (n2-1))] = acc;
	}
    }

  return R;
}
