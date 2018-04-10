#ifndef PART_HPP
#define PART_HPP

#include <array>
#include <map>
#include <memory>

#include "shapes.hpp"

class Part
{
private:
  /* -1design A vector would have been a better choice here, especially since your key simply corresponds to a shape number */
  std::map<int,std::shared_ptr<Shape>> shapes;

  /* -design No need to store a nshapes variable explicitly if you used a vector, e.g., shapes.size() */
  int nshapes = 0;
  unsigned long ncolor = 0;

  /* Method to iterate over the grid on the slicing plane to 
     compute the volume in terms of number of subvolumes inside
     the part */  
  void GridIterator(std::map<unsigned int,double> &vol,
                    std::array<double,3> &X,
                    double x0max, double x1max,
                    double dx0, double dx1,
                    const std::array<unsigned long,2> &i);

public:
  /* Method to read in a part file */
  void ReadPartFile(std::string partfile);

  /* Method to compute the volume/area of the part cut by a plane */
  std::map<unsigned int,double> SliceVolume(const std::array<double,3> &unitnormal,
                                            const std::array<double,3> &point,
                                            const std::array<double,3> &discretization);

  /* Method to give number of shapes */
  int GetnShapes(void);
  
  /* Method to give number of colors */
  unsigned long GetnColor(void);
};
#endif /* PART_HPP */
