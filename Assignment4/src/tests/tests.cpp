#include <cstddef>

#include <cppunit/TestCase.h>

/* -1functionality Missing includes: <cppunit/ui/text/TestRunner.h>, <cppunit/TestCaller.h>, <cppunit/extensions/HelperMacros.h> */

#include "utilities.hpp"

/* -1design No test suite, runner, etc. See Piazza post (@186) */

class TransposeTest: public CppUnit::TestCase
{
private:

  /* -style It would be better to initialize the pointer value with something at declaration time (use NULL if necessary) */
  double *mat1;
  double *mat2;

  /* -functionality Better to use a larger test case. */
  int size = 4;
  int ldim = size + 2;
  
  // Method to compare two matrices element-wise
  bool TestEquality(double *mat1, double *mat2, int size, int ldim)
  {
    for (int i=0; i<size; i++)
      {
	for (int j=0; j<size; j++)
	  {
	    int index = j + i*ldim;

	    if (mat1[index] != mat2[index])
	      return false;
	  }
      }
    return true;
  }

public:
  TransposeTest() : CppUnit::TestCase("Tranpose Test") {}

  void runTest()
  {
    mat1 = new double[size*ldim];
    InitMatrix(mat1, size, ldim);
                                                                                                
    mat2 = new double[size*ldim];
    InitMatrix(mat2, size, ldim);
    
    bool flag = false;

    /* -design Potential for a memory leak here.  Note that if either SimpleTranspose or OptimizedTranspose fail, mat1 and mat2 will never get deallocated. */
    if (!SimpleTranspose(mat1, size, ldim))
      {	
	if (!OptimizedTranspose(mat2, size, ldim, 2))
	  {
	    flag = TestEquality(mat1,mat2,size,ldim);

	    delete [] mat1; mat1 = NULL;
	    delete [] mat2; mat2 = NULL;    
	  }  
      }
    CPPUNIT_ASSERT(flag);
  }

};

int main() 
{
  TransposeTest t;
  t.runTest();

  return 0; 
}
