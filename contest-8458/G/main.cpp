// https://contest.yandex.ru/contest/8458/problems/G/

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <queue>
#include <utility>


struct Point {
    int x;
    int y;

    Point(int _x, int _y) : x(_x), y(_y) {
    }
};

long long dist(const Point& p1, const Point& p2) {
    return std::abs((long long)p1.x - p2.x) + std::abs((long long)p1.y - p2.y);
}

std::vector<Point> readPoints(int n) {
    std::vector<Point> points;
    points.reserve(n);
    for (int i = 0; i < n; i++) {
        int x, y;
        std::cin >> x >> y;
        points.emplace_back(x, y);
    }
    return points;
}

int bfs(std::vector<Point> points, int from, int to, int maxDist) {
    std::queue<std::pair<int, int>> q;
    std::vector<int> visited(points.size());
    visited[from] = 1;
    q.push({ from, 0 });
    for (; !q.empty(); q.pop()) {
        auto [v, level] = q.front();
        for (int i = 0; i < (int)points.size(); ++i) {
            if (visited[i]) {
                continue;
            }
            const Point& cand = points[i];
            if (dist(cand, points[v]) <= maxDist) {
                if (i == to) {
                    return level + 1;
                }
                visited[i] = 1;
                q.push({ i, level + 1 });
            }
        }
    }
    return -1;
}

int readInt() {
    int x;
    std::cin >> x;
    return x;
}


int main() {
    int n = readInt();
    std::vector<Point> points = readPoints(n);
    int maxDist = readInt();
    int from = readInt();
    int to = readInt();
    std::cout << bfs(std::move(points), from - 1, to - 1, maxDist) << std::endl;
    return 0;
}
