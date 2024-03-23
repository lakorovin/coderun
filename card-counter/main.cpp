// https://contest.yandex.ru/contest/36783/problems/B/

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;


long long getCardCount(int n, int k, const vector<long long> &cards) {
    assert(k <= n);
    assert(n == (int)cards.size());
    long long  sum = 0;
    
    for (size_t j = n-k; j < n; ++j) {
        sum += cards[j];
    }
    long long res = sum;
    int right = n-k;
    int left = 0;
    for (int i = 0; i < k; ++i) {
        sum -= cards[right];
        sum += cards[left];
        res = std::max(res, sum);
        ++left;
        ++right;
    }
    return res;
}

int readInt() {
    int x;
    cin >> x;
    return x;
}

vector<long long> readList(int n) {
    vector<long long> res(n);
    for (int i = 0; i < n; i++) {
        cin >> res[i];
    }
    return res;
}

int main() {
    int n = readInt();
    int k = readInt();
    vector<long long> cards = readList(n);
    cout << getCardCount(n, k, cards);
}
