// https://contest.yandex.ru/contest/3/problems/B/

#include <fstream>

int readInt(std::ifstream& f) {
    int x;
    f >> x;
    return x;
}


int main() {
    std::ifstream in("input.txt");
    int a = readInt(in);
    int b = readInt(in);
    long long res = 0;
    res += a;
    res += b;
    std::ofstream out("output.txt");
    out << res << std::endl;
    return 0;
}
