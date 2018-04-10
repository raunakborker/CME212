#include <array>
#include <cmath>
#include <iostream>

#include "shapes.hpp"

/* Method to return the color of the shape */
unsigned int Shape::GetColor(void)
{
  return this->color;
}

/* Method to set the color of the shape */
void Shape::SetColor(unsigned int color)
{
  this->color = color;
}

/* Constructor for sphere concrete class */
Sphere::Sphere(double x, double y, double z, double r)
{
  this->x = x;
  this->y = y;
  this->z = z;
  this->r = r;
}

/* Method to check if point is inside sphere */
bool Sphere::PointInside(const std::array<double,3> &point)
{
  double rpointSquare = norm2(point[0]-x,point[1]-y,point[2]-z);

  if (rpointSquare <= r)
    return true;
  else
    return false;
}

/* Method to return a cube which bounds the sphere.
   Parametrized by center coordinates and width */
std::array<double,4> Sphere::BoundingBox(void)
{
  std::array<double,4> box = {{x,y,z,2*r}};

  return box;
}

/* Constructor for right circular cone concrete class */
RightCircularCone::RightCircularCone(double r, double xb, double yb, double zb, \
                                     double xa, double ya, double za)
{
  this->r = r;

  /* -design Don't you think it would be more natural to store these variables as points?  E.g., std::array<double, 3> apex, std::array<double, 3> base_center */
  this->xa = xa;
  this->ya = ya;
  this->za = za;
  this->xb = xb;
  this->yb = yb;
  this->zb = zb;
  this->height = norm2(xa-xb,ya-yb,za-zb);
}

/* Method to check if point is inside the cone */
bool RightCircularCone::PointInside(const std::array<double,3> &point)
{
  double coneangle = atan2(r,height);
  
  /* -design A better alternative to using a hardcoded eps is to use std::numeric_limits<double>::epsilon */
  double eps = 1e-14;

  double distToApex = norm2(point[0]-xa,point[1]-ya,point[2]-za);
  double dotProd = (point[0]-xa)*(xb-xa) + (point[1]-ya)*(yb-ya) + (point[2]-za)*(zb-za);
  double angle = acos(dotProd/(distToApex*height + eps));
  double projHeight = distToApex*cos(angle);

  /* if vector from point to apex makes an angle with the cone axis 
     that is smaller than equal to the cone angle and has a axis projected 
     height less equal to the cone height then it is inside the cone */
  if (angle <= coneangle && projHeight <= height)
    return true;
  else
    return false;
}

/* Method to return a cube which bounds the cone.
   Parametrized by center coordinates and width */
std::array<double,4> RightCircularCone::BoundingBox(void)
{
  std::array<double,4> box;
  
  // Cube centered at cone axis midpoint
  double x = (xa + xb)/2;
  double y = (ya + yb)/2;
  double z = (za + zb)/2;
  double w;
  
  /* -3functionality Bounding box for shape is not large enough.  Consider a cone that is not axis aligned with, say, w == height == 2*r.  The distance from cone axis midpt (x,y,z) to a point on the base circumference would be sqrt(2)*r > w/2. */
  // Width is the highest dimension fo the cone
  if (height > 2*r)
    w = height;
  else
    w = 2*r;

  
  box[0] = x; box[1] = y; box[2] = z; box[3] = w;
  
  return box;
}

/* Helper function to compute the 2 norm of a vector (not C++ vector)*/
double norm2(double x1, double x2, double x3)
{
  return sqrt(x1*x1 + x2*x2 + x3*x3);
}
