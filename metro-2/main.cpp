#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>
#include <queue>
#include <utility>
#include <cstdint>

typedef int nums_s;
typedef int nums_bool;
typedef int nums_line;
typedef int nums_level;

struct Station {
    std::vector<nums_line> lines;
};

struct Line {
    std::vector<nums_s> stations;
};

struct Metro {
    Metro(int _N, int _M): N(_N), M(_M), lines(_M), stations(_N) {}
    const int N;
    const int M;
    const std::vector<nums_line>& getLines(nums_s v) const {
        return stations[v].lines;
    }

    const std::vector<nums_s>& getStations(nums_line l) const {
        return lines[l].stations;
    }

    std::vector <Line> lines;
    std::vector <Station> stations;
};



int bfs(Metro& g, nums_s start, nums_s finish) {
    if (start == finish) {
        return 0;
    }
    std::vector<nums_bool> visited(g.N, 0);
    std::vector<std::pair<nums_s, nums_level>> q;
    q.reserve(g.M);
    q.emplace_back(start, nums_level{-1});
    visited[start] = 1;
    size_t ind = 0;
    for (; ind < q.size(); ++ind) {
        const auto [v, level] = q[ind];
        for (nums_line line: g.getLines(v)) {
            for (nums_s s : g.getStations(line)) {
                if (!visited[s]) {
                    if (s == finish) {
                        return level + 1;
                    }
                    visited[s] = 1;
                    q.emplace_back(s, level + 1);
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
    for (int i = 0; i < size; ++i) {
        int x;
        std::cin >> x;
        x -= 1;
        l.stations.push_back(x);
        Station& s = g.stations[x];
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
