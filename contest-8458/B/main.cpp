// https://contest.yandex.ru/contest/8458/problems/B/

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;


size_t getCardCount(int n, vector<int> cards) {
    assert(n == (int)cards.size());
    size_t res = 0;
    size_t cur = 0;
    
    for (int c : cards) {
        if (c == 1) {
            ++cur;
        }
        else {
            cur = 0;
        }
        res = std::max(res, cur);
    }
    return res;
}

int readInt() {
    int x;
    cin >> x;
    return x;
}

vector<int> readList(int n) {
    vector<int> res(n);
    for (int i = 0; i < n; i++) {
        cin >> res[i];
    }
    return res;
}

int main() {
    int n = readInt();
    vector<int> cards = readList(n);
    cout << getCardCount(n, std::move(cards));
}
