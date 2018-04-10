#ifndef IMAGEIO_HPP
#define IMAGEIO_HPP

#include <string>

namespace ImageIO
{
  /* Function to read a TIFF image using the LibTIFF library*/
  void Read8bitGrayscaleTIFF(std::string filename, 
			     unsigned char * &data,
			     unsigned int &width, 
			     unsigned int &height);
  
  /* Function to write a TIFF image using LibTIFF library*/
  void Write8bitGrayscaleTIFF(std::string filename, 
			      unsigned char *data,
			      unsigned int width, 
			      unsigned int height);
}

#endif /* IMAGEIO_HPP */
