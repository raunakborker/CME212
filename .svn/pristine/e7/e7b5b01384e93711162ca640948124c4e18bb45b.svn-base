#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstddef> 
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <new>
#include <stdexcept>
#include <string>
#include <set>
#include <utility>
#include <vector>

#include "audioio.h"
#include "mkl.h"
#include "identify.hpp"

#define samplefreq 44100

AudioIdentify::AudioIdentify(unsigned int windowsize,
			     unsigned int overlap,
			     unsigned int neighborhood_size, unsigned int fan_value,
			     float threshold)
{
  this->windowsize = windowsize;
  this->overlap = overlap;
  this->neighborhood_size = neighborhood_size;
  this->fan_value = fan_value;
  this->threshold = 100*threshold;
  
  if (windowsize % 2 != 0)
    throw std::runtime_error("ERROR: window size should be an even number");

  if (overlap >= windowsize)
    throw std::runtime_error("ERROR: overlap should be less than windowsize");

  if (neighborhood_size % 2 != 1)
    throw std::runtime_error("ERROR: neighborhood size should be an odd number");

}

void AudioIdentify::AddToDatabase(std::string filename)
{
  std::set<std::size_t> fingerprints;

  int status = Analyze(filename,fingerprints);
  if (status !=0)
      throw std::runtime_error("ERROR: Analysis Failed!");
  else
      database[filename] = fingerprints;
}

std::pair<std::string, double> AudioIdentify::FindMatches(std::string filename)
{
  std::set<std::size_t> fingerprints;

  int status = Analyze(filename,fingerprints);
  if (status !=0)
    throw std::runtime_error("ERROR: Analysis Failed!");
  
  std::pair<std::string, double> match ("",threshold);  
  for (auto &d : database)
    {
      std::set<std::size_t> common;

      std::set_intersection(fingerprints.begin(), fingerprints.end(), 
                            (d.second).begin(), (d.second).end(), 
			    std::inserter(common, common.begin()));      

      float percentage = (float) (common.size())/(fingerprints.size())*100;      
      if (percentage >= match.second)
	{
	  match.first = d.first;
	  match.second = percentage;
	}
    }

  return match;
}

int AudioIdentify::Analyze(std::string filename, std::set<std::size_t> &fingerprints)
{
  float *data = NULL;
  long nframes = 0;

  /* Extract Channel 1 */
  int status = ExtractChannel1(filename, &data, nframes);
  if (status != 0)
      return 1;

  /* Compute the Spectrogram */
  float *spectrogram = NULL;
  unsigned int ntime = std::floor((nframes-overlap)/(windowsize-overlap));
  unsigned int nfreq = (windowsize/2 + 1);
  status = Spectrogram(data, &spectrogram, nframes, ntime, nfreq);
  delete[] data; data = NULL;
  if (status != 0)
    return 1;
  
  /* Obtain Local Maxima */ ////////
  std::vector< std::pair <int,int> > maxima;
  status = LocalMaxima(spectrogram, ntime, nfreq, maxima);
  delete[] spectrogram; spectrogram = NULL;
  if (status != 0)
    return 1;
  
  /* Generate Fingerprints */
  fingerprints = GenerateFingerprints(maxima);
  
  return 0;
}

int AudioIdentify::ExtractChannel1(std::string filename, float **data, long &nframes)
{
  short *datachannels = NULL;
  int nchannels = 0;
  const char *filein = filename.c_str();

  int status = ReadWavFile(filein, &datachannels, &nframes, &nchannels);    
  if (status != 0)
    {
      std::cerr << "ERROR: Could not read wav file, status = " << status << std::endl;
      free(datachannels); datachannels = NULL;
      return 1;
    }
  else
    {
      *data = NULL;
      *data = new float [nframes];
      
      for (long n = 0; n < nframes; n++)
	{
	  (*data)[n] = (float)datachannels[n*nchannels];
	}
      free(datachannels); datachannels = NULL;
    }

  return 0;
}

