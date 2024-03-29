// https://contest.yandex.ru/contest/36783/problems/F/

#include <iostream>
#include <stack>
#include <cctype>
#include <string>

std::string convertToGoodString(std::string probablyBadString) {
    std::stack<unsigned char> st;
    for (unsigned char c : probablyBadString) {
        if (!st.empty()) {
            unsigned char sCh = st.top();
            if (sCh != c && std::tolower(sCh) == std::tolower(c)) {
                st.pop();
            	continue;
            }            
        }
    	st.push(c);
    }
    size_t size = st.size();
    std::string s(size, ' ');
    while (!st.empty()) {
        s[--size] = st.top();
        st.pop();
    }
    return s;
}

int main() {
    std::string probablyBadString;
    std::cin >> probablyBadString;
    std::cout << convertToGoodString(std::move(probablyBadString)) << std::endl;
    return 0;
}
