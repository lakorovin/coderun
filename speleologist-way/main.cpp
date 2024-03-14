#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>
#include <queue>
#include <utility>
#include <cstdint>

typedef int nums_t;
typedef int nums_x;
typedef int nums_y;

struct Vertex {
    Vertex() : x(0), y(0), z(0) {};
    Vertex(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {};
    int x;
    int y;
    int z;
};

struct Field {
    int N;
    std::vector<std::vector<std::vector<nums_t> > > visited;
    Field(int _N) : N(_N), visited(_N, std::vector<std::vector<nums_t> >(_N, std::vector<nums_t>(_N, 0))) {}
    bool try_visit(const Vertex& v) {
        if (!in_bounds(v)) {
            return false;
        }
        if (visited[v.z][v.y][v.x]) {
            return false;
        }
        visited[v.z][v.y][v.x] = 1;
        return true;
    }
    bool in_bounds(const Vertex& v) const {
        return v.x >= 0 && v.y >= 0 && v.z >= 0 && v.x < N && v.y < N && v.z < N;
    }

    int size() const {
        return N;
    }

};


int bfs(Field& g, Vertex s) {
    std::vector< std::pair<Vertex, nums_t>> q;
    q.reserve(g.size() * 3);
    q.emplace_back(s, nums_t{0});
    size_t ind = 0;
    for (; ind < q.size(); ++ind) {
        const auto [v, level] = q[ind];
        if (v.z == 0) {
            return level;
        }
        for (int dz = -1; dz < 2; ++dz) {
            for (int dy = -1; dy < 2; ++dy) {
                for (int dx = -1; dx < 2; ++dx) {
                    if (std::abs(dz) + std::abs(dy) + std::abs(dx) != 1) {
                        continue;
                    }
                    int x = v.x + dx;
                    int y = v.y + dy;
                    int z = v.z + dz;
                    Vertex newV(x, y, z);
                    if (g.try_visit(newV)) {
                        if (z == 0) {
                            return level + 1;
                        }
                        q.emplace_back(newV, nums_t{ level + 1 });
                    }
                }
            }
        }
    }
    return -1;
}


void print_res(int x) {
    std::cout << x << std::endl;
}

Vertex read_map(Field& g) {
    Vertex s;
    for (int z = 0; z < g.size(); ++z) {
        std::string line;
        std::getline(std::cin, line);
        for (int y = 0; y < g.size(); ++y) {
            std::getline(std::cin, line);
            if (line.empty()) {
                --y;
                continue;
            }
            assert(line.size() == g.size());
            for (int x = 0; x < g.size(); ++x) {
                Vertex v(x, y, z);
                if (line[x] == '#') {
                    bool res = g.try_visit(v);
                    assert(res);
                }
                else if (line[x] == 'S') {
                    s = v;
                }
            }
        }

    }
    return s;
}

int main()
{
    int N;
    std::cin >> N;
    Field g(N);
    Vertex s = read_map(g);
    
    print_res(bfs(g, std::move(s)));
    return 0;
}
