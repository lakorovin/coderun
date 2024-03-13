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


std::vector<nums_t> bfs(const Graph& g, nums_t start, nums_t finish) {
    std::vector<std::pair<nums_t, nums_t>> q;
    q.reserve(g.size());
    std::vector<int> visited((size_t) g.size());
    std::vector<nums_t> from(g.size(), -1);

    q.emplace_back(start, nums_t{0});
    size_t ind = 0;
    for (; ind < q.size(); ++ind) {
        const auto [v, level] = q[ind];
        if (finish == v) {
            assert(false);
            return getPath(from, start, finish);
        }
        // assert(visited[v] == 0);
        visited[v] =  1;
        for (nums_t to : g.edges(v)) {
            if (!visited[to]) {
                visited[to] = 1;
                from[to] = v;
                if (finish == to) {
                    return getPath(from, start, finish);
                }
                q.emplace_back(to, nums_t{ level + 1 });
            }
        }
    }
    return {};
}

void print_res(const std::vector<nums_t>& x) {
    if (x.empty()) {
        std::cout << -1 << std::endl;
        return;
    }
    std::cout << x.size() - 1 << std::endl;
    if (x.size() < 2) {
        assert(false);
        return;
    }

    for (auto it = x.cbegin(); it != x.cend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void read_as_matrix(Graph& g) {
    for (nums_t i = 0; i < g.size(); ++i) {
        for (nums_t j = 0; j < g.size(); ++j) {
            int x;
            std::cin >> x;
            if (x > 0) {
                g.add(i, j);
            }
        }
    }
}

int main()
{
    int N;
    std::cin >> N;
    Graph g(static_cast<nums_t>(N));
    read_as_matrix(g);
    int start, finish;
    std::cin >> start >> finish;
    if (start == finish) {
        std::cout << 0 << std::endl;
        // std::cout << start << std::endl;
        return 0;
    }
    assert(start > 0);
    assert(finish > 0);
    assert(finish != start);
    print_res(bfs(g, static_cast<nums_t>( start - 1 ), static_cast<nums_t>(finish - 1 )));
    return 0;
}
