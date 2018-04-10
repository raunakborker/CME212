#ifndef PARTICLEBOX_HPP
#define PARTICLEBOX_HPP

#include <array>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "auxfuncs.hpp"
#include "macros.hpp"
#include "Particle.hpp"
#include "swap.hpp"

#ifndef DIM
#define DIM 3
#endif

#define PREC 16

/* Class that has a N particles in a box */
template <typename T>
class ParticleBox
{
private:
  std::vector<Particle<T> > particles;
  T h, L, T0, Lby2, Linv, currentTime;
  unsigned int N;
  int currentStep;

#ifndef SWIG
  /* Compute distance square */
  T DistanceSq(const std::array<T,DIM> &posi, 
	     const std::array<T,DIM> &posj);

  T Potential(T r);
  
  /* Method to advance inputted number of steps in time */
  void Advance_nSteps(unsigned int steps);
  
  void ComputeEnergy(std::array<T,DIM> &energy);
  void Displacement(const std::array<T,DIM> &posi, 
		    const std::array<T,DIM> &posj, 
		    std::array<T,DIM> &d);
  void GetForce(const std::array<T,DIM> &posi, 
		const std::array<T,DIM> &posj, 
		std::array<T,DIM> &F);

  /* Method to initialize class from a checkpoint file */
  void InitCheckpoint(std::string filename);

  void InitPosition(T M);
  void InitVelocity(T M);
  void InternalForce(std::vector< std::array<T,DIM> > &Fvec);
  void PutInBox(std::array<T,DIM> &posi);

  /* Methods to set position and velocity for all particles */
  void SetPos(const std::vector<std::array<T,DIM> > &pos);
  void SetVel(const std::vector<std::array<T,DIM> > &vel);

  void WriteData(std::string outputfile);

  std::array<T,DIM> VerletNextR(unsigned int ind);
  std::array<T,DIM> VerletNextV(unsigned int ind, const std::array<T,DIM> &nacc);
  
  /* Returns the datatype referred to be typename T */
  std::string GetDtype();
  
  /* Outputs energy as a vector instead of array */
  std::vector<T> ConvertEnergytoVector();
#endif

public:
  /* Constructor for simulation performed with a random initialization */
  ParticleBox(unsigned int N, T L, T T0, T M = (T)1.0, T h = (T)0.01);

  /* Overloaded constructor to start from a checkpoint file */
  ParticleBox(std::string checkpointfile);

  /* Method to Output the current energy state */
  std::vector<T> OutputEnergy();

  /* Method to perform inputted solve steps */
  int Solve(unsigned int steps=25);

  /* Method to write data to disk */
  void SaveOutput(std::string outputfile);
};

template <typename T>
ParticleBox<T>::ParticleBox(unsigned int N, T L, T T0, T M, T h)
{
  this->N = N;
  this->L = L;
  this->Lby2 = L*(T)0.5;
  this->Linv = (T)1.0/L;
  this->T0 = T0;
  this->h = h;
  this->currentStep = 0;
  this->currentTime = (T)0;

  particles = std::vector< Particle<T> > (N,Particle<T>());

  InitPosition(M);
  InitVelocity(M);
}

template <typename T>
ParticleBox<T>::ParticleBox(std::string checkpointfile)
{
  InitCheckpoint(checkpointfile);
}

template <typename T>
int ParticleBox<T>::Solve(unsigned int steps)
{
  Advance_nSteps(steps);  
  return this->currentStep;
}


template <typename T>
void ParticleBox<T>::SaveOutput(std::string outputfile)
{
  WriteData(outputfile);
}

template <>
std::string ParticleBox<double>::GetDtype()
{
  return "double";
}

template <>
std::string ParticleBox<float>::GetDtype()
{
  return "float";
}

