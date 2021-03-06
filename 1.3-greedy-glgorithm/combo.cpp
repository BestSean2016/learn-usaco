/*
ID: stonegu1
LANG: C++11
PROG: combo
*/

#include <stdio.h>
#include <set>
#include <string>
#include <iostream>
#include <fstream>

typedef unsigned char uint8;

static int    N = 0;
static int    d[6] = {0};
static uint8* array = 0;

static inline int get_num(int a) {
    if (a < 0)
        return a % N + N;
    else if (a == 0)
        return N;
    else if (a > N)
        if ((a - N) % N == 0)
            return N;
        else
            return (a - N) % N;
    else
        return a;
}

static int count = 0;
static void generate_combination(int b) {
    register int pos = 0;
    for (int i = -2; i <= 2; ++i) {
        for (int j = -2; j <= 2; ++j) {
            for (int k = -2; k <= 2; ++k) {
                pos = (get_num(d[b + 0] + i) - 1) + (get_num(d[b + 1] + j) - 1) * N + (get_num(d[b + 2] + k) - 1) * N * N;
                if (!array[pos]) {
                    array[pos] = 1;
                    ++count;
                }
            }
        }
    }
}

int main(void) {
    std::ifstream in("combo.in");
    std::ofstream out("combo.out");

    in >> N >> d[0] >> d[1] >> d[2] >> d[3] >> d[4] >> d[5];

    array = (uint8*)calloc(N * N * N, sizeof(uint8));
    generate_combination(0);
    generate_combination(3);
    free(array);
    out << count << std::endl;

    return 0;
}
