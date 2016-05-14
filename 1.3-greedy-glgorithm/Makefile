CC=gcc
CXX=g++
CFLAGS=-g -O2 -Wall
CXXFLAGS=-g -O2 -Wall

targets=crypt1-1 crypt1-2
.PHONY: all

all: $(targets)

crypt1-1:	crypt1-1.cpp
	$(CXX) $(CXXFLAGS) -o $@ crypt1-1.cpp

crypt1-2:	crypt1-2.cpp
	$(CXX) $(CXXFLAGS) -o $@ crypt1-2.cpp


.PHONY:clean

clean:
	rm -f $(targets) *.out
