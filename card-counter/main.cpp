// https://contest.yandex.ru/contest/36783/problems/B/

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;


int getCardCount(int n, int k, vector<int> cards) {
    assert(k <= n);
    assert(n == (int)cards.size());
    int sum = 0;

    for (size_t j = n - k; j < n; ++j) {
        sum += cards[j];
    }
    int res = sum;
    int right = n - k;
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

vector<int> readList(int n) {
    vector<int> res(n);
    for (int i = 0; i < n; i++) {
        cin >> res[i];
    }
    return res;
}

int main() {
    int n = readInt();
    int k = readInt();
    vector<int> cards = readList(n);
    cout << getCardCount(n, k, std::move(cards));
}
