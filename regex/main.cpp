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

bool rec_check(const string& stringToCheck, string& templateString, int sind, int tind) {
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
        return true;
    }
    if (tind >= templateString.size()) {
        return false;
    }
    char curT = templateString[tind];
    if (curT == '?') {
        return rec_check(stringToCheck, templateString, sind + 1, tind + 1);
    } else if (curT == '*') {
        for (int i = 0; i + sind < stringToCheck.size(); ++i) {
            bool maybe = rec_check(stringToCheck, templateString, sind + i, tind + 1);
            if (maybe) {
                return true;
            }
        }
        return false;
    }
    else {
        if (curT != stringToCheck[sind]) {
            return false;
        }
        return rec_check(stringToCheck, templateString, sind + 1, tind + 1);
    }
}

bool stringMatchesTemplate(string stringToCheck, string templateString) {
    string tm = normalizeTemplate(std::move(templateString));
    if (tm.size() > stringToCheck.size() * 2) {
        return false;
    }
    // your code goes here
    return rec_check(stringToCheck, tm, 0, 0);
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
