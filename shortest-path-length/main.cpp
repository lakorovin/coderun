#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <queue>
#include <utility>
#include <cstdint>

typedef std::int8_t nums_t;

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


int bfs(const Graph& g, nums_t start, nums_t finish) {
    std::vector<std::pair<nums_t, nums_t>> q;
    q.reserve(g.size());
    std::vector<nums_t> visited((size_t) g.size());

    q.emplace_back(start, nums_t{0});
    size_t ind = 0;
    for (; ind < q.size(); ++ind) {
        std::pair<nums_t, nums_t> v = q[ind];
        if (finish == v.first) {
            return static_cast<int>(v.second);
        }
        visited[v.first] = nums_t{ 1 };
        for (nums_t to : g.edges(v.first)) {
            if (finish == v.first) {
                return static_cast<int>(v.second + 1);
            }
            if (!visited[to]) {
                q.emplace_back(to, nums_t{ v.second + 1 });
            }
        }
    }
    return -1;
}

void print_res(int x) {
    std::cout << x << std::endl;
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
    print_res(bfs(g, static_cast<nums_t>( start - 1 ), static_cast<nums_t>(finish - 1 )));
    return 0;
}
