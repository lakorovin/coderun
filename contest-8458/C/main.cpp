// https://contest.yandex.ru/contest/36783/problems/C/

#include <iostream>

int readInt() {
    int x;
    std::cin >> x;
    return x;
}

int main() {
    int n = readInt();
    if (n == 0) {
        return 0;
    }
    int prev = readInt();
    std::cout << prev << std::endl;
    for (int i = 1; i < n; ++i) {
        int cur = readInt();
        if (cur > prev) {
            std::cout << cur << std::endl;
        }
        prev = cur;
    }
    return 0;
}