template <typename T>
void ParticleBox<T>::InitCheckpoint(std::string filename)
{
  
  std::string Dtype = GetDtype();

  std::ifstream f (filename.c_str(), std::ios::binary);
  if (not f.is_open())
    { 
      ThrowException("ERROR: Failed to open the file " + filename + " !");
    }
  
  T M;
  
  std::string line, attr, n1, n2, datatype;
  std::stringstream ss;

  /* Read Header */
  for (int i=0; i<6; i++)
    {
      std::getline(f, line);
    }
  ss << line;
  ss >> attr >> n1 >> n2 >> datatype;
  ss.str(std::string());
  ss.clear();

  if (datatype != Dtype)
    {
      ThrowException("ERROR: Data type in " + filename + " is " + datatype 
		     + " whereas simulation is setup for " + Dtype + "!");
    }

  /* Read Time */
  char bufT[sizeof(T)];
  f.read(bufT, sizeof(T));
  unswap(bufT, &this->currentTime);

  /* Read Cycle */
  std::getline(f, line);
  char bufI[sizeof(int)];
  f.read(bufI, sizeof(int));
  unswap(bufI, &this->currentStep);

  /* Read Box Width */
  std::getline(f, line);
  f.read(bufT, sizeof(T));
  unswap(bufT, &this->L);
  this->Lby2 = L*(T)0.5;
  this->Linv = (T)1.0/L;

  /* Read Temperature */
  std::getline(f, line);
  f.read(bufT, sizeof(T));
  unswap(bufT, &this->T0);

  /* Read Discretization */
  std::getline(f, line);
  f.read(bufT, sizeof(T));
  unswap(bufT, &this->h);

  /* Read Mass */
  std::getline(f, line);
  f.read(bufT, sizeof(T));
  unswap(bufT, &M);

  /* Read Particle Positions */
  std::getline(f, line);
  ss << line;
  ss >> attr >> n1 >> datatype;
  ss.str(std::string());
  ss.clear();

  this->N = (unsigned int)(std::atoi(n1.c_str()));

  particles = std::vector< Particle<T> > (N,Particle<T>());
  
  for (unsigned int n=0; n<N; n++)
    {
      std::array<T,DIM> pos{{0.0,0.0,0.0}};
      for (unsigned int i=0; i<DIM; i++)
	{
	  f.read(bufT, sizeof(T));
	  unswap(bufT, &pos[i]);
	}
      particles[n].SetPos(pos);
      particles[n].SetMass(M);
    }

  /* Read Vertices and skip */
  std::getline(f, line);
  {
    char bufInt[2*N*sizeof(int)];
    f.read(bufInt, 2*N*sizeof(int));
  }

  /* Read Scalars */
  std::getline(f, line);
  std::getline(f, line);
  std::getline(f, line);
  for (unsigned int n=0; n<N; n++)
    {
      char bufFloat[sizeof(float)];
      f.read(bufFloat, sizeof(float));
    }
  std::cout << std::endl;

  /* Read Particles Velocities */
  std::getline(f, line);
  for (unsigned int n=0; n<N; n++)
    {
      std::array<T,DIM> vel{{0.0,0.0,0.0}};
      for (unsigned int i=0; i<DIM; i++)
        {
          f.read(bufT, sizeof(T));
          unswap(bufT, &vel[i]);
        }
      particles[n].SetVel(vel);
    }

  f.close();  
}

/* Initialize position of all the particles */
template <typename T>
void ParticleBox<T>::InitPosition(T M)
{
  unsigned int Ncube = 1;
  
  while (N > (Ncube*Ncube*Ncube))
    Ncube++;

  if ((T)std::pow(Ncube,3) != N)
    {
      std::cout << "Particle number " << N << " is not a perfect cube;" 
                << " this may result in a lousy initialization" << std::endl;
    }

  T rs = (T) L/Ncube;
  T roffset =  Lby2 - rs*(T)0.5;
  unsigned int n = 0;
  
  for (unsigned int x=0; x<Ncube; x++)
    {
      for (unsigned int y=0; y<Ncube; y++)
        {
          for (unsigned int z=0; z<Ncube; z++)
            {
              if (n < N)
                {
                  std::array<T,DIM> pos = {rs*x - roffset, rs*y - roffset, rs*z - roffset};
		  
		  particles[n].SetMass(M);
		  particles[n].SetPos(pos);
                  n++;
                }
            }
        }
    }
}

