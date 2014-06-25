GXX = g++
GXXFLAGS = -O2 -Wall -std=c++0x -pedantic

BIN = FenwickTree
OBJS = main.o

.PHONY: all clean

all: $(BIN)
	
$(BIN): $(OBJS)
	$(GXX) $(OBJS) -o $(BIN)

main.o: main.cpp FenwickTree.hpp RangeFenwickTree.hpp
	$(GXX) -c $(GXXFLAGS) $< -o $@
	
clean:
	rm -f $(BIN) $(OBJS)

