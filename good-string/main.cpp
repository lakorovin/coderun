// https://contest.yandex.ru/contest/36783/problems/F/

#include <iostream>
#include <stack>
#include <algorithm>

using namespace std;


string convertToGoodString(const string& probablyBadString) {
    std::stack<char> st;
    for (char c : probablyBadString) {
        if (st.empty()) {
            st.push(c);
        }
        else {
            char sCh = st.top();
            if (sCh != c && tolower(sCh) == tolower(c)) {
                st.pop();
            }
            else {
                st.push(c);
            }
        }
    }
    size_t size = st.size();
    string s(size, ' ');
    while (!st.empty()) {
        s[--size] = st.top();
        st.pop();
    }
    return s;
}

int main() {
    string probablyBadString;
    cin >> probablyBadString;
    cout << convertToGoodString(probablyBadString);
}
