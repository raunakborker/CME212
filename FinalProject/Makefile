CXX=g++
CXXFLAGS=-g -O3 -Wall -Wextra -Wconversion -std=c++11
LDFLAGS=-lcppunit

INCS = ParticleBox.hpp Particle.hpp array3.hpp macros.hpp
MAIN = main
TEST = test
PATHS = -I include/
SRC = src/main.cpp src/swap.cpp src/timer.c
TESTS = tests/tests.cpp src/swap.cpp

$(MAIN): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(MAIN) $(SRC) $(PATHS)
	./$(MAIN) 10 -o sol10.vtk
	./$(MAIN) 10 -i sol10.vtk -o sol20.vtk

check: $(TESTS)
	$(CXX) $(CXXFLAGS) -o $(TEST) $(TESTS) $(PATHS) $(LDFLAGS)
	./$(TEST)

clean:
	rm -f $(TEST) $(MAIN) *~