/* Initialize velocity of all the particles */
template <typename T>
void ParticleBox<T>::InitVelocity(T M)
{
  T netE = 0.0;
  T newP = 0.0;
  T vscale = 0.0;
  std::array<T,DIM> netP{{0.0,0.0,0.0}};

  std::srand(1);

  for (unsigned int n=0; n<N; n++)
    {
      std::array<T,DIM> vel{{0.0,0.0,0.0}};
      for (unsigned int x=0; x<DIM; x++)
	{
	  newP = ((T)rand())/((T)(RAND_MAX)) - (T)0.5;
	  netP[x] += newP;
	  netE += newP*newP;
	  vel[x] = newP;
	}
      particles[n].SetVel(vel);
    }

  netP = ((T)1.0/N)*netP;
  vscale = std::sqrt(3*N*T0/(M*netE));
  for (unsigned int n=0; n<N; n++)
    {
      std::array<T,DIM> &vel = particles[n].vel;
      for (unsigned int x=0; x<DIM; x++)
        {
          vel[x] = (vel[x] - netP[x]) * vscale;
        }
      particles[n].SetVel(vel);
    }
}

template <typename T>
void ParticleBox<T>::Advance_nSteps(unsigned int steps)
{
  std::array<T,3> computedE;

  ComputeEnergy(computedE);
  std::cout << 0 << " " << std::setprecision( 12 ) << computedE << std::endl;

  std::vector< std::array<T,DIM> > npos (N,{0.0,0.0,0.0}), nvel (N,{0.0,0.0,0.0});
  std::vector< std::array<T,DIM> > Fvec (N,{0.0,0.0,0.0});

  InternalForce(Fvec);

  for (unsigned int t=0; t<steps; t++)
    {
      for (unsigned int n=0; n<N; n++)
        {
          T &mass = particles[n].mass;
          std::array<T,DIM> &force = Fvec[n];
          std::array<T,DIM> acc = (1/mass)*force;
          particles[n].SetAcc(acc);
	  
	  std::array<T,DIM> pos = VerletNextR(n);
	  
	  for (unsigned int i=0; i<DIM; i++)
	    {
	      if (fabs(pos[i])>Lby2)
		{
		  pos[i] = (pos[i] - (T)nearbyint(pos[i]*Linv)*L);	      
		}
	    }

          npos[n] = pos;
        }
      SetPos(npos);

      InternalForce(Fvec);
      for (unsigned int n=0; n<N; n++)
        {
          T &mass = particles[n].mass;
          std::array<T,DIM> &nforce = Fvec[n];
	  std::array<T,DIM> nacc = (1/mass)*nforce;

          nvel[n] = (VerletNextV(n,nacc));
        }
      SetVel(nvel);

      ComputeEnergy(computedE);
      std::cout << t+1 << " " << std::setprecision( 12 ) << computedE << std::endl;
      this->currentStep++;
    }
  this->currentTime += this->currentStep*this->h;
}

template <typename T>
std::vector<T> ParticleBox<T>::OutputEnergy()
{  
  std::vector<T> energy = ConvertEnergytoVector();
  return energy;
}

template<typename T>
std::vector<T> ParticleBox<T>::ConvertEnergytoVector()
{
  std::array<T,3> energy;
  ComputeEnergy(energy);
  
  std::vector<T> energyvec (3,(T)0);  
  energyvec[0] = energy[0];
  energyvec[1] = energy[1];
  energyvec[2] = energy[2];

  return energyvec;
}

