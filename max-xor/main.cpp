#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;


long long getMaxXOR(vector<long long> list) {
    if (list.empty()) {
        return 0;
    }
    std::sort(list.begin(), list.end());
    int left = 0;
    int right = (int)list.size() - 1;
    long long res = list[left] ^ list[right];
    while (left + 1 < right) {
        long long cand = list[right - 1];
        if ((cand ^ list[left]) > res) {
            res = cand ^ list[left];
            --right;
        }
        else {
            ++left;
            long long cand2 = list[right] ^ list[left];
            res = std::max(res, cand2);
        }
    }
    return res;
}

vector<long long> readList() {
    int n;
    cin >> n;
    vector<long long> res(n);
    for (int i = 0; i < n; i++) {
        cin >> res[i];
    }
    return res;
}

int main() {
    vector<long long> list = readList();
    cout << getMaxXOR(std::move(list));
}
