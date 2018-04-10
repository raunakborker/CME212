#include <stdlib.h>
#include <stdio.h>
#include "pivcext.h"
#include "timer.h"

void main()
{
  int n1 = 64, n2 = 64;
  int i,j;
  double ti, tj;
  double *a = (double *)malloc(n1*n2*sizeof(double));
  double *b = (double *)malloc(n1*n2*sizeof(double));
  double *c = (double *)malloc((2*n1-1)*(2*n2-1)*sizeof(double));

  for (i=0; i<n1; i++)
    {
      for (j=0; j<n2; j++)
	{
	  a[i*n2 + j] = i*j;
	  b[i*n2 + j] = i+j;
	}
    }
  printf("XCorr\n");
  ti = timer();
  for (i=0; i<1; i++)
    {
      c = XCorrC(a,b,n1,n2);
    }
  tj = timer();
  printf("Elapsed time: %f sec\n",tj-ti);
  free(a); a = NULL;
  free(b); b = NULL;
  free(c); c = NULL;
}
