CXX = g++
CXXFLAGS = -g -Wall -std=gnu++11
SHELL = bash
program = worddice
objects = worddice.o classes.o

all: $(program)

$(program): $(objects)
	$(CXX) $(CXXFLAGS) $^ -o $@

worddice.o: worddice.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ 

classes.o: classes.cpp classes.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean 

clean:
	rm -f $(program) $(objects)