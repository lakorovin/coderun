// https://contest.yandex.ru/contest/8458/problems/E/

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

std::vector<int> str_to_vec(const std::string& s) {
    std::vector<int> res(26);
    for (unsigned char c : s) {
        ++res[c - 'a'];
    }
    return res;
}

bool is_equal(const std::vector<int>& a, const std::vector<int>& b) {
    assert(a.size() == 26);
    assert(b.size() == 26);
    for (int i = 0; i < 26; ++i) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    std::string s1, s2;
    std::cin >> s1;
    std::cin >> s2;
    if (is_equal(str_to_vec(s1), str_to_vec(s2))) {
        std::cout << 1 << std::endl;
    }
    else {
        std::cout << 0 << std::endl;
    }
    return 0;
}
