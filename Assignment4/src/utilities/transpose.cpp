#include <cstddef>

#include "utilities.hpp"

// Performs inplace matrix tranpose
int SimpleTranspose(double *a, int size, int ldim)
{
  if (a == NULL || ldim < size)
    {
      return 1;
    }

  // Loop over elements below the diagonal
  // starts from i=1 since i=0,j=0 is on the diagonal
  for (int i=1; i<size; i++)
    {
      for (int j=0; j<i; j++)
        {
          /* -design Better to do this computation inline instead of creating a separate function for it.  Function calls have a small overhead and creating a separate function for just one line of code is probably overkill here. */
          int indij = GlobalIndex(i, j, ldim);
          int indji = GlobalIndex(j, i, ldim);
          /* -design std::swap will do this in one line */
          double aij = a[indij];
          a[indij] = a[indji];
          a[indji] = aij;
        }
    }

  return 0;
}

// Performs inplace matrix tranpose using blocks
int OptimizedTranspose(double *a, int size, int ldim, int blocksize)
{
  if (a == NULL || ldim < size)
    {
      return 1;
    }

  if (size % blocksize != 0)
    {
      return 2;
    }
  
  int nblock = size/blocksize;
  
  // Loop over blocks below the diagonal
  /* -design It is easier and cleaner to loop through the rows/columns directly, e.g., by i+=blocksize, j+=blocksize.   The indexing math is more straightforward. */

  for (int ni=0; ni<nblock; ni++)
    {
      for (int nj=0; nj<ni; nj++)
	{
	  int row_lowerblock = ni*blocksize;
	  int col_lowerblock = nj*blocksize;

	  int ind_lowerblock = GlobalIndex(row_lowerblock, col_lowerblock,ldim);
	  int ind_upperblock = GlobalIndex(col_lowerblock, row_lowerblock,ldim);

	  SimpleTranspose(a + ind_lowerblock, blocksize, ldim);
	  SimpleTranspose(a + ind_upperblock, blocksize, ldim);

	  Swap(a + ind_lowerblock, a + ind_upperblock, blocksize, ldim);	
	}

      /* -design If you move the diagonal block computation/transpose above the inner for-loop, you can calculate row=ni*blocksize once and you won't need the row_lowerblock variable. */
      // Diagonal block
      int row = ni*blocksize;
      int col = ni*blocksize;
      int ind = GlobalIndex(row, col, ldim);

      SimpleTranspose(a + ind, blocksize, ldim);
    }

  return 0;
}

// Helper function converts 2D index (rowid,colid) to 1D
int GlobalIndex(int rowid, int colid, int ldim)
{
  return colid + rowid*ldim;
}

// Swaps elements of matrices a and b
/* -design Careful using the name "Swap" for a function, since "swap" is already used by the std library. */
void Swap(double *a, double *b, int size, int ldim)
{
  // Loop over matrix elements
  for (int i=0; i<size; i++)
    {
      for (int j=0; j<size; j++)
	{
	  int indij = GlobalIndex(i, j, ldim);
	  double aij = a[indij];
	  a[indij] = b[indij];
	  b[indij] = aij;
	}
    }
}
