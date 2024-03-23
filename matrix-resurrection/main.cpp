// https://contest.yandex.ru/contest/36783/problems/D/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

bool in_bounds(int x, int y, int n, int m) {
    return x >= 0 && y >= 0 && x < m && y < n;
}

int calc_dp(int y, int x, int n, int m, vector<vector<int>>& dp, const vector<vector<int>>& matrixs) {
    assert(in_bounds(x, y, n, m));
    if (dp[y][x] > 0) {
        return dp[y][x];
    }
    for (int dy = -1; dy < 2; ++dy) {
        for (int dx = -1; dx < 2; ++dx) {
            if (abs(dx) + abs(dy) != 1) {
                continue;
            }
            int xN = x + dx;
            int yN = y + dy;
            if (!in_bounds(xN, yN, n, m)) {
                continue;
            }
            int curr = matrixs[y][x];
            int next = matrixs[yN][xN];
            if (next > curr) {
                dp[y][x] = std::max(dp[y][x], calc_dp(yN, xN, n, m, dp, matrixs) + 1);
            }
        }
    }
    if (dp[y][x] == 0) {
        dp[y][x] = 1;
    }
    return dp[y][x];
}

int getLongestIncreasingPath(int n, int m, const vector<vector<int>>& matrixs) {
    vector<vector<int>> dp(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            calc_dp(i, j, n, m, dp, matrixs);
        }
    }
    int res = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            res = std::max(res, dp[i][j]);
        }
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

vector<vector<int>> readMatrix(int n, int m) {
    vector<vector<int>> matrix(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        matrix[i] = readList(m);
    }
    return matrix;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> matrix = readMatrix(n, m);
    cout << getLongestIncreasingPath(n, m, matrix);
}
