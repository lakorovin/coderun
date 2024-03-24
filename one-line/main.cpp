// https://contest.yandex.ru/contest/36783/problems/Q/

#include <iostream>
#include <vector>

using namespace std;

struct Point {
    long long x;
    long long y;

    Point(long long _x, long long _y) : x(_x), y(_y) {
    }
};

bool collinear(Point p1, Point p2, Point p3) {
    // x1y2 - x2y1 == 0
    long long x1 = p2.x - p1.x;
    long long x2 = p3.x - p1.x;
    long long y1 = p2.y - p1.y;
    long long y2 = p3.y - p1.y;
    return x1 * y2 == x2 * y1;
}


bool isOnOneLine(vector<Point> points) {
    if (points.size() < 3) {
        return true;
    }
    Point fp = points[0];
    Point sp = points[1];
    int ind = 2;
    while (ind < points.size()) {
        if (sp.x != fp.x || sp.y != fp.y) {
            break;
        }
        sp = points[ind];
        ++ind;
    }
    while (ind < points.size()) {
        if (!collinear(fp, sp, points[ind])) {
            return false;
        }
        ++ind;
    }

    return true;
}

int main() {
    int n;
    cin >> n;
    vector<Point> points;
    points.reserve(n);
    for (int i = 0; i < n; i++) {
        long long x, y;
        cin >> x >> y;
        points.emplace_back(x, y);
    }
    if (isOnOneLine(std::move(points))) {
        cout << "YES";
    }
    else {
        cout << "NO";
    }
}
