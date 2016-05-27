/*
ID : stonegu1
PROG : barn1
LANG : C++11
*/

#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
int repair(vector<int>, int);
 
int main()
{    
    ifstream fin("barn1.in");
    ofstream fout("barn1.out");
 
    int board_num, shed_num, cow_num, stall_num;
    fin >> board_num >> shed_num >> cow_num;
    vector<int> barn(shed_num+1, 0);
    while (fin >> stall_num)
        barn[stall_num] = 1;
 
    fout << repair(barn, board_num) << endl;
    return 0;
}
 
int repair(vector<int> barn, int board_num)
{
    int begin = 0, end = 0;
    for (vector<int>::iterator iter = barn.begin()+1; iter != barn.end(); ++iter) {
        if (*iter) {
            begin = iter - barn.begin();
            break;
        }
    }
    for (vector<int>::iterator iter = barn.end()-1; iter != barn.begin(); --iter) {
        if (*iter) {
            end = iter - barn.begin();
            break;
        }
    }
 
    vector<int> blank;
    int is_blank = 0, blank_length = 0;
    for (int i = begin; i <= end; ++i) {
        if (barn[i]) {
            if (is_blank) {
                if (blank_length)
                    blank.push_back(blank_length);
                is_blank = 0;
                blank_length = 0;
            }
        } else {
            if (is_blank)
                ++blank_length;
            else {
                is_blank = 1;
                blank_length = 1;
            }
        }
    }
 
    int length = end - begin + 1, boards = 1;
    if (blank.empty())
        return length;
 
    sort(blank.begin(), blank.end());
    vector<int>::reverse_iterator iter = blank.rbegin();
    while (boards < board_num && iter != blank.rend()) {
        length -= *iter++;
        ++boards;
    }
    return length;
}