int AudioIdentify::Spectrogram(float *data, float **spectrogram, long nframes, unsigned int ntime, unsigned int nfreq)
{
  /* Configure FFT */
  MKL_LONG status;
  DFTI_DESCRIPTOR_HANDLE handle;
  status = DftiCreateDescriptor(&handle, DFTI_SINGLE, DFTI_REAL, 1, windowsize);
  assert(status == 0);
  
  status = DftiSetValue(handle, DFTI_PLACEMENT, DFTI_NOT_INPLACE);
  assert(status == 0);

  status = DftiCommitDescriptor(handle);
  assert(status == 0);  

  float *fftoutput = new float [2*nfreq];
  
  *spectrogram = NULL;
  *spectrogram = new float [ntime*nfreq];  
  
  unsigned int startind = 0;
  for (unsigned int i=0; i<ntime; i++)
    {
      status = DftiComputeForward(handle, data + startind, fftoutput);

      if (status !=0)
	{
	  std::cerr << "ERROR: FFT failed at window number " << i << ", status = " << status << std::endl;
	  delete[] fftoutput; fftoutput = NULL;
	  return 1;
	}

      for (unsigned int j=0; j<nfreq; j++)
	{  
	  int fac = 2;
	  if (j==0 || j==(nfreq-1))	    
	    fac = 1;
	  
	  float k = (float)fac/(windowsize * samplefreq );
	  float fre = fftoutput[2*j];
	  float fim = fftoutput[2*j+1];
	  float P = 10*std::log10(k*(fre*fre + fim*fim));
	  
	  (*spectrogram)[i*nfreq + j] = P;
	}

      startind = (i+1)*(windowsize - overlap);
    }
  
  /* Cleanup */
  delete[] fftoutput; fftoutput = NULL;
  status = DftiFreeDescriptor(&handle);
  assert(status == 0);

  return 0;
}

int AudioIdentify::LocalMaxima(float *data, unsigned int ni, unsigned int nj, std::vector< std::pair<int,int> > &maxima)
{
  if (data == NULL)
    {
      std::cerr << "ERROR: data pointer is NULL" << std::endl;
      return 1;
    }

  int range = (neighborhood_size-1)/2;
  
  for (int i=0; i<ni; i++)
    {
      for (int j=0; j<nj; j++)
	{
	  bool flag_ismax = true;

	  float valij = data[i*nj + j];
	  if (valij < 10)
	      continue;

	  int range_negi = range; int range_posi = range;
	  int range_negj = range; int range_posj = range;
	  
	  if ( (i-range_negi) < 0 )
	    range_negi = i;
	  
	  if ( (i+range_posi) > (ni-1) )
	    range_posi = ni-1-i;
	  
	  if ( (j-range_negj) < 0 )
	    range_negj = j;

	  if ( (j+range_posj) > (nj-1) )
	    range_posj = nj-1-j;

	  for (int row=i-range_negi; row<=(i+range_posi); row++)
	    {
	      if (valij < *std::max_element(data + (row*nj + (j-range_negj)), data + (row*nj + (j+range_posj) + 1) ))
		{
		  flag_ismax = false;
		  break;
		}
	    }
	      
	  if (flag_ismax == true)
	      maxima.emplace_back(i,j);
	}
    }

  return 0;
}

std::set<std::size_t> AudioIdentify::GenerateFingerprints(std::vector< std::pair<int,int> > &maxima)
{
  std::set<std::size_t> fingerprints;
  std::hash<std::string> hash_fn;

  for (int i=0; i<maxima.size(); i++)
    {
      for (int j=i+1; j<=(i+fan_value) && j<(maxima.size()); j++)
	{
	  std::string str = std::to_string(maxima[i].second) + "|" 
            + std::to_string(maxima[j].second) + "|" 
            + std::to_string(maxima[j].first-maxima[i].first);

	  fingerprints.insert(hash_fn(str));
	}
    }

  return fingerprints;
}

