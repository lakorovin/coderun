// https://contest.yandex.ru/contest/36783/problems/S/

#include <iostream>
#include <string>


using namespace std;

namespace {
    const string IPV4 = "IPv4";
    const string IPV6 = "IPv6";
    const string ERROR = "Error";
}

/**
 * return IPV4,IPV6, or ERROR
 */
string checkIpAddress(string ip) {
    // Your code here
    return ERROR;
}

int main() {
    string ipAddress;
    cin >> ipAddress;
    cout << checkIpAddress(std::move(ipAddress));
}
