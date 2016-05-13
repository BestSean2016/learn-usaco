/*
ID: stonegu1
PROG: friday
LANG: C++11
*/

#include <iostream>
#include <fstream>

using namespace std;

int frec[7] = {0};
int mdays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };


inline bool is_leap(int year) {
    return !(year % 4) && (year % 100 || !(year % 400));
}

void output(ostream& out) {
    for (int i = 0; i < 7; ++i)
        out << ((i) ? " " : "") << frec[i];
    out << endl;
}

void frequnce(int N) {
    int dow = 0;    /* day of week: January 13, 1900 was a Saturday = 0 */
    for(int y = 1900; y < 1900 + N; y++) {
        mdays[1] = (is_leap(y) ? 29 : 28);
        for (int m = 0; m < 12; m++) {
            frec[dow]++;
            dow = (dow + mdays[m]) % 7;
        }
    }
}

int main() {
    ofstream fout ("friday.out");
    ifstream fin ("friday.in");

    int N = 0;
    fin >> N;

    frequnce(N);
    output(fout);
    
    return 0;
}
