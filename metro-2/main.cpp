#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>
#include <queue>
#include <utility>
#include <cstdint>

typedef int nums_t;
typedef int nums_line;
typedef int nums_x;
typedef int nums_y;

struct Station {
    Station() : v(-1) {}
    Station(nums_t _v) : v(_v) {}
    nums_t v;
    std::vector<nums_line> lines;
};

struct Line {
    nums_line num;
    std::vector<nums_line> stations;
};

struct Metro {
    Metro() : N(0), M(0) {}
    Metro(int _N, int _M): N(_N), M(_M), lines(_M), stations(_N) {}
    int N;
    int M;
    std::vector <Line> lines;
    std::vector <Station> stations;
};



int bfs(Metro& g, nums_t start, nums_t finish) {
    if (start == finish) {
        return 0;
    }
    std::vector<nums_t> visited(g.N, 0);
    std::vector< std::pair<Station, nums_t>> q;
    q.reserve(g.M);
    q.emplace_back(g.stations[start], nums_t{-1});
    size_t ind = 0;
    for (; ind < q.size(); ++ind) {
        const auto [v, level] = q[ind];
        if (v.v == finish) {
            return level;
        }
        visited[v.v] = 1;
        for (nums_line line: v.lines) {
            Line l = g.lines[line];
            for (nums_t s : l.stations) {
                if (!visited[s]) {
                    if (s == finish) {
                        return level + 1;
                    }
                    visited[s] = 1;
                    q.emplace_back(g.stations[s], level + 1);
                }
            }
        }
    }
    return -1;
}


void print_res(int x) {
    std::cout << x << std::endl;
}

void read_line(Metro& g, nums_line line) {
    int size;
    std::cin >> size;
    Line& l = g.lines[line];
    l.num = line;
    for (int i = 0; i < size; ++i) {
        int x;
        std::cin >> x;
        x -= 1;
        l.stations.push_back(x);
        Station& s = g.stations[x];
        s.v = x;
        s.lines.push_back(line);        
    }
}

void read_map(Metro& g) {
    for (nums_line line = 0; line < g.M; ++line) {
        read_line(g, line);
    }
}

int main()
{
    int N, M;
    std::cin >> N >> M;
    Metro g(N, M);
    read_map(g);
    int A, B;
    std::cin >> A >> B;
    print_res(bfs(g, A - 1, B - 1));
    return 0;
}
