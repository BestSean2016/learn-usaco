/*
ID: stonegu1
LANG: C++11
PROG: wormhole
*/

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

typedef unsigned char uint8;
typedef unsigned int  uint32;

typedef struct Point {
    uint32 x;
    uint32 y;
} Point;

typedef std::vector<Point> VecPoint;
static VecPoint wormholes;
static uint8 N = 0; /// 2 <= N <= 12
static uint32 MaxX = 0, MaxY = 0;
static uint8* holepair; ///hole-pair


void visit() {
    for (uint8 i = 1; i <= N; i++)
        std::cout << (uint)i << ", " << (uint)holepair[i] << std::endl;
    std::cout << std::endl;
}

int main(void) {
    std::ifstream in("wormhole.in");
    std::ofstream out("wormhole.out");

    //get wormholes
    int N0;
    in >> N0;
    N = static_cast<uint8>(N0);
    for (uint8 i = 0; i < N; ++i) {
        Point p;
        in >> p.x >> p.y;
        MaxX = std::max(MaxX, p.x);
        MaxY = std::max(MaxY, p.y);
        wormholes.push_back(p);
    }

    //generating all hole-pairs
    holepair = new uint8[sizeof(uint8) * (N + 1)];
    memset(holepair, 0, sizeof(uint8) * (N + 1));
    uint32 j = 0;
    {
    M2:
        visit();
        j = N;
    M4:
        if (holepair[j] == (N - 1)) {
            holepair[j] = 0;
            --j;
            goto M4;
        }

        if (j != 0) {
            holepair[j] += 1;
            goto M2;
        }
    }

    //free memory
    free(holepair);
    //free(wh);
    //free(loc);
    return 0;
}
