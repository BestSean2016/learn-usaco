/*
ID: stonegu1
LANG: C++11
PROG: wormhole
*/

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

typedef struct Point {
    uint x;
    uint y;
    uint xn;
    uint yn;
} Point;

typedef std::vector<Point> VecPoint;
static VecPoint wormholes;
static int N = 0;
static int MaxX = 0, MaxY = 0;
static int* loc; ///location
static int* wh;  ///location of wormholes;
static int* loc_wh; ///after wormhole was linked

int main(void) {
    std::ifstream in("wormhole.in");
    std::ofstream out("wormhole.out");

    //get wormholes
    in >> N;
    for (uint i = 0; i < N; ++i) {
        Point p;
        in >> p.x >> p.y;
        MaxX = std::max(MaxX, p.x);
        MaxY = std::max(MaxY, p.y);
        worms.push_back(p);
    }

    //initial location
    MaxX++; MaxY++;
    loc = (int*)calloc(MaxX * MaxY, sizeof(int));
    wh  = (int*)calloc(N, sizeof(int));
    loc_wh = (int*)calloc(MaxX * MaxY, sizeof(int));
    for (int x = 0; x < MaxX; ++x)
        for (int y = 0; y < MaxY; ++y)
            loc[x + y * MaxX] = (x + 1 == MaxX) ? -1 : (x + 1) + y * MaxX;

    //setting wormhole location

    //free memory
    free(loc_wh);
    free(wh);
    free(loc);
    return 0;
}
