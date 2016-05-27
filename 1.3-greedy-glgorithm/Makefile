CC=gcc
CXX=g++
CFLAGS=-g -O2 -Wall
CXXFLAGS=-g -O2 -Wall -std=c++11

targets=crypt1-1 crypt1 combo wormhole milk barn1

.PHONY: all

all: $(targets)

crypt1-1:	crypt1-1.cpp
	$(CXX) $(CXXFLAGS) -o $@ crypt1-1.cpp

crypt1:	crypt1.c
	$(CC) $(CFLAGS) -o $@ crypt1.c

combo:	combo.cpp
	$(CXX) $(CXXFLAGS) -o $@ combo.cpp

wormhole:	wormhole.cpp
	$(CXX) $(CXXFLAGS) -o $@ wormhole.cpp

milk:	milk.cpp
	$(CXX) $(CXXFLAGS) -o $@ milk.cpp

barn1:	barn1.cpp
	$(CXX) $(CXXFLAGS) -o $@ barn1.cpp

.PHONY:clean

clean:
	rm -f $(targets) *.out ~* *core*
