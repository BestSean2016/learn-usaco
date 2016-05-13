/* ID: stonegu1
PROG: transform
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdlib.h>

using namespace std;

#define TRANS_TYPE_ROT90       1
#define TRANS_TYPE_ROT180      2
#define TRANS_TYPE_ROT270      3
#define TRANS_TYPE_REFLACTION  4
#define TRANS_TYPE_COMBINATION 5
#define TRANS_TYPE_NO_CHANGE   6
#define TRANS_TYPE_INVALID     7

class Matrix {
public:
    int n;
    char* data;
    Matrix(int N) : n(N), data(0) {
        data = new char[N * N];
    }
    Matrix() : n(0), data(0) {}
    ~Matrix() {
        if (data) delete data;
    }
    
    void copy(Matrix& A) {
        if (n == A.n) {
            for (int i = 0; i < n * n; ++i)
                data[i] = A.data[i];
        }
    }

    bool operator== (Matrix& A) {
        if (A.n != n) return false;
        for (int i = 0; i < n * n; ++i)
            if (data[i] != A.data[i])
                return false;

        return true;
    }

    Matrix& rot90() {
        Matrix B(n);
        for (int i = 0; i < n * n; ++i) {
            int r = i / n, c = i % n;
            //cout << r << ", " << c << " -> " << c << ", " << n - r - 1 << " : " << c * n + n - r - 1 << endl;
            B.data[c * n  + n - r - 1] = data[i];
        } 
        copy(B);
        return *this;
    }

    Matrix& rot180() {
        Matrix B(n);
        for (int i =0; i < n * n; ++i) {
            int r = i / n, c = i % n;
            B.data[(n - r - 1) * n + (n - c - 1)] = data[i];
        }
        copy(B);
        return *this;
    }

    Matrix& rot270() {
        Matrix B(n);
        for (int i = 0; i < n * n; ++i) {
            int r = i / n, c = i % n;
            B.data[(n - c - 1) * n + r] = data[i];
        }
        copy(B);
        return *this;
    }

    Matrix& reflaction() {
        Matrix B(n);
        for (int i =0; i < n * n; ++i) {
            int r = i / n, c = i % n;
            B.data[r * n + (n - c - 1)] = data[i];
        }
        copy(B);
        return *this;
    }

    void random() {
        srand(time(0));
        for (int i = 0; i < n * n; ++i)
            data[i] = (rand() % 2) ? '@' : '-';
    }

    typedef Matrix& (Matrix::*transfun) (void);
    Matrix& transform(int action) {
        transfun fun = 0;
        switch(action) {
        case TRANS_TYPE_ROT90:
            fun = &Matrix::rot90;
            break;
        case TRANS_TYPE_ROT180:
            fun = &Matrix::rot180;
            break;
        case TRANS_TYPE_ROT270:
            fun = &Matrix::rot270;
            break;
        case TRANS_TYPE_REFLACTION:
            fun = &Matrix::reflaction;
            break;
        case 5:
        case 6:
        case 7:
            return (*this);
        }

        return (this->*fun)();
    }
};


istream& operator>>(istream& in, Matrix& A) {
    for (int i = 0; i < A.n * A.n; ++i)
        in >> A.data[i];

    return in;
};

ostream& operator<<(ostream& o, Matrix& a) {
    for (int i = 0; i < a.n * a.n; ++i) {
        o << a.data[i];
        if ((i + 1) % a.n == 0) o << endl;
    }
    o << endl;
    return o;
}

static void test();
static void output_result(ostream& fout, bool valid, vector<int> trans_types) {
    if (!valid)
        fout << TRANS_TYPE_INVALID << endl;
    else {
        for(auto& p: trans_types)
            fout << p << endl;
    }
}

int main() {
    ofstream fout ("transform.out");
    ifstream fin ("transform.in");
    int N;
    fin >> N;
    Matrix A(N), B(N);
    fin >> A >> B;

    //cout << "A and B" << endl << A << B << endl;
    //test(N);

    vector<int> trans_type;
    bool valid = false;
    //if (A == B) {
    //    trans_type.push_back(TRANS_TYPE_NO_CHANGE);
    //    valid = true;
    //}

    Matrix C(N);
    if (!valid) {
        for (int i = TRANS_TYPE_ROT90; i <= TRANS_TYPE_REFLACTION; ++i) {
            C.copy(A);
            C.transform(i);
            if (C == B) {
                trans_type.push_back(i);
                valid = true;
                break;
            }
        }
    }

    if (!valid) {
        C.copy(A);
        C.transform(TRANS_TYPE_REFLACTION);
        for (int i = TRANS_TYPE_ROT90; i <= TRANS_TYPE_ROT270; ++i) {
            Matrix D(N);
            D.copy(C);
            D.transform(i);
            if (D == B) {
                trans_type.push_back(TRANS_TYPE_COMBINATION);
                valid = true;
                break;
            }
        }
    }

    output_result(fout, valid, trans_type);

    return 0;
}

void test() {
    int N;
    cin >> N;

    Matrix A(N);
    A.random();

    Matrix C(N), D(N);

    /*D.copy(A);
    D.rot180();
    cout << D << endl;

    C.transform(TRANS_TYPE_ROT90);
    cout << "D == C is " << (D == C) << endl;

    D.copy(A);
    D.rot270();
    cout << D << endl;
    C.transform(TRANS_TYPE_ROT90);
    cout << "D == C is " << (D == C) << endl;

    D.rot90();
    cout << "d == a IS" << (D == A) << endl;

    D.copy(A);
    D.reflaction();
    cout << D << endl;
*/
//-----------------------------
    D.copy(A);
    C.copy(A);
    C.transform(TRANS_TYPE_ROT90);
    C.transform(TRANS_TYPE_REFLACTION);
    C.transform(TRANS_TYPE_ROT90);
    D.reflaction();
    cout << "test10 D == C is " << (D == C) << endl;

    D.copy(A);
    C.copy(A);
    C.transform(TRANS_TYPE_ROT90);
    C.transform(TRANS_TYPE_REFLACTION);
    C.transform(TRANS_TYPE_ROT180);
    D.reflaction();
    D.rot90();
    cout << "test11 D == C is " << (D == C) << endl;

    D.copy(A);
    C.copy(A);
    C.transform(TRANS_TYPE_ROT90);
    C.transform(TRANS_TYPE_REFLACTION);
    C.transform(TRANS_TYPE_ROT270);
    D.reflaction();
    D.rot180();
    cout << "test12 D == C is " << (D == C) << endl;

