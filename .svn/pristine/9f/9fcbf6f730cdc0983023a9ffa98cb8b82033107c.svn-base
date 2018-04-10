#ifndef HELPERFUNCTIONS_HPP
#define HELPERFUNCTIONS_HPP

#include <algorithm>
#include <array>
#include <cmath>
#include <ostream>

#include "macros.hpp"

#define DIM 3

template <typename T>
T L2norm(const std::array<T,DIM> &v)
{
  T norm = std::inner_product(v.begin(),v.end(),v.begin(),(T)0);

  return std::sqrt(norm);
}

template <typename T>
std::array<T,DIM> operator-(const std::array<T,DIM> &v1, const std::array<T,DIM> &v2)
{
  if (v1.size() != v2.size())
  {
    ThrowException("Vectors of different lengths");
  }

  std::array<T,DIM> v3;
  std::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), std::minus<T>());

  return v3;
}

template <typename T>
std::array<T,DIM> operator+=(std::array<T,DIM> &v1, const std::array<T,DIM> &v2)
{
  if (v1.size() != v2.size())
  {
    ThrowException("Vectors of different lengths");
  }

  std::transform(v1.begin(), v1.end(), v2.begin(), v1.begin(), std::plus<T>());

  return v1;
}

template <typename T>
std::array<T,DIM> operator*(T scalar, const std::array<T,DIM> &v1)
{
  std::array<T,DIM> v2;

  for (unsigned int n = 0; n < v1.size(); n++)
  {
    v2[n] = scalar*v1[n];
  }

  return v2;
}

template <typename T>
std::array<T,DIM> operator+(const std::array<T,DIM> &v1, const std::array<T,DIM> &v2)
{
  if (v1.size() != v2.size())
  {
    ThrowException("Vectors of different lengths");
  }

  std::array<T,DIM> v3;

  std::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), std::plus<T>());

  return v3;
}

template <typename T>
std::ostream & operator<< (std::ostream &os, const std::array<T,DIM> &v) 
{
  for (unsigned int i=0; i<v.size(); i++)
    {
      os << v[i];
      if (i!=v.size()-1)
        os << " ";
    } 

  return os;
}

#endif /* HELPERFUNCTIONS_HPP */
