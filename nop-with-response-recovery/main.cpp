#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<std::vector<int>> fill_dyn_matrix(const std::vector<int>& x, const std::vector<int>& y) {
    std::vector<std::vector<int>> L(x.size() + 1, std::vector<int>(y.size() + 1, 0));
    for (size_t x_i = 0; x_i < x.size(); ++x_i) {
        for (size_t y_i = 0; y_i < y.size(); ++y_i) {
            if (x[x_i] == y[y_i]) {
                L[x_i + 1][y_i + 1] = L[x_i][y_i] + 1;
            }
            else {
                L[x_i + 1][y_i + 1] = std::max(L[x_i + 1][y_i], L[x_i][y_i + 1]);
            }
        }
    }
    return L;
}

std::vector<int> scan_vec(int n) {
    std::vector<int> x;
    x.reserve(n);
    for (int i = 0; i < n; ++i) {
        int el;
        std::cin >> el;
        x.push_back(el);
    }
    return x;
}

std::vector<int> LCS_DYN(const std::vector<int>& x, const std::vector<int>& y) {
    if (x.empty() || y.empty()) {
        return {};
    }

    std::vector<std::vector<int>> L = fill_dyn_matrix(x, y);
    std::vector<int> LCS;
    LCS.reserve(std::min(x.size(), y.size()));
    size_t x_i = x.size();
    size_t y_i = y.size();
    while (x_i > 0 && y_i > 0) {
        if (x[x_i - 1] == y[y_i - 1]) {
            LCS.push_back(x[x_i - 1]);
            x_i -= 1;
            y_i -= 1;
        }
        else if (L[x_i - 1][y_i] > L[x_i][y_i - 1]) {
            x_i -= 1;
        }
        else {
            y_i -= 1;
        }
    }
    std::reverse(LCS.begin(), LCS.end());
    return LCS;
}

void print_res(const std::vector<int> x) {
    for (int el : x) {
        std::cout << el << " ";
    }
    std::cout << std::endl;
}

int main()
{
    int N, M;
    std::cin >> N;
    std::vector<int> x = scan_vec(N);
    std::cin >> M;
    std::vector<int> y = scan_vec(M);
    auto ans = LCS_DYN(x, y);
    print_res(ans);
    return 0;
}