//---------------
    D.copy(A);
    C.copy(A);
    C.transform(TRANS_TYPE_ROT180);
    C.transform(TRANS_TYPE_REFLACTION);
    C.transform(TRANS_TYPE_ROT90);
    D.reflaction();
    D.rot270();
    cout << "test13 D == C is " << (D == C) << endl;

    D.copy(A);
    C.copy(A);
    C.transform(TRANS_TYPE_ROT180);
    C.transform(TRANS_TYPE_REFLACTION);
    C.transform(TRANS_TYPE_ROT180);
    D.reflaction();
    cout << "test14 D == C is " << (D == C) << endl;

    D.copy(A);
    C.copy(A);
    C.transform(TRANS_TYPE_ROT180);
    C.transform(TRANS_TYPE_REFLACTION);
    C.transform(TRANS_TYPE_ROT270);
    D.reflaction();
    D.rot90();
    cout << "test15 D == C is " << (D == C) << endl;

//---------------
    D.copy(A);
    C.copy(A);
    C.transform(TRANS_TYPE_ROT270);
    C.transform(TRANS_TYPE_REFLACTION);
    C.transform(TRANS_TYPE_ROT90);
    D.reflaction();
    D.rot180();
    cout << "test16 D == C is " << (D == C) << endl;

    D.copy(A);
    C.copy(A);
    C.transform(TRANS_TYPE_ROT270);
    C.transform(TRANS_TYPE_REFLACTION);
    C.transform(TRANS_TYPE_ROT180);
    D.reflaction();
    D.rot270();
    cout << "test17 D == C is " << (D == C) << endl;

    D.copy(A);
    C.copy(A);
    C.transform(TRANS_TYPE_ROT270);
    C.transform(TRANS_TYPE_REFLACTION);
    C.transform(TRANS_TYPE_ROT270);
    D.reflaction();
    //D.rot90();
    cout << "test18 D == C is " << (D == C) << endl;


//---------------
    D.copy(A);
    C.copy(A);
    C.transform(TRANS_TYPE_REFLACTION);
    C.transform(TRANS_TYPE_ROT90);
    C.transform(TRANS_TYPE_REFLACTION);
    D.rot270();
    cout << "test19 D == C is " << (D == C) << endl;

    D.copy(A);
    C.copy(A);
    C.transform(TRANS_TYPE_REFLACTION);
    C.transform(TRANS_TYPE_ROT180);
    C.transform(TRANS_TYPE_REFLACTION);
    D.rot180();
    cout << "test20 D == C is " << (D == C) << endl;

    D.copy(A);
    C.copy(A);
    C.transform(TRANS_TYPE_REFLACTION);
    C.transform(TRANS_TYPE_ROT270);
    C.transform(TRANS_TYPE_REFLACTION);
    D.rot90();
    cout << "test21 D == C is " << (D == C) << endl;
//
}
