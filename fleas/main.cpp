#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <queue>
#include <utility>
#include <cstdint>

typedef int nums_t;

struct Graph {
    Graph(nums_t size) : N(size), map(size) {
        for (auto& v : map) {
            v.reserve(size);
        }
    };
    nums_t N;
    std::vector<std::vector<nums_t>> map;

    void add(nums_t x, nums_t y) {
        assert(x >= 0);
        assert(y >= 0);
        map[x].push_back(y);
        // map[y-1].insert(x-1);
    }

    const std::vector<nums_t>& edges(nums_t id) const {
        return map[id];
    }

    nums_t size() const {
        return N;
    }
};

std::vector<nums_t> getPath(const std::vector<nums_t>& from, nums_t start, nums_t finish) {
    std::vector<nums_t> path{ finish + 1 };
    for (nums_t v = from[finish]; v != start; v = from[v]) {
        path.push_back(v + 1);
    }
    path.push_back(start + 1);
    std::reverse(path.begin(), path.end());
    return path;
}

bool in_field(int x, int y, int N, int M) {
    if (x < 0 || y < 0) {
        return false;
    }
    if (x >= M) {
        return false;
    }
    if (y >= N) return false;
    return true;
}

std::vector<std::vector<nums_t>> bfs(int N, int M, int S, int T) {
    std::vector<std::vector<nums_t>> cost(N, std::vector<nums_t>(M, -1));
    std::vector< std::pair<std::pair<nums_t, nums_t>, nums_t>> q;

    std::vector<std::vector<nums_t>> visited(N, std::vector<nums_t>(M, 0));

    q.emplace_back(std::make_pair(T, S), nums_t{0});
    cost[S][T] = 0;
    visited[S][T] = 1;
    size_t ind = 0;
    for (; ind < q.size(); ++ind) {
        const auto [v, level] = q[ind];
        // std::cout << v.first << " " << v.second << " " << level << std::endl;
        assert(visited[v.second][v.first] == 1);
        for (int dy = -2; dy < 3; ++dy) {
            for (int dx = -2; dx < 3; ++dx) {
                if (dy == 0 || dx == 0 || std::abs(dy) == std::abs(dx)) {
                    continue;
                }
                int x = v.first + dx;
                int y = v.second + dy;
                if (in_field(x, y, N, M)) {
                    if (!visited[y][x]) {
                        visited[y][x] = 1;
                        cost[y][x] = level + 1;
                        q.emplace_back(std::make_pair(x, y), nums_t{ level + 1 });
                    }
                }
            }
        }
    }
    return cost;
}

long long sum_len(const std::vector<std::vector<nums_t>>& cost, std::vector<std::pair<nums_t, nums_t>>& q) {
    long long sum = 0;
    for (const auto [x, y] : q) {
        if (cost[y][x] < 0) {
            return -1;
        }
        sum += cost[y][x];
    }
    return sum;
}

void print_res(long long x) {
    std::cout << x << std::endl;
}

void read_fleas(std::vector<std::pair<nums_t, nums_t>>& q, int Q) {
    q.reserve(Q);
    for (nums_t i = 0; i < Q; ++i) {
        int x, y;
        std::cin >> y >> x;
        assert(x > 0);
        assert(y > 0);
        q.emplace_back(x-1, y-1);
    }
}

int main()
{
    int N, M, S, T, Q;
    std::cin >> N >> M >> S >> T >> Q;
    
    std::vector<std::pair<nums_t, nums_t>> q;
    read_fleas(q, Q);
    if (Q == 0) {
        std::cout << 0 << std::endl;
        return 0;
    }
    print_res(sum_len(bfs(N, M, S-1, T-1), q));
    return 0;
}
