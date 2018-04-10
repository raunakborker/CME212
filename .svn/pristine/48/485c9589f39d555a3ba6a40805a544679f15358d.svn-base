#include <iostream>
#include <new>

#include "config.h"

#include "timer.h"
#include "utilities.hpp"

#define PAD 8

int main()
{
  int size = 4096;
  int ldim = size + PAD;

  // Initialize matrix of size 4096 X 4096
  double *mat = new double [ldim*size];
  if (InitMatrix(mat, size, ldim))
    {
      std::cerr<< "Matrix initialization failed!" << std::endl;
      delete [] mat; mat = NULL;
      return 1;
    }

  std::cout << "Running OptimizedTranspose():" << std::endl;
  double t_start = timer();
  int out = OptimizedTranspose(mat, size, ldim, 128);
  double t_end = timer();
  
  delete [] mat; 
  mat = NULL;
  
  if (out != 0)
    {
      std::cerr << "Matrix transpose not succesful!" << std::endl;
      return out;
    }  

  double bandwidth = 2*size*size*(double)sizeof(double)/1.e9/(t_end-t_start);
  std::cout << "Effective bandwidth = " << bandwidth << " GB/sec" << std::endl;

  return 0;
}
