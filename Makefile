CXX = g++
CXXFLAGS = -O2 -Wall -std=c++0x -pedantic

.PHONY: clean

FenwickTree: main.o
	$(CXX) $< -o $@

main.o: main.cpp FenwickTree.hpp RangeFenwickTree.hpp
	$(CXX) -c $(CXXFLAGS) $<
	
clean:
	rm -f FenwickTree
	rm -f main.o

