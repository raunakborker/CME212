#include <exception>
#include <iostream>
#include <string>
#include <unistd.h>

#include "ParticleBox.hpp"
#include "timer.h"

#define PRECISION double

void printUsage(char *argv[])
{
  std::cout << "Usage:" << std::endl;
  std::cout << " " << argv[0] << " <nsteps> -i <input file> (optional) -o <outputfile> (optional)" << std::endl;
}

int main (int argc, char *argv[])
{
  
  if (argc < 2)
    {
      printUsage(argv);
      return 1;
    }

  // default input file
  std::string inputfile = "random";

  // default output file location
  std::string outputfile = "solution_default.vtk";
  
  try
    {
      if (std::stoi(argv[1]) < 0)
	{
	  std::cerr << "ERROR: number of steps specified as " << argv[1] << " cannot be negative!" << std::endl;
	  return 1;
	}
    }
  catch (std::exception &e)
    {
      std::cerr << "ERROR: invalid input argument for number of steps!" << std::endl;
      printUsage(argv);
      return 1;
    }
  unsigned int nsteps = (unsigned int)std::stoi(argv[1]);
  
  int c;
  opterr = 0;
  while ((c = getopt (argc, argv, "i:o:")) != -1)
    {   
      switch (c)
	{
	case 'i':
	  if (optarg && optarg[0] != '-')
	    {
	      inputfile = optarg;
	    }
	  else
	    {
	      std::cout << "WARNING: no input file provided, solution0.dat will be used" << std::endl;
	    }
	  break;
	case 'o':
	  if (optarg && optarg[0] != '-')
	    {
	      outputfile = optarg;
              std::cout << "Output will be saved to " << outputfile;
	    }
	  else
	    {
	      std::cout << "WARNING: no output file specified, output will be saved to solution_default.dat" << std::endl;
	    }
	  break;
	case '?':
	  char option = (char) optopt;
	  switch (option)
	    {
	    case 'i':
	      std::cout << "WARNING: no input file provided, solution0.dat will be used" << std::endl;
	      break;
	    case 'o':
	      std::cout << "WARNING: no output file specified, output will be saved to solution_default.dat" << std::endl;
	      break;
	    }
	  break;
	}
    }

  if (inputfile == "random")
    {
      unsigned int N = 64;
      //unsigned int N = 512;
      PRECISION L = (PRECISION) 4.2323167;
      //PRECISION L = (PRECISION) 8.4646344;
      PRECISION T0 = (PRECISION) 0.728;
      PRECISION M = (PRECISION) 48.0;
      PRECISION h = (PRECISION) 0.01;
      
      ParticleBox<PRECISION> PB(N,L,T0,M,h);
      double t_start = timer();
      auto step = PB.Solve(nsteps);
      double t_stop = timer();
      PB.SaveOutput(outputfile);
      std::cout << "Elapsed time: " << t_stop-t_start << "sec, total steps: " << step << std::endl;
    }
  else
    {
      ParticleBox<PRECISION> PB(inputfile);
      double t_start = timer();
      auto step = PB.Solve(nsteps);
      double t_stop = timer();
      PB.SaveOutput(outputfile);
      std::cout << "Elapsed time: " << t_stop-t_start << "sec, total steps: " << step << std::endl;
    }  
  
  return 0;
}

