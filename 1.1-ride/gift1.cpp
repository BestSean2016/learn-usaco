/*
ID: stonegu1
PROG: gift1
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

using namespace std;

static map<string, int> account;
static int group_num = 0;
static vector<string> group;

void get_group(ifstream& in) {
    in >> group_num;
    string name;
    for (int i = 0; i < group_num; i++) {
	in >> name;
        group.push_back(name);
        account[name] = 0;
    }
}

void clean_group() {
    account.clear();
    group.clear();
}


void output_balance(ostream& out) {
    for(auto& p: group)
        out << p << " " << account[p] << endl;
}

void give_gift(ifstream& in) {
    string giver;
    string receiver;
    int amount;
    int number = 1;

    while(!in.eof()) {
        in >> giver >> amount >> number;
        if (in.eof())
            return;

        if (number == 0)
            continue;

        account[giver] -= amount;
        int reminder = amount % number;
        amount /= number;
        account[giver] += reminder;

        for (int i = 0; i < number; ++i) {
            in >> receiver;
            account[receiver] += amount;
        }
        //output_balance(cout);
        //cout << endl;
    }
}

int main() {
    ofstream fout ("gift1.out");
    ifstream fin ("gift1.in");

    get_group(fin);
    give_gift(fin);
    output_balance(fout);
    clean_group();

    fin.close();
    fout.close();
    return 0;
}
