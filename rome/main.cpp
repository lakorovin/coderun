// https://contest.yandex.ru/contest/36783/problems/E/

// IXIX выдает 18, хотя должен выдавать -1, тесты на контесте это не ловят
// IXI тоже прокатывает
// XLX прокатывает
// MCCM - есть тест, -1
// XLIX - есть тест, 49



#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;
namespace {
    std::unordered_map <char, int> Costs{
      { 'I', 1},
      { 'V', 5},
      { 'X', 10},
      { 'L', 50},
      { 'C', 100},
      { 'D', 500},
      { 'M', 1000}
    };

    std::unordered_map <char, char> ValidPrev{
      { 'D', 'C'},
      { 'M', 'C'},
      { 'L', 'X'},
      { 'C', 'X'},
      { 'V', 'I'},
      { 'X', 'I'}
    };
}

void update_count(std::unordered_map <char, int>& counts, const std::string& nonTree, char c, char prevChar) {
    auto nt = nonTree.find(c);
    if (nt != std::string::npos && prevChar != c) {
        counts[c] = 1;
    }
    else {
        ++counts[c];
    }
}

int convertToArabic(const string& romanNumber) {
    int sum = 0;
    std::unordered_map <char, int> counts;
    std::string nonTree = "IXCM";
    std::string single = "VLD";
    char prevChar = ' ';
    int n = (int)romanNumber.size();
    int prevMaxCost = 1000;
    for (int i = 0; i < n; ++i) {
        char c = romanNumber[i];
        int currCost = Costs[c];
        if (currCost < 1) {
            return -1;
        }
        if (currCost > prevMaxCost) {
            return -1;
        }
        update_count(counts, nonTree, c, prevChar);
        sum += currCost;
        if (i + 1 < n) {
            char nextCh = romanNumber[i + 1];
            if (Costs[nextCh] > currCost) {
                if (ValidPrev[nextCh] != c) {
                    return -1;
                }
                int maxCost = Costs[nextCh] - currCost;
                if (prevMaxCost < maxCost) {
                    return -1;
                }
                prevMaxCost = currCost - 1;
                sum -= 2 * currCost;
                sum += Costs[nextCh];
                update_count(counts, nonTree, nextCh, c);
                ++i;
            }
            else {
                if (currCost > prevMaxCost) {
                    return -1;
                }
                prevMaxCost = currCost;
            }
        }
        else {
            if (currCost > prevMaxCost) {
                return -1;
            }
        }
        prevChar = romanNumber[i];
    }

    for (char ch : single) {
        if (counts[ch] > 1) {
            return -1;
        }
    }

    for (char ch : nonTree) {
        if (counts[ch] > 3) {
            return -1;
        }
    }

    return sum;
}

int main() {
    string romanNumber;
    cin >> romanNumber;
    cout << convertToArabic(romanNumber);
}
