// https://contest.yandex.ru/contest/36783/problems/S/

#include <iostream>
#include <string>
#include <algorithm>


using namespace std;

namespace {
    const string IPV4 = "IPv4";
    const string IPV6 = "IPv6";
    const string ERROR = "Error";
}

bool is_ip4(const string& ip) {
    if (ip.size() > 3 * 4 + 3) {
        return false;
    }
    if (std::count(ip.begin(), ip.end(), '.') != 3) {
        return false;
    }
    const int DOT = 1;
    const int INT_PARSE = 0;
    const int LEADING_ZEROES = 2;
    int state = DOT;
    int curD = 0;
    for (char c : ip) {
        if (c == '.') {
            if (state == DOT) {
                return false;
            }
            state = DOT;
            curD = 0;
        }
        else if (c <= '9' && c >= '0') {
            if (state == LEADING_ZEROES) {
                return false;
            }
            if (c == '0') {
                if (state == DOT) {
                    state = LEADING_ZEROES;
                }
            }
            else {
                state = INT_PARSE;
            }
            int diff = c - '0';
            curD *= 10;
            curD += diff;
            if (curD > 255) {
                return false;
            }
        }
        else {
            return false;
        }
    }
    return state != DOT;
}

bool is_ip6(const string& ip) {
    if (ip.size() > 8 * 4 + 7) {
        return false;
    }
    if (std::count(ip.begin(), ip.end(), ':') != 7) {
        return false;
    }

    const int SEMICOLON = 1;
    const int INT_PARSE = 0;
    int state = SEMICOLON;
    int curlen = 0;
    for (char c : ip) {
        if (c == ':') {
            if (state == SEMICOLON) {
                return false;
            }
            state = SEMICOLON;
            curlen = 0;
        }
        else if ((c <= '9' && c >= '0') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F')) {
            state = INT_PARSE;
            ++curlen;
            if (curlen > 4) {
                return false;
            }
        }
        else {
            return false;
        }
    }
    return state != SEMICOLON;
}

/**
 * return IPV4,IPV6, or ERROR
 */
string checkIpAddress(string ip) {
    if (ip.size() < 7) {
        return ERROR;
    }
    for (int i = 0; i < 5; ++i) {
        if (ip[i] == '.') {
            if (is_ip4(ip)) {
                return IPV4;
            }
            return ERROR;
        }
        if (ip[i] == ':') {
            if (is_ip6(ip)) {
                return IPV6;
            }
            return ERROR;
        }
    }
    return ERROR;
}

int main() {
    string ipAddress;
    cin >> ipAddress;
    cout << checkIpAddress(std::move(ipAddress));
}
