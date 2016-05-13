/*
ID: stonegu1
PROG: milk2
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;
typedef struct MILK {
    int  pos;
    char dir;
} MILK;

static vector<MILK> milks;
static char odd = 0;
static int longest_milk = 0;
static int longest_nomilk = 0;
static int milk_start = 0;

istream& operator>>(istream& in, MILK& milk) {
    in >> milk.pos;
    milk.dir = odd;
    odd =  1 - milk.dir;
    return in;
}

void insert_into_milks(MILK& milk) {
    vector<MILK>::iterator it = milks.begin();
    for (; it != milks.end(); it++) {
        if (milk.pos == (*it).pos && milk.dir != (*it).dir) {
            milks.erase(it);
            return;
        }

        if (milk.pos < (*it).pos) {
            milks.insert(it, milk);
            return;
        }
    }

    milks.push_back(milk); 
}

void milkman() {
    stack<int> s;
    milk_start = milks[0].pos;
    for (int i = 0; i < (int)milks.size(); ++i) {
        if (milks[i].dir == 0) {
            if (s.empty() && i > 0) {
                longest_nomilk = max(longest_nomilk, milks[i].pos - milks[i - 1].pos);
                milk_start = milks[i].pos;
            }
            s.push(milks[i].pos);
	} else {
            s.pop();
            if (s.empty())
                longest_milk = max(longest_milk, milks[i].pos - milk_start);
        }
    }
}

int main() {
    ofstream fout ("milk2.out");
    ifstream fin ("milk2.in");
    int N;
    fin >> N;

    for (int i = 0; i < 2 * N; ++i) {
        MILK milk;
        fin >> milk;
        insert_into_milks(milk);
    }

    //for (int i = 0; i < (int)milks.size(); ++i)
    //    cout << milks[i].pos << " " << (int)milks[i].dir << endl;

    milkman();

    fout << longest_milk <<  " " << longest_nomilk << endl;
 
    return 0;
}
