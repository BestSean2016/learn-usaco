/*
ID: stonegu1
PROG: milk
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;
static int N, M;

typedef struct milk_price {
    int index;
    int price;
    int amount;
} milk_price;

static milk_price* mp = nullptr;

int compare(const void* mp1, const void* mp2) {
    return (((milk_price*)mp1)->price - ((milk_price*)mp2)->price);
}

int main() {
    ofstream fout ("milk.out");
    ifstream fin ("milk.in");

    fin >> N >> M;
    mp = new milk_price[M];
    for (int i = 0; i < M; i++) {
        mp[i].index = i;
        fin >> mp[i].price >> mp[i].amount;
    }

    qsort(mp, M, sizeof(mp[0]), compare);
    //for (int i = 0; i < M; i++)
    //    fout << mp[i].index << " " << mp[i].price << endl;
   
    int sum = 0, i = 0, money = 0;
    while(sum < N) {
        if (N - sum >= mp[i].amount)
            sum += mp[i].amount,
            money += mp[i].amount * mp[i].price;
        else
            money += (N - sum) * mp[i].price,
            sum = N; 
        ++i;
        //cout << sum << " " << money << endl;  
    } 
    delete mp;

    fout << money << endl;
    return 0;
}
