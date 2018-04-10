CXX=g++
CXXFLAGS=-g -O3 -Wall -Wextra -Wconversion -std=c++11
LDFLAGS=-lcppunit

INCS = ParticleBox.hpp Particle.hpp auxfuncs.hpp macros.hpp
MAIN = main
TEST = tests
PATHS = -I include/
SRC_EXEC = src/exec/main.cpp src/exec/swap.cpp src/exec/timer.c
SRC_TEST = src/tests/tests.cpp src/exec/swap.cpp

$(MAIN): $(SRC_EXEC)
	$(CXX) $(CXXFLAGS) -o $(MAIN) $(SRC_EXEC) $(PATHS)
	./$(MAIN) 10 -o sol10.vtk
	./$(MAIN) 10 -i sol10.vtk -o sol20.vtk

check: $(SRC_TEST)
	$(CXX) $(CXXFLAGS) -o $(TEST) $(SRC_TEST) $(PATHS) $(LDFLAGS)
	./$(TEST)

clean:
	rm -f $(TEST) $(MAIN) *~
