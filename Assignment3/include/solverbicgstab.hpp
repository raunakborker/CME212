#ifndef solverbicgstab_hpp
#define solverbicgstab_hpp

#include <algorithm>
#include <cfloat>
#include <limits>
#include <numeric>
#include <vector>

#include "macros.hpp"
#include "solveroperators.hpp"
#include "sparse.hpp"
#include "timer.h"


/* Template class for a BiConjugate Gradient STABilized (BiCGSTAB) solver */

template <typename T>
class BiCGSTABSolver
{
  private:
    int niter = -1;                             // actual number of iterations that were run
    T l2normr = std::numeric_limits<T>::max();  // l2 norm of the residual at end of iterations
    double elapsedtime = -1.;                   // elapsed solver time

  public:

    /* Method to run solver.  On entry the vector x may contain an initial guess,
       and on return will contain the solution.  Optional parameters can be specified
       to control the maximum number of iterations (defaults to the size of the
       linear system if nitermax == -1), whether to use the contents of x as the
       initial guess for the solution, and the relative threshold for determining whether
       the solution is converged. */

    bool Solve(const CSRMatrix<T> &A,
               const std::vector<T> &b,
               std::vector<T> &x,
               int nitermax = -1,
               bool use_initial_guess = false,
               double threshold = 1.e-4);

    /* Returns the actual number of iterations performed */

    int GetNumberIterations(void);

    /* Returns the l2 norm of the residual */
    
    double Getl2NormResidual(void);

    /* Get solver elapsed time */

    double GetElapsedTime(void);
};


template <typename T>
bool BiCGSTABSolver<T>::Solve(const CSRMatrix<T> &A,
                              const std::vector<T> &b,
                              std::vector<T> &x,
                              int nitermax,
                              bool use_initial_guess,
                              double threshold)
{
  double t_start = timer();
  
  int ncols = A.GetNumberCols();
  int nrows = A.GetNumberRows();

  /* -1functionality Should check that matrix A is square. */
  
  // Confirm input matrix and rhs have compatible sizes
  if ( ncols != (int)b.size())
      ThrowException("Matrix and RHS Vector of incompatible sizes");

  // Check initial guess is to be used, compatible
  if (use_initial_guess)
    {
      if ((int)x.size() != ncols)
        ThrowException("Initial guess of incompatible size with RHS and the Matrix");      
    }
  else
    {
      /* -design At least you didn't make the very common mistake of assuming x is empty.  However, it would be much easier to just set x=std::vector(ncols,0) or x.assign(ncols,0). */
      int npads = ncols - (int)x.size();
      x.resize(ncols,0);
      
      if (npads > 0)
        {
          for (int i=0; i<(ncols-npads); i++)
            x[i] = 0;
        }
      else
        {
          for (int i=0; i<ncols; i++)
            x[i] = 0;
        }
    }
  
  // Set the max number of iterations
  if (nitermax == -1)
    nitermax = nrows;

  // Initialize and define variables used in BiCGSTAB
  T rhoprev = 1; T alpha = 1; T omega = 1;
  T rhonext, beta;
  int n = 0;

  std::vector<T> r = b - A*x;
  T l2normr0 = L2norm(r);

  std::vector<T> rhat(r);
  /* -2functionality Need to confirm that (rhat,r) is not approximately 0 */

  std::vector<T> s, t;
  std::vector<T> v(r.size(),0.0);
  std::vector<T> p(r.size(),0.0);

  // BiCGSTAB Algorithm
  while (n < nitermax)
    {
      /* -style n++ is fine here, you don't have to match the pseudocode exactly. */
      n = n + 1;

      rhonext = InnerProduct(rhat,r);
      beta = (rhonext/rhoprev)*(alpha/omega);
      
      p = r + beta*(p - omega*v);

      v = A*p;
      
      alpha = rhonext/InnerProduct(rhat,v);

      s = r - alpha*v;

      t = A*s;
      
      omega = InnerProduct(t,s)/InnerProduct(t,t);

      /* -design Overloading operator+= and doing x += ... would have been fine too, no need to follow pseudocode exactly. */
      x = x + alpha*p + omega*s;
      r = s - omega*t;

      l2normr = L2norm(r);
      if (l2normr/l2normr0 < threshold)
        {
          niter = n;
          elapsedtime = timer() - t_start;

          return true;
        }

      rhoprev = rhonext;
    }

  /* -1functionality Set niter and elapsed time if the solution doesn’t converge. */
  return false;
}


template <typename T>
int BiCGSTABSolver<T>::GetNumberIterations(void)
{
  return niter;
}


template <typename T>
double BiCGSTABSolver<T>::Getl2NormResidual(void)
{
  return l2normr;
}


template <typename T>
double BiCGSTABSolver<T>::GetElapsedTime(void)
{
  return elapsedtime;
}

#endif /* solverbicgstab_hpp */
