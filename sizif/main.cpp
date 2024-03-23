// https://contest.yandex.ru/contest/36783/problems/H/

#include <vector>
#include <iostream>
#include <queue>

using namespace std;

long long getEnergyForUnion(vector<long long> stones) {
    if (stones.size() < 1) {
        return 0;
    }
    std::priority_queue minq2(stones.begin(), stones.end(), std::greater<long long>());
    long long work = 0;
    while (minq2.size() > 1) {
        long long l1 = minq2.top();
        minq2.pop();
        long long l2 = minq2.top();
        work += l1 + l2;
        minq2.pop();
        minq2.push(l2 + l1);
    }
    return work;
}

vector<long long> readList(int n) {
    vector<long long> res(n);
    for (int i = 0; i < n; i++) {
        cin >> res[i];
    }
    return res;
}

int main() {
    int n;
    cin >> n;
    vector<long long> stones = readList(n);
    cout << getEnergyForUnion(std::move(stones));
}
