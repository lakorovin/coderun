// https://contest.yandex.ru/contest/36783/problems/H/

#include <vector>
#include <iostream>
#include <queue>
#include <functional>

using namespace std;

long getEnergyForUnion(vector<long> stones) {
    if (stones.size() < 1) {
        return 0;
    }
    // std::priority_queue<long> minq2(std::greater<long>(), std::move(stones));
    std::priority_queue<long, std::vector<long>, std::greater<long>>
        minq2(stones.begin(), stones.end());
    long work = 0;
    while (minq2.size() > 1) {
        long l1 = minq2.top();
        minq2.pop();
        long l2 = minq2.top();
        work += l1 + l2;
        minq2.pop();
        minq2.push(l2 + l1);
    }
    return work;
}

vector<long> readList(int n) {
    vector<long> res(n);
    for (int i = 0; i < n; i++) {
        cin >> res[i];
    }
    return res;
}

int main() {
    int n;
    cin >> n;
    vector<long> stones = readList(n);
    cout << getEnergyForUnion(std::move(stones));
}
