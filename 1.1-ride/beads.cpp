/*
ID: stonegu1
PROG: beads
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
static string necklace = "";
static int length = 0;

/*
 * Return n positive mod m.
 */
int mod(int n, int m)
{
    while(n < 0)
        n += m;
    return n % m;
}

/*
 * Calculate number of beads gotten by breaking
 * before character p and going in direction dir,
 * which is 1 for forward and -1 for backward.
 */
int nbreak(int p, int dir)
{
    char color;
    int i, n;

    color = 'w';

    /* Start at p if going forward, bead before if going backward */
    if(dir > 0)
        i = p;
    else
        i = mod(p-1, len);

    /* We use "n<len" to cut off loops that go around the whole necklace */
    for(n=0; n<len; n++, i=mod(i+dir, len)) {
        /* record which color we're going to collect */
        if(color == 'w' && necklace[i] != 'w')
            color = necklace[i];

        /*
         * If we've chosen a color and see a bead
         * not white and not that color, stop
         */
        if(color != 'w' && necklace[i] != 'w' && necklace[i] != color)
            break;
    }
    return n;
}

int main() {
    ofstream fout ("beads.out");
    ifstream fin ("beads.in");

    fin >> length >> necklace;

    int maxc = -1;
    for (int i = 0; i < length; ++i) {
        int len = nbreak(1, i) + nbreak(-1, i);
        len = (len > n) ? n : len;
        maxc = max(maxc, len);
    }

    fout << maxc << endl;
    
    return 0;
}
