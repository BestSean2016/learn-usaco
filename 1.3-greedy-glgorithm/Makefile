CC=gcc
CXX=g++
CFLAGS=-g -O2 -Wall
CXXFLAGS=-g -O2 -Wall

crypt1-1:	crypt1-1.cpp
	$(CXX) $(CFLAGS) -o $@ crypt1-1.cpp

crypt1-2:	crypt1-2.cpp
	$(CXX) $(CXXFLAGS) -o $@ crypt1-2.cpp

target=crypt1-1 crypt1-2

all:	$(target)

clean:
	rm -f $(target) *.out
