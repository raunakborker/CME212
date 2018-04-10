#ifndef IMAGE_HPP
#define IMAGE_HPP

/* -1style Unneeded include file(s), <limits> */
#include <algorithm>
#include <limits>
#include <string>

#include "imageio.hpp"
#include "tiffio.h"

/* functor class */
template <typename T>
class IsGreaterThan
{
  T limit;
  public:
  IsGreaterThan(T limitin) 
  { 
    limit = limitin; 
  }
  
  // Special method so object can be called as a function
  bool operator()(T value) 
  { 
    return (value>=limit); 
  }
};

namespace ImageAnalysis
{
  template <typename T>
  class Image
  {
  private:
    unsigned int width, height;
/* -0style It would be better to initialize the pointer value with something at declaration time (e.g., NULL or nullptr) */    
    T *imagedata;
    T minval, maxval;
    float normalize;

/* -3design Put your method implementations outside the class declaration */
    /* Method to set min,max and normalization values.
       Has been specialized for floats */
    void setMinMax(T &minval,T &maxval, float &normalize)
    {
      minval = (T)0;
      maxval = (T)255;
      normalize = 1.0f;
    }    

  public:
    /* Constructor initializes image data by reading TIFF file */
    Image(std::string filename)
    {
      unsigned char *dataint = NULL;
      ImageIO::Read8bitGrayscaleTIFF(filename,dataint,this->width,this->height);

      this->imagedata = new T[this->width*this->height];

      /* Set min, max pixel values used for saving and threshold.
	 Normlization factor is also set */
      setMinMax(this->minval,this->maxval,this->normalize);

      /* -2design Although it's impressive you managed to avoid using a specialized template constructor, this loop is redundant in the case of an unsigned char */
      // Convert data from unsigned int 8bit to T
      for(unsigned int n = 0; n < this->width*this->height; n++)
	{
	  this->imagedata[n] = (T)(dataint[n]/this->normalize);
	}
      
      delete[] dataint;
      dataint = NULL;
    }
    
    /* Overloaded Constructor initializes image data using provided data
       in the memory region */       
    Image(T *data, unsigned int width, unsigned int height)
    {
      this->width = width;
      this->height = height;

      // Allocate memory for image data
      this->imagedata = new T[width*height];

      // Copy data from source to class
/* -1design Instead of a loop, use std::copy() to copy memory */
      for(unsigned int n = 0; n < width*height; n++)
	  this->imagedata[n] = data[n];      

      /* Set min, max pixel values used for saving and threshold.
	 Normlization factor is also set */
      setMinMax(this->minval,this->maxval,this->normalize);
    }
    
    /* Method to save current image data as TIFF */
    void Save(std::string filename)
    {
      unsigned char *dataint = NULL;

      dataint = new unsigned char[this->width*this->height];
      
/* -0design Again, this loop is unneeded in the case of an unsigned char. Better to use template specialization */
      // Convert data from float to unsigned int 8bit
      for(unsigned int n = 0; n < this->width*this->height; n++)
	{
	  float pix = this->imagedata[n]*this->normalize;	  
	  dataint[n] = (unsigned char)(pix);
	}
      
      ImageIO::Write8bitGrayscaleTIFF(filename,dataint,this->width,this->height);
      
      delete[] dataint;
      dataint = NULL;
    }  

    /* Image processing operation: Threshold */
    void Threshold(T threshold)
    {
      // Loop over pixels to perform "Threshold" operation
      /* -0style Can do this with a std algorithm for_each or transform */ 
      for(unsigned int n = 0; n < this->width*this->height; n++)
	{
	  T pix = this->imagedata[n];
	  if (pix < threshold)
	    this->imagedata[n] = this->minval;
	  else
	    this->imagedata[n] = this->maxval;
	}
    }

    /* Image processing operation: Count number of pixels with 
       value greater than a threshold */
    unsigned long int CountPixelsGreaterThanOrEqual(T value = (T)0)
    {
      unsigned int n = this->width*this->height;

      // Use count_if function from algorithm to perform count
      unsigned long int count =
	std::count_if(this->imagedata,this->imagedata+n,IsGreaterThan<T>(value));
      
      return count;
    }

    /* Destructor */
    ~Image()
    {
      delete[] this->imagedata;
      this->imagedata = NULL;
    }
  };
  
  /* Template specialization for float*/
  template<>
  void Image<float>::setMinMax(float &minval,float &maxval, float &normalize)
  {
    minval = 0.0f;
    maxval = 1.0f;
    normalize = 255.0f;
  }    
}

#endif /* IMAGE_HPP */
