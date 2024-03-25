// https://contest.yandex.ru/contest/36783/problems/R/

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

namespace {
    const int WIN = 1;
    const int LOOSE = 0;
    const int NOT_SET = -3;
    vector<int> dp(10000 + 1, NOT_SET);
}

void init() {
    dp[1] = LOOSE;
    // dp[2] = WIN;
    // dp[3] = LOOSE;
}

bool fill_rec(int n) {
    assert(n > 0);
    if (dp[n] != NOT_SET) {
        return dp[n] == WIN;
    }
    for (int d = 1; d <= n/2; ++d) {
        if (n % d != 0) {
            continue;
        }
        bool other = fill_rec(n - d);
        if (!other) {
            dp[n] = WIN;
            return true;
        }
    }
    dp[n] = LOOSE;
    return false;
}

bool isPashaWins(int n) {
    int ans = dp[n];
    if (ans != NOT_SET) {
        return ans == WIN;
    }
    assert(false);
    return true;
}

int main() {
    int n;
    cin >> n;
    init();
    fill_rec(n);
    if (isPashaWins(n)) {
        cout << "Pasha";
    }
    else {
        cout << "Mark";
    }
}