template <typename T>
void ParticleBox<T>::ComputeEnergy(std::array<T,3> &energy)
{
  energy = {0.0,0.0,0.0};

  for (unsigned int i=0; i<N; i++)
    {
      T &mass = particles[i].mass;
      std::array<T,DIM> &posi = particles[i].pos;
      std::array<T,DIM> &vel = particles[i].vel;

      // Kinetic Energy
      for (unsigned int k=0; k<DIM; k++)
        energy[1] += (T)0.5*mass*(vel[k]*vel[k]);

      // Potential Energy
      for (unsigned int j=0; j<i; j++)
        {
          std::array<T,DIM> &posj = particles[j].pos;
          T d = DistanceSq(posi,posj);
          energy[0] += Potential(d);
        }
    }
  // Total Energy
  energy[2] = energy[0] + energy[1];
}

template <typename T>
void ParticleBox<T>::InternalForce(std::vector< std::array<T,DIM> > &Fvec)
{
  Fvec[0] = {0.0,0.0,0.0};

  std::array<T,DIM> &Ri = particles[0].pos;
  for (unsigned int j=1; j<N; j++)
    {
      std::array<T,DIM> &Rj = particles[j].pos;
      std::array<T,DIM> dF;
      GetForce(Ri,Rj,dF);

      Fvec[0] += dF;
      Fvec[j]  = -(T)(1)*dF;
    }

  for (unsigned int i=1; i<N; i++)
    {
      std::array<T,DIM> &Ri = particles[i].pos;
      for (unsigned int j=i+1; j<N; j++)
	{	  
	  std::array<T,DIM> dF;
	  std::array<T,DIM> &Rj = particles[j].pos;
	  GetForce(Ri,Rj,dF);
	  
	  Fvec[i] += dF;
	  Fvec[j] -= dF;
	}
    }
}

template <typename T>
void ParticleBox<T>::GetForce(const std::array<T,DIM> &posi, 
			      const std::array<T,DIM> &posj, 
			      std::array<T,DIM> &F)
{
  T r2 = DistanceSq(posi,posj);
  T r2i = 1/r2;
  T r6i = r2i*r2i*r2i;

  Displacement(posi,posj,F);

  for (unsigned int i=0; i<DIM; i++)
    {
      F[i] = 24*r6i*r2i*(2*r6i-1)*F[i];
    }
}

template <typename T>
void ParticleBox<T>::Displacement(const std::array<T,DIM> &posi, 
				  const std::array<T,DIM> &posj, 
				  std::array<T,DIM> &d)
{
  d = {posi[0] - posj[0], posi[1] - posj[1], posi[2] - posj[2]};
  PutInBox(d);
}

template <typename T>
T ParticleBox<T>::DistanceSq(const std::array<T,DIM> &posi,
			   const std::array<T,DIM> &posj)
{
  std::array<T,DIM> d;
  Displacement(posi,posj,d);

  return L2normSq(d);
}

template <typename T>
T ParticleBox<T>::Potential(T r2)
{
  T r6 = r2*r2*r2;
  T r12 = r6*r6;

  return 4*(1/r12 - 1/r6);
}

template <typename T>
void ParticleBox<T>::PutInBox(std::array<T,DIM> &pos)
{
  for (unsigned int i=0; i<DIM; i++)
    {
      if (fabs(pos[i])>Lby2)
	{
	  pos[i] = (pos[i] - (T)nearbyint(pos[i]*Linv)*L);	  
	}
    }
}

template <typename T>
std::array<T,DIM> ParticleBox<T>::VerletNextR(unsigned int ind)
{
  std::array<T,DIM> rt_plus_h{{0.0,0.0,0.0}};
  
  std::array<T,DIM> &pos = particles[ind].pos;
  std::array<T,DIM> &vel = particles[ind].vel;
  std::array<T,DIM> &acc = particles[ind].acc;

  rt_plus_h += pos + h*vel + (T)0.5*h*h*acc;

  return rt_plus_h;
}

template <typename T>
std::array<T,DIM> ParticleBox<T>::VerletNextV(unsigned int ind, 
					      const std::array<T,DIM> &nacc)
{
  std::array<T,DIM> vt_plus_h{{0.0,0.0,0.0}};

  std::array<T,DIM> &vel = particles[ind].vel;
  std::array<T,DIM> &acc = particles[ind].acc;

  vt_plus_h += vel + (T)0.5*h*(acc + nacc);

  return vt_plus_h;
}

