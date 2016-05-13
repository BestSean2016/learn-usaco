/*
ID: stonegu1
PROG: ride
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

unsigned int code(const string str) {
    unsigned int p = 1;
    for (int i = 0; i < str.length(); i++)
        p = ((str[i] - 'A' + 1) * p) % 47;
    return p;
}

int main() {
    ofstream fout ("ride.out");
    ifstream fin ("ride.in");
    string comet, group;
    fin >> comet >> group;

    fout << ((code(comet) == code(group)) ? "GO" : "STAY") << endl;

    return 0;
}
