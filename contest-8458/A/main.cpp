#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;


int getCardCount(int , int , vector<int> ) {
    return 0;
}

void print_res(const std::vector<int>& x) {
    if (x.empty()) {
        std::cout << -1 << std::endl;
        return;
    }

    for (auto it = x.crbegin(); it != x.crend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
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
    // int n = readInt();
    // int k = readInt();
    // vector<int> cards = readList(n);
    std::string S, J;
    std::cin >> J;
    std::cin >> S;
    int juls[26] = {};
    for (auto c : J) {
        juls[c - 'a'] = 1;
    }
    int res = 0;
    for (auto c : S) {
        res += juls[c - 'a'];
    }
    std::cout << res;
    return 0;

}
