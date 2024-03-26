// https://contest.yandex.ru/contest/36783/problems/U/

#include <iostream>
#include <vector>
#include <string>
#include <cassert>

using namespace std;

void outputAnswer(const vector<string>& sequences) {
    for (const string& sequence : sequences) {
        cout << sequence << std::endl;
    }
}

void generate_rec(string& cur, int openR, int openS, int n, vector<string>& res) {
    assert(openR >= 0);
    assert(openS >= 0);
    if (openR + openS > n) {
        return;
    }
    if (n == 0) {
        res.push_back(cur);
        return;
    }
    if (openS == 0) {
        cur.push_back('(');
        generate_rec(cur, openR + 1, openS, n - 1, res);
        cur.pop_back();
    }
    cur.push_back('[');
    generate_rec(cur, openR, openS + 1, n - 1, res);
    cur.pop_back();
    
    if (openS > 0) {
        cur.push_back(']');
        generate_rec(cur, openR, openS - 1, n - 1, res);
        cur.pop_back();        
    }
    
    if (openR > 0 && openS == 0) {
        cur.push_back(')');
        generate_rec(cur, openR - 1, openS, n - 1, res);
        cur.pop_back();        
    }    
}

vector<string> generateSequences(int n) {
    vector<string> res;
    if (n < 2 || n%2 == 1) {
        return res;
    }
    string tmp;
    tmp.reserve(n);
    generate_rec(tmp, 0, 0, n, res);
    return res;
}

int main() {
    int n;
    cin >> n;
    outputAnswer(generateSequences(n));
}
