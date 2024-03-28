// https://contest.yandex.ru/contest/3/problems/C/

// D 11 13
// E Earth
// 

#include <iostream>

int readInt() {
    int x;
    std::cin >> x;
    return x;
}


int main() {
    int a = readInt();
    int b = readInt();
    long long res = 0;
    res += a;
    res += b;
    std::cout << res << std::endl;
    return 0;
}
