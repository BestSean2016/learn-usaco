CC=gcc
CXX=g++
CFLAGS=-g -O2 -Wall
CXXFLAGS=-g -O2 -Wall -std=c++11

targets=crypt1-1 crypt1 combo

.PHONY: all

all: $(targets)

crypt1-1:	crypt1-1.cpp
	$(CXX) $(CXXFLAGS) -o $@ crypt1-1.cpp

crypt1:	crypt1.c
	$(CC) $(CFLAGS) -o $@ crypt1.c

combo:	combo.cpp
	$(CXX) $(CXXFLAGS) -o $@ combo.cpp

.PHONY:clean

clean:
	rm -f $(targets) *.out ~* *core*
