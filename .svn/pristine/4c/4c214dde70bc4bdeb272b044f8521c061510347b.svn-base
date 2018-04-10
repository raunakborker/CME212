#ifndef solveroperators_hpp
#define solveroperators_hpp

/* +style Nice job including the necessary libraries for this file.*/
#include <algorithm>
#include <cmath>
#include <vector>

#include "macros.hpp"

/* +design Good use of std library algorithms to make your operators efficient and concise */

/* Substraction of vectors a-b */
template <typename T>
std::vector<T> operator- (const std::vector<T> &a, 
			  const std::vector<T> &b)
{
  std::vector<T> sum(a);
  
  // Check if vectors are of the same size
  if (a.size()==b.size())
    {
      std::transform(sum.begin(), sum.end(), b.begin(), 
		     sum.begin(), std::minus<T>());
      return sum;
    }
  else
    {
      ThrowException("Vectors of different lengths");
    }
}

/* Addition of vectors a+b */
template <typename T>
std::vector<T> operator+ (const std::vector<T> &a, 
			  const std::vector<T> &b)
{
  std::vector<T> sum(a);

  // Check if vectors are of the same size
  if (a.size()==b.size())
    {
      std::transform(sum.begin(), sum.end(), b.begin(), 
		     sum.begin(), std::plus<T>());
      return sum;
    }
  else
    {
      ThrowException("Vectors of different lengths");
    }
}

/* Product of a scalar and vector a*b */
template <typename T>
std::vector<T> operator* (const T a, const std::vector<T> &b)
{
  std::vector<T> prod (b.size(),0.0);
  
  std::transform(b.begin(), b.end(), prod.begin(),
		 std::bind1st(std::multiplies<T>(),a));
  return prod;
}

/* Overloaded product of scalar and vector a*b */
template <typename T>
std::vector<T> operator* (const std::vector<T> &b, const T a)
{
  std::vector<T> prod (b.size(),0.0);
  
  std::transform(b.begin(), b.end(), prod.begin(),
		 std::bind1st(std::multiplies<T>(),a));
  return prod;
}

/* Dot product of 2 vectors */
template <typename T>
T InnerProduct(const std::vector<T> &a, 
	       const std::vector<T> &b)
{
  T val = 0.0;
  
  // Check if vectors are of the same size
  if (a.size()==b.size())
    {
      /* -design Look at std::inner_product for a one-line way to do this, or see solution */
      for (unsigned int i=0; i<a.size(); i++)
        val += a[i]*b[i];

      return val;
     }
  else
    {
      ThrowException("Vectors of different lengths")
    } 
}

/* Helper function to compute L2 norm of a vector */
template <typename T>
T L2norm(const std::vector<T> &x)
{
  /* -design Make sure you call the C++ version std::sqrt instead of the C version sqrt.  Then you wouldn't need an explicit cast. */
  T l2norm = (T)sqrt(InnerProduct(x,x));
  
  return l2norm;
}

#endif /* solveroperators_hpp */



