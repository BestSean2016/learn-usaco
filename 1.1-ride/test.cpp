/*
ID: your_id_here
PROG: test
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
int 
mod(int n, int m)
{
    while(n < 0)
	n += m;
    return n%m;
}

int main() {
/*    ofstream fout ("test.out");
    ifstream fin ("test.in");
    int a, b;
    fin >> a >> b;
    fout << a+b << endl;
*/

    int p = -15;
    int q = 4;
    cout << p % q << endl;
    cout << mod(p, q) << endl;

    return 0;
}
