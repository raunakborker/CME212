#include <array>
#include <cmath>
#include <iostream>
#include <vector>

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestCaller.h>
#include <cppunit/extensions/HelperMacros.h>

#include "auxfuncs.hpp"
#include "ParticleBox.hpp"

#define DIM 3
#define PRECISION double
#define TOL 1.e-10

class ParticleBoxTest: public CppUnit::TestCase
{  
  CPPUNIT_TEST_SUITE( ParticleBoxTest );
  CPPUNIT_TEST( Test00to10 );
  CPPUNIT_TEST( Test10to20 );
  CPPUNIT_TEST_SUITE_END();

public:
  ParticleBoxTest() : CppUnit::TestCase("ParticleBox Test") {}

  void Test00to10()
  {
    std::cout << "Test time 0 to 10 " << std::endl;

    // reference energy
    Array3<double> energy_ref;
    energy_ref[0] = -323.527790079;
    energy_ref[1] = 65.4308062926;
    energy_ref[2] = -258.096983787;
  
    Array3<double> energy (DIM,0.0);

    ParticleBox<PRECISION> PB("solution0.vtk");
    PB.Solve(10);

    PB.ComputeEnergy(energy);
    CPPUNIT_ASSERT( fabs(energy[0]-energy_ref[0])/fabs(energy_ref[0]) < TOL && \
                    fabs(energy[1]-energy_ref[1])/fabs(energy_ref[1]) < TOL && \
                    fabs(energy[2]-energy_ref[2])/fabs(energy_ref[2]) < TOL );
  }

  void Test10to20()
  {
    std::cout << "Test time 10 to 20 " << std::endl;

    Array3<double> energy_ref (DIM,0.0);
    energy_ref[0] = -311.566604177; 
    energy_ref[1] = 53.472789131; 
    energy_ref[2] = -258.093815046;  
    Array3<double> energy (DIM,0.0);
    
    ParticleBox<PRECISION> PB("solution10_ref.vtk");
    PB.Solve(10);
    PB.ComputeEnergy(energy);
    CPPUNIT_ASSERT( fabs(energy[0]-energy_ref[0])/fabs(energy_ref[0]) < TOL && \
                    fabs(energy[1]-energy_ref[1])/fabs(energy_ref[1]) < TOL && \
                    fabs(energy[2]-energy_ref[2])/fabs(energy_ref[2]) < TOL );
  }
};

int main()
{
  CppUnit::TextUi::TestRunner runner;
  runner.addTest(ParticleBoxTest::suite());
  bool successful = runner.run();
  return !successful;
}
