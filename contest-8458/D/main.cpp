// https://contest.yandex.ru/contest/8458/problems/D/

#include <iostream>
#include <vector>
#include <string>
#include <cassert>

// using namespace std;

int readInt() {
    int x;
    std::cin >> x;
    return x;
}

void outputAnswer(const std::vector<std::string>& sequences) {
    for (const std::string& sequence : sequences) {
        std::cout << sequence << std::endl;
    }
}

void generate_rec(std::string& cur, int openR, int n, std::vector<std::string>& res) {
    assert(openR >= 0);
    if (openR > n) {
        return;
    }
    if (n == 0) {
        res.push_back(cur);
        return;
    }
    {
        cur.push_back('(');
        generate_rec(cur, openR + 1, n - 1, res);
        cur.pop_back();
    }

    if (openR > 0) {
        cur.push_back(')');
        generate_rec(cur, openR - 1, n - 1, res);
        cur.pop_back();
    }
}

std::vector<std::string> generateSequences(int n) {
    std::vector<std::string> res;
    if (n == 0) {
        return res;
    }
    std::string tmp;
    tmp.reserve(2 * n);
    generate_rec(tmp, 0, 2 * n, res);
    return res;
}

int main() {
    outputAnswer(generateSequences(readInt()));
}
