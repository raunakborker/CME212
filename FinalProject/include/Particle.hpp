#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <array>
#include <iostream>

#define DIM 3

template<typename T>
class ParticleBox;

/* Class that defines a particle in a MD simulation */
template <typename T>
class Particle
{
private:
  std::array<T,DIM> pos;
  std::array<T,DIM> vel;
  std::array<T,DIM> acc;
  T mass;
public:
  template<typename U> friend class ParticleBox;
  Particle(const std::array<T,DIM> &pos = {0.0,0.0,0.0},
           const std::array<T,DIM> &vel = {0.0,0.0,0.0},
           const std::array<T,DIM> &acc = {0.0,0.0,0.0},
           T mass = 1.0);
  void SetPos(const std::array<T,DIM> &R);
  void SetVel(const std::array<T,DIM> &V);
  void SetAcc(const std::array<T,DIM> &A);
  void SetMass(T M);
  std::array<T,DIM> GetPos(void);
  std::array<T,DIM> GetVel(void);
  std::array<T,DIM> GetAcc(void);
  T GetMass(void);
};

template <typename T>
Particle<T>::Particle(const std::array<T,DIM> &pos, 
                      const std::array<T,DIM> &vel,
                      const std::array<T,DIM> &acc,
                      T mass)
{
  this->pos = pos;
  this->vel = vel;
  this->acc = acc;
  this->mass = mass;
}

template <typename T>
void Particle<T>::SetPos(const std::array<T,DIM> &R)
{
  this->pos = R;
}

template <typename T>
void Particle<T>::SetVel(const std::array<T,DIM> &V)
{
  this->vel = V;
}

template <typename T>
void Particle<T>::SetAcc(const std::array<T,DIM> &A)
{
  this->acc = A;
}

template <typename T>
void Particle<T>::SetMass(T M)
{
  this->mass = M;
}

template <typename T>
std::array<T,DIM> Particle<T>::GetPos(void)
{
  return this->pos;
}

template <typename T>
std::array<T,DIM> Particle<T>::GetVel(void)
{
  return this->vel;
}

template <typename T>
std::array<T,DIM> Particle<T>::GetAcc(void)
{
  return this->acc;
}

template <typename T>
T Particle<T>::GetMass(void)
{
  return this->mass;
}

#endif /* PARTICLE_HPP */
