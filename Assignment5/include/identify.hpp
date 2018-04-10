#ifndef AUDIOIDENTITY_HPP
#define AUDIOIDENTITY_HPP

#include <map>
#include <string>
#include <set>
#include <utility>
#include <vector>

class AudioIdentify
{
private:
  unsigned int windowsize, overlap, neighborhood_size, fan_value;
  float threshold;
  std::map< std::string, std::set<std::size_t> > database;
  
  int ExtractChannel1(std::string filename, float **data, long &nframes);
  int Spectrogram(float *data, float **spectrogram, long nframes, unsigned int ntime, unsigned int nfreq);
  int LocalMaxima(float *data, unsigned int ni, unsigned int nj, std::vector< std::pair<int,int> > &maxima);
  std::set<std::size_t> GenerateFingerprints(std::vector< std::pair<int,int> > &maxima);
  int Analyze(std::string filename, std::set<std::size_t> &fingerprints);
  
public:  
  AudioIdentify(unsigned int windowsize,
		unsigned int overlap,
		unsigned int neighborhood_size,
		unsigned int fan_value,
		float threshold);
  
  void AddToDatabase(std::string filename);
  
  std::pair<std::string, double> FindMatches(std::string filename);
};


#endif /* AUDIOIDENTITY_HPP */
