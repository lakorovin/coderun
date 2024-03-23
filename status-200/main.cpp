// https://contest.yandex.ru/contest/36783/problems/C/

#include <iostream>
#include <vector>

using namespace std;

long long pairs(long long  el) {
    return el * (el - 1) / 2;
}

long long getNumberOfGoodPairs(int /*n*/, const vector<int>& numbers) {
    vector<int> module(200, 0);
    for (auto el : numbers) {
        ++module[el % 200];
    }
    long long res = 0;
    for (auto el : module) {
        res += pairs(el);
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
    vector<int> numbers = readList(n);
    cout << getNumberOfGoodPairs(n, numbers);
}
