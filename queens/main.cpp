// https://contest.yandex.ru/contest/36783/problems/J/

#include <vector>
#include <iostream>
#include <numeric>
#include <algorithm>

using namespace std;

void printArray(const vector<int>& combination) {
    for (int elem : combination) {
        cout << elem + 1 << " ";
    }
    cout << endl;
}

bool is_good(const vector<int>& places) {
    int n = (int)places.size();
    vector<int> diag1(2*n-1);
    vector<int> diag2(2 * n - 1);
    for (int i = 0; i < n; ++i) {
        int d1 = i + places[i];
        int d2 = n - 1 + i - places[i];
        if (diag1[d1]) {
            return false;
        }
        if (diag2[d2]) {
            return false;
        }
        diag1[d1] = 1;
        diag2[d2] = 1;
    }
    return true;
}

vector<vector<int>> getAllPeacefulCombinations(int n) {
    vector<vector<int>> res;
    vector<int> places(n);
    std::iota(places.begin(), places.end(), 0);
    do {
        if (is_good(places)) {
            res.push_back(places);
        }
    }
    while (std::next_permutation(places.begin(), places.end()));
    return res;
}


void outputAnswer(const vector<vector<int>>& possibleCombinations) {
    cout << possibleCombinations.size() << endl;
    for (const vector<int>& combination : possibleCombinations) {
        printArray(combination);
    }
}

int main() {
    int n;
    cin >> n;
    vector<vector<int>> possibleCombinations = getAllPeacefulCombinations(n);
    outputAnswer(possibleCombinations);
}
