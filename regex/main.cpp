// https://contest.yandex.ru/contest/36783/problems/K/

#include <vector>
#include <iostream>
#include <regex>
#include <string>

using namespace std;

bool stringMatchesTemplate(string stringToCheck, string templateString) {
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
