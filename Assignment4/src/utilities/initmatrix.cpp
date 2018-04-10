#include <cstddef>
#include <iostream>

#include "utilities.hpp"

// Initializes a matrix "a"
int InitMatrix(double *a, int size, int ldim)
{
  /* +design Good validation of inputs */
  if (a == NULL || ldim < size)
    {
      std::cerr << "a is NULL or ldim < size" << std::endl;
      return 1;
    }
  
  for (int i=0; i<size; i++) 
    {
      for (int j=0; j<size; j++)
        {
          int indij = i*ldim + j;
          a[indij] = (double)indij*3.14;
        }
        /* -1design Would be better to initialize the padding values */
    }

  return 0;
}