template <typename T>
void ParticleBox<T>::SetPos(const std::vector<std::array<T,DIM> > &pos)
{
  for (unsigned int n=0; n<N; n++)
    particles[n].SetPos(pos[n]);
}

template <typename T>
void ParticleBox<T>::SetVel(const std::vector<std::array<T,DIM> > &vel)
{
  for (unsigned int n=0; n<N; n++)
    particles[n].SetVel(vel[n]);
}

template <typename T>
void ParticleBox<T>::WriteData(std::string outputfile)
{  
  std::string Dtype = GetDtype();

  std::ofstream f (outputfile.c_str(), std::ios::binary);
  if (not f.is_open())
    {
      ThrowException("ERROR: Failed to open the file !");
    }

  T &M = particles[0].mass;

  /* Header */
  f << "# vtk DataFile Version 3.0" << std::endl;
  f << "Molecular Dynamics Output" << std::endl;
  f << "BINARY" << std::endl;
  f << "DATASET POLYDATA" << std::endl;

  f << "FIELD FieldData 6" << std::endl;

  f << "TIME 1 1 " << Dtype << std::endl;
  char bufT[sizeof(T)];
  swap(this->currentTime,bufT);
  f.write(bufT,sizeof(T));

  f << "CYCLE 1 1 " << "int" << std::endl;
  char bufI[sizeof(int)];
  swap(this->currentStep,bufI);
  f.write(bufI,sizeof(int));

  f << "BOXWIDTH 1 1 " << Dtype << std::endl;
  swap(L,bufT);
  f.write(bufT,sizeof(T));

  f << "TEMPERATURE 1 1 " << Dtype << std::endl;
  swap(T0,bufT);
  f.write(bufT,sizeof(T));

  f << "STEPSIZE 1 1 " << Dtype << std::endl;
  swap(h,bufT);
  f.write(bufT,sizeof(T));

  f << "MASS 1 1 " << Dtype << std::endl;
  swap(M,bufT);
  f.write(bufT,sizeof(T));
  
  /* x,y,z Coordinates of Points */
  f << "POINTS " << this->N << " " << Dtype << std::endl;
  for (unsigned int n=0; n < this->N; n++)
    {
      std::array<T,DIM> &pos = particles[n].pos;
      for (unsigned int i=0; i < DIM; i++)
	{
	  char buf[sizeof(T)];
	  swap(pos[i], buf);
	  f.write(buf, sizeof(T));
	}
    }
  
  /* Vertices */
  char one[sizeof(int)];
  swap(1, one);
  f << "VERTICES " << this->N << " " << 2*this->N << std::endl;
  for (int n=0; n < this->N; n++)
    {
      f.write(one, sizeof(int));
      char buf[sizeof(int)];
      swap(n, buf);
      f.write(buf, sizeof(int));
    }
  
  /* Scalar field data */
  f << "POINT_DATA " << this->N << std::endl;
  f << "SCALARS element" << " float" << std::endl;
  f << "LOOKUP_TABLE default" << std::endl;
  char onef[sizeof(float)];
  swap(1.0f, onef);
  for (unsigned int n=0; n < this->N; n++)
    {
      f.write(onef, sizeof(float));
    }
  
  /* Velocity Data */
  f << "VECTORS velocity" << " " << Dtype << std::endl;
  for (unsigned int n=0; n < this->N; n++)
    {
      std::array<T,DIM> &vel = particles[n].vel;
      for (unsigned int i=0; i < DIM; i++)
	{
	  char buf[sizeof(T)];
	  swap(vel[i], buf);
	  f.write(buf, sizeof(T));
	}
    }

  f.close();
  std::cout << "Solution saved to: " << outputfile << std::endl;
}

#endif /* PARTICLEBOX_HPP */
