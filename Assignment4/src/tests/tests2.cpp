#include <cstddef>
#include <iostream>

#include <cppunit/TestCase.h>

#include "../../include/utilities.hpp"

class TransposeTest: public CppUnit::TestCase
{
  /*  CPPUNIT_TEST_SUITE( TransposeTest );
  CPPUNIT_TEST( TestTranpose );
  CPPUNIT_TEST_SUITE_END();*/

private:
  double *mat1;
  double *mat2;
  int size = 200;
  int ldim = size + 20;
  
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

  /*  void setUp() 
  {
    mat1 = new double[size*ldim];
    InitMatrix(mat1,size,ldim);
    
    mat2 = new double[size*ldim];
    InitMatrix(mat2,size,ldim);
  } */

  /*  void tearDown()
  {
    delete [] mat1; mat1 = NULL;
    delete [] mat2; mat2 = NULL;
    }*/
    
  void runTest()
  {
    if (!SimpleTranspose(mat1,size,ldim))
      {
	if (!OptimizedTranspose(mat2,size,ldim))
	  {
	    auto flag = TestEquality(mat1,mat2,size,ldim);
	    CPPUNIT_ASSERT(flag);
	  }	  
      }
    delete [] mat1; mat1 = NULL;
    delete [] mat2; mat2 = NULL;    
  }

};

int main() 
{
  TransposeTest t;
  t.runTest();
  return 0; 
}
