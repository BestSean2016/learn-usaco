/* ID: stonegu1
PROG: crypt1
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdlib.h>

using namespace std;

static int digits[10] = {0};

static inline int get_last_digit(int* p) {
    int q = (*p) % 10;
    *p /= 10;
    return q;
}

int main() {
    ofstream fout ("crypt1.out");
    ifstream fin ("crypt1.in");

    int N = 0, result = 0;

    {//read input
        fin >> N;
        int d;
        for (int i = 0; i < N; ++i) {
            fin >> d;
            digits[d] = 1;
        }
    }
    //           a b c     <-- number 'abc'
    //         x   d e     <-- number 'de'; the 'x' means 'multiply'
    //       -----------
    // p1        * * *     <-- product of e * abc; first star might be 0 (absent)
    // p2      * * *       <-- product of d * abc; first star might be 0 (absent)
    //       -----------
    //         * * * *     <-- sum of p1 and p2 (e*abc + 10*d*abc) == de*abc
    {//output the result
        fout << result << endl << endl;
    }
    return (0);
}

