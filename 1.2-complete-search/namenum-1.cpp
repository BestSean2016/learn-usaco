/* ID: stonegu1
PROG: namenum
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <stdlib.h>
#include <memory.h>

using namespace std;
#define MAX_CHILD 26
#define MAX_STRING_LEN 64

typedef unsigned char uint8_t;
typedef struct node {
    char me;
    struct node* child[MAX_CHILD];
    struct node* parent;
    uint8_t deep;
    uint8_t child_num;
    bool has_break;
    node(char c) : me(c), parent(0), deep(0), child_num(0) {
        memset(child, 0, sizeof(child));
    }
    node(char c, struct node* p) : me(c), parent(p), child_num(0) {
        memset(child, 0, sizeof(child));
        deep = p->deep + 1;
        ++p->child_num;
    }
    bool get_name(char* buf, int buflen) {
        if (buflen < deep + 1) {
            *buf = 0;
            return false;
        }
        buf[deep] = 0;
        node* p = this;
        for (int i = deep - 1; p; p = p->parent, --i)
            buf[i] = p->me;
        return true;
    }
} node;

static void free_node(node* n) {
    if (n) {
        for (int i = 0; i < MAX_CHILD; ++i)
            free_node(n->child[i]);
        delete n;
    }
}

static void del_node(node* n) {
    if (!n) return;
    //get the top level parent
    node* p = n;
    while(p && p->parent && p->parent->parent)
        p = p->parent;
    node* top = p->parent;
    if (top) {
        char c = p->me;
        if (c) {
            free_node(p);
            top->child[c -'A'] = 0;
        }
    }
}

ostream& operator<< (ostream& out, node* n) {
    if (!n) {
        cout << "null node\n";
    } else {
        char str[MAX_STRING_LEN];
        n->get_name(str, MAX_STRING_LEN);
        out << str;
    }
    return out;
}

map<int, string> num_name = {
    {2, "ABC"},
    {3, "DEF"},
    {4, "GHI"},
    {5, "JKL"},
    {6, "MNO"},
    {7, "PRS"},
    {8, "TUV"},
    {9, "WXY"},
};

//for test---------------
  vector<string> words;
//-----------------------
vector<string> cow_names;

class dict {
public:
    node* head;
    int amount;

    dict() : amount(0) {
        head = new node(0);
    }
    ~dict() {
        free_node(head);
    }

    //return the amount of words
    int read_dict(string dict_file) {
        ifstream fin(dict_file);
        while(!fin.eof()) {
            string word;
            fin >> word;
            //if (word[0]) cout << word << endl;
            if (word.size() > 0 && word[0]) {
                add_to_dict(word);
                words.push_back(word);
                ++amount;
            }
        }
        return amount;
    }

    void output() {
        output_(head);
    }

    node* search(string word) {
        node* n = head;
        for (auto& p : word) {
            n = n->child[p - 'A'];
            if (!n)
                break;
        }
        return n;
    }


    node* search_word(string word) {
        node* n = head;
        for (auto& p : word) {
            n = n->child[p - 'A'];
            if (!n)
                break;
        }

        return (n->has_break) ? n : 0;
    }


    void freenodes() {
        free_node(head);
        head = new node(0);
    }

    void getnames(int deep) {
        getnames_(head, deep);
    }

private:
    void add_to_dict(string word) {
        node* h = head;
        //cout << word;
        for (auto& p : word) {
            //cout << " " << p - 'A';
            if (h->child[p - 'A'] == 0)
                h->child[p - 'A'] = new node(p, h);
            h = h->child[p - 'A'];
        }
        h->has_break = true;
        //cout << endl;
    }

    void output_(node *h) {
        if (h->child_num == 0)
            cout << h << endl;
        else {
            for (auto&c : h->child)
                if (c) output_(c);
        }
    }

    void getnames_(node* h, int deep) {
        if (h->child_num == 0 && h->deep == deep) {
            char buf[MAX_STRING_LEN];
            h->get_name(buf, MAX_STRING_LEN);
            cow_names.push_back(buf);
        } else {
            for (auto&c : h->child)
                if (c) getnames_(c, deep);
        }
    }
};

static void test_search(dict& d) {
    srand(time(0));
    for (int times = 0; times < 1000000; ++times) {
        int i  = rand() % d.amount;
        node* n = d.search(words[i]);
        if (!n)
            cout << "ERR: Can not find word " << words[i] << endl;
        //else
        //    cout << n << endl;
    }
}

dict gdict;
dict namedict;
char gbuf[MAX_STRING_LEN];

void add_to_level(node* h, char c, int deep) {
    if (h->deep == deep - 1) {
        h->get_name(gbuf, MAX_STRING_LEN);
        string s(gbuf);
        s.push_back(c);

        if (gdict.search(s))
            h->child[c - 'A'] = new node(c, h);
    } else if (h->deep < deep - 1){
        for (int i = 0; i < MAX_CHILD; ++i)
            if (h->child[i])
                add_to_level(h->child[i], c, deep);
    }
}

void namenum(string number) {
    node* h = namedict.head;
    for (int i = 0; i < (int)number.size(); i++) {
        string nn = num_name[number[i] - '0'];
        if (nn.size() == 0) {
            namedict.freenodes();
            return;
        }
        for (auto& c : nn)
            add_to_level(h, c, i + 1);
    }
}



int main() {
    gdict.read_dict("dict.txt");
    // gdict.output();
    // test_search(gdict);
    // gdict.search_word("GREG");

    // string str;
    // cin >> str;
    // cout << gdict.search(str) << endl;

    //------------------------------
    ofstream fout ("namenum.out");
    ifstream fin  ("namenum.in");

    ostream& out = fout; //cout;
    istream& in  = fin;  //cin;

    string number;
    //out << "Enter a number :";
    in >> number;

    namenum(number);
    //namedict.output();

    namedict.getnames(number.size());
    int i = 0;
    for (auto& name : cow_names)
        if (gdict.search_word(name)) {
            out << name << endl;
            ++i;
        }

    if (!i)
        out << "NONE\n";

    return 0;
}

