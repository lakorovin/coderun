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

void fill_rec(vector<int>& visited, vector<vector<int>>& res, vector<int>& diag1, vector<int>& diag2, int line, int n, vector<int>& places) {
    if (line >= n) {
        res.push_back(places);
        return;
    }
    for (int i = 0; i < n; ++i) {
        if (visited[i]) {
            continue;
        }
        int v = i;
        int d1 = line + v;
        int d2 = n - 1 + line - v;
        if (diag1[d1]) {
            continue;
        }
        if (diag2[d2]) {
            continue;
        }
        places[line] = v;
        diag1[d1] = 1;
        diag2[d2] = 1;
        visited[i] = 1;
        fill_rec(visited, res, diag1, diag2, line + 1, n, places);
        visited[i] = 0;
        diag1[d1] = 0;
        diag2[d2] = 0;
    }
}

vector<vector<int>> getAllPeacefulCombinations(int n) {
    vector<vector<int>> res;
    vector<int> places(n);
    std::iota(places.begin(), places.end(), 0);
    vector<int> diag1(2 * n - 1);
    vector<int> diag2(2 * n - 1);
    vector<int> places2(n, -1);
    vector<int> visited(n, 0);
    fill_rec(visited, res, diag1, diag2, 0, n, places2);
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
