/*
ID: stonegu1
PROG: palsquare
LANG: C++
*/
#include <fstream>
#include <string>
using namespace std;
 
char NUMBER[20] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 
                   'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
 
string convert(int, int);
bool is_plalindrome(string);
 
int main()
{
    ifstream fin("palsquare.in");
    ofstream fout("palsquare.out");
 
    int b;
    fin >> b;
 
    string num, square;
    for (int i = 1; i <= 300; ++i) {
        num = convert(i, b);
        square = convert(i*i, b);
        if (is_plalindrome(square))
            fout << num << " " << square << "\n";
    }
 
    return 0;
}
 
string convert(int n, int b)
{
    string number;
    while (n) {
        number.insert(number.begin(), NUMBER[n%b]);
        n /= b;
    }
    return number;
}
 
bool is_plalindrome(string s)
{
 
    for (string::iterator back = s.begin(), forward = s.end()-1;
         back < forward; ++back, --forward) {
        if (*back != *forward)
            return false;
    }
    return true;
}
