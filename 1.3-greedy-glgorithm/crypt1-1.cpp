/* ID: stonegu1
PROG: crypt1
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdlib.h>

using namespace std;


int main() {
    ofstream fout ("crypt1.out");
    ifstream fin ("crypt1.in");

    int N = 0, result = 0;
    std::vector<int> digits;

    {//read input
        fin >> N;
        int d;
        for (int i = 0; i < N; ++i) {
            fin >> d;
            digits.push_back(d);
        }
    }
    //           a b c     <-- number 'abc'
    //         x   d e     <-- number 'de'; the 'x' means 'multiply'
    //       -----------
    // p1        * * *     <-- product of e * abc; first star might be 0 (absent)
    // p2      * * *       <-- product of d * abc; first star might be 0 (absent)
    //       -----------
    //         * * * *     <-- sum of p1 and p2 (e*abc + 10*d*abc) == de*abc
    {//find the anwser
        //first number
        for (int a = 0; a < N; ++a) {
            for (int b = 0; b < N; ++b) {
                for (int c = 0; c < N; ++c) {
                    int abc = digits[a] * 100 + digits[b] * 10 + digits[c];

                    //second number
                    for (int d = 0; d < N; ++d) {
                        for (int e = 0; e < N; ++e) {
                            int de = digits[d] * 10 + digits[e];

                            //third number
                            for (int p1_1 = 0; p1_1 < N; ++p1_1) {
                                for (int p1_2 = 0; p1_2 < N; ++p1_2) {
                                    for (int p1_3 = 0; p1_3 < N; ++p1_3) {
                                        int p1 = digits[p1_1] * 100 + digits[p1_2] * 10 + digits[p1_3];
                                        if (abc * digits[e] != p1) continue;

                                        //fourth number
                                        for (int p2_1 = 0; p2_1 < N; ++p2_1) {
                                            for (int p2_2 = 0; p2_2 < N; ++p2_2) {
                                                for (int p2_3 = 0; p2_3 < N; ++p2_3) {
                                                    int p2 = digits[p2_1] * 100 + digits[p2_2] * 10 + digits[p2_3];
                                                    if (abc * digits[d] != p2) continue;

                                                    //fiveth number
                                                    for (int sum_1 = 0; sum_1 < N; ++sum_1) {
                                                        for (int sum_2 = 0; sum_2 < N; ++sum_2) {
                                                            for (int sum_3 = 0; sum_3 < N; ++sum_3) {
                                                                for (int sum_4 = 0; sum_4 < N; ++sum_4) {
                                                                    int sum = digits[sum_1] * 1000 + digits[sum_2] * 100 + digits[sum_3] * 10 + digits[sum_4];

                                                                    if (sum == p2 * 10 + p1 && sum == abc * de) {
                                                                        //cout << abc << " * " << de << " = " << sum << ", p1 = " << p1 << ", p2 = " << p2 << std::endl;
                                                                        ++result;
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    {//output the result
        fout << result << endl << endl;
    }
    return (0);
}

