/*
ID: stonegu1
PROG: milk2
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
typedef struct MILK {
    int  pos;
    char dir;
} MILK;

static int N = 0;
static MILK milks[5000 * 2];
static char odd = 0;
static int longest_milk = 0;
static int longest_nomilk = 0;


istream& operator>>(istream& in, MILK& milk) {
    in >> milk.pos;
    milk.dir = odd;
    odd =  1 - milk.dir;
    return in;
}


int eventcmp (const MILK *a, const MILK *b)
{
   if (a->pos != b->pos)
      return (a->pos - b->pos); /* 300 before 500 */

   return (b->dir - a->dir); /* 1 (start) before -1 (stop) */
}

void milkman() {
    int milk_time = 0;
    int milk_start = 0;
    bool is_break = true;
 
    for (int i = 0; i < 2 * N - 1; ++i) {
        if (milks[i].dir == 0) {
            if (++milk_time == 1 && is_break) {
                milk_start = milks[i].pos;
                is_break = false;
            }
	} else {
            --milk_time;
            if (milk_time == 0) {
                if (milks[i + 1].pos > milks[i].pos) {
                    longest_nomilk = max(longest_nomilk, milks[i + 1].pos - milks[i].pos);
                    longest_milk = max(longest_milk, milks[i].pos - milk_start);
                    is_break = true;
                }
            }
        }
    }
   
    longest_milk = max(longest_milk, milks[2 * N - 1].pos - milk_start);
}

int main() {
    ofstream fout ("milk2.out");
    ifstream fin ("milk2.in");
    fin >> N;

    for (int i = 0; i < 2 * N; i++)
        fin >> milks[i];

    qsort(milks, 2 * N, sizeof(MILK), (int (*)(const void*, const void*))eventcmp);

    milkman();

    fout << longest_milk <<  " " << longest_nomilk << endl;
 
    return 0;
}
