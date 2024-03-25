// https://contest.yandex.ru/contest/36783/problems/K/

#include <vector>
#include <iostream>
#include <regex>
#include <string>

using namespace std;

bool stringMatchesTemplate2(string stringToCheck, string templateString) {
    string tm;
    tm.reserve(2 * templateString.size());
    for (char c : templateString) {
        if (c == '?') {
            tm.push_back('.');
        }
        else if (c == '*') {
            tm.push_back('.');
            tm.push_back('*');
        }
        else {
            tm.push_back(c);
        }
    }
    const std::regex txt_regex(std::move(tm));
    // your code goes here
    return std::regex_match(stringToCheck, txt_regex);
}

string normalizeTemplate(string templateString) {
    const int CHAR = 1;
    const int STAR = 2;
    int state = CHAR;

    string tm;
    tm.reserve(templateString.size());

    for (char c : templateString) {
        if (c == '*') {
            state = STAR;
        } else if (c == '?') {
            tm.push_back(c);
        }
        else {
            if (state == STAR) {
                tm.push_back('*');
            }
            state = CHAR;
            tm.push_back(c);
        }
    }
    if (state == STAR) {
        tm.push_back('*');
    }
    return tm;
}

bool rec_check(const string& stringToCheck, string& templateString, int sind, int tind, vector<vector<int>>& cache) {
    if (sind >= stringToCheck.size() && tind >= templateString.size()) {
        return true;
    }
    if (sind >= stringToCheck.size() && (tind + 1 == templateString.size()) && templateString[tind] == '*') {
        return true;
    }
    if (sind >= stringToCheck.size()) {
        return false;
    }
    if (tind + 1 == templateString.size() && templateString[tind] == '*') {
        cache[sind][tind] = 1;
        return true;
    }
    if (tind >= templateString.size()) {
        return false;
    }
    if (cache[sind][tind] > -1) {
        return cache[sind][tind] == 1;
    }
    char curT = templateString[tind];
    if (curT == '?') {
        return rec_check(stringToCheck, templateString, sind + 1, tind + 1, cache);
    } else if (curT == '*') {
        for (int i = 0; i + sind < stringToCheck.size(); ++i) {
            bool maybe = rec_check(stringToCheck, templateString, sind + i, tind + 1, cache);
            if (maybe) {
                cache[sind][tind] = 1;
                return true;
            }
        }
        cache[sind][tind] = 0;
        return false;
    }
    else {
        if (curT != stringToCheck[sind]) {
            cache[sind][tind] = 0;
            return false;
        }
        return rec_check(stringToCheck, templateString, sind + 1, tind + 1, cache);
    }
}

bool stringMatchesTemplate(string stringToCheck, string templateString) {
    string tm = normalizeTemplate(std::move(templateString));
    if (tm.size() > stringToCheck.size() * 2) {
        return false;
    }
    vector<vector<int>> cache(stringToCheck.size(), vector<int>(tm.size(), -1));
    return rec_check(stringToCheck, tm, 0, 0, cache);
}


int main() {
    string templateString;
    cin >> templateString;
    string stringToCheck;
    cin >> stringToCheck;

    if (stringMatchesTemplate(std::move(stringToCheck), std::move(templateString))) {
        cout << "YES" << endl;
    }
    else {
        cout << "NO" << endl;
    }
}
