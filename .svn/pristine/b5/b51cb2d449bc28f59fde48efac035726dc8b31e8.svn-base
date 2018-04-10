CXX=g++
CXXFLAGS=-g -O3 -Wall -Wextra -Wconversion -std=c++11
LDFLAGS=-lcppunit

INCS = ParticleBox.hpp Particle.hpp auxfuncs.hpp macros.hpp
MAIN = main
TEST = tests
PATHS = -I include/
SRC_EXEC = src/exec/main.cpp
SRC_TEST = src/tests/tests.cpp

$(MAIN): $(SRC_EXEC)
	$(CXX) $(CXXFLAGS) -o $(MAIN) $(SRC_EXEC) $(PATHS)
	./$(MAIN) 10 -o sol10.dat
	./$(MAIN) 10 -i sol10.dat -o sol20.dat

check: $(SRC_TEST)
	$(CXX) $(CXXFLAGS) -o $(TEST) $(SRC_TEST) $(PATHS) $(LDFLAGS)
	./$(TEST)

clean:
	rm -f $(TEST) $(MAIN) *~
