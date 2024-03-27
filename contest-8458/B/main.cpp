// https://contest.yandex.ru/contest/8458/problems/B/

#include <iostream>
#include <vector>
#include <algorithm>

size_t maxLen(std::vector<int> arr, int to_find) {
    size_t res = 0;
    size_t cur = 0;
    
    for (int c : arr) {
        if (c == to_find) {
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
    std::cin >> x;
    return x;
}

std::vector<int> readList(int n) {
    std::vector<int> res(n);
    for (int i = 0; i < n; i++) {
        std::cin >> res[i];
    }
    return res;
}

int main() {
    int n = readInt();
    std::vector<int> arr = readList(n);
    std::cout << maxLen(std::move(arr), 1) << std::endl;
}
