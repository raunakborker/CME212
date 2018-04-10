#ifndef ARRAY3_HPP
#define ARRAY3_HPP

#include <algorithm>
#include <cmath>
#include <numeric>
#include <ostream>

#include "macros.hpp"

#define DIM 3

template <typename T>
struct Array3{
  T arr[DIM];
  
  Array3(T x0=(T)0, T x1=(T)0, T x2=(T)0);
  T& operator[] (std::size_t n);
  Array3<T> operator=(const Array3<T> &v);
  Array3<T> operator+(const Array3<T> &v);
};

template <typename T>
Array3<T>::Array3(T x0, T x1, T x2)
{
  arr[0] = x0; arr[1] = x1; arr[2] = x2; 
}

template <typename T>
T& Array3<T>::operator[] (std::size_t n)
{
  return arr[n];
}

template <typename T>
Array3<T> Array3<T>::operator=(const Array3<T> &v)
{
  arr[0] = (v.arr)[0];
  arr[1] = (v.arr)[1];
  arr[2] = (v.arr)[2];

  return *this;
}

template <typename T>
Array3<T> Array3<T>::operator+(const Array3<T> &v)
{
  return Array3<T> (arr[0]+(v.arr)[0], arr[1]+(v.arr)[1], arr[2]+(v.arr)[2]);
}

template <typename T>
Array3<T> operator-(const Array3<T> &v1, const Array3<T> &v2)
{
  return Array3<T> ((v1.arr)[0]-(v2.arr)[0], (v1.arr)[1]-(v2.arr)[1], (v1.arr)[2]-(v2.arr)[2]);
}

template <typename T>
Array3<T> operator*(T scalar, const Array3<T> &v)
{
  return Array3<T> (scalar*(v.arr)[0], scalar*(v.arr)[1], scalar*(v.arr)[2]);
}

template <typename T>
std::ostream & operator<< (std::ostream &os, const Array3<T> &v) 
{
  for (unsigned int i=0; i<DIM; i++)
    {
      os << (v.arr)[i];
      if (i!= DIM - 1)
        os << " ";
    } 

  return os;
}

template <typename T>
T L2norm(const Array3<T> &v)
{
  return std::sqrt((v.arr)[0]*(v.arr)[0] + (v.arr)[1]*(v.arr)[1] +
  (v.arr)[2]*(v.arr)[2]);
}

#endif /* ARRAY3_HPP */
