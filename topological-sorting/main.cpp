#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>
#include <unordered_map>
#include <unordered_set>
#include <set>

struct Graph {
    Graph(int size) : N(size), map(size) {};
    int N;
    std::vector<std::unordered_set<int>> map;

    void add(int x, int y) {
        assert(x > 0);
        assert(y > 0);
        map[x-1].insert(y-1);
        // map[y-1].insert(x-1);
    }

    std::unordered_set<int> edges(int id) const {
        return map[id];
    }

    int size() const {
        return N;
    }
};

void dfs_rec(const Graph& g, int id, std::vector<int>& visited, std::vector<int>& order, bool& has_cycle) {
    if (visited[id] || has_cycle) {
        return;
    }
    visited[id] = 1;
    for (int to : g.edges(id)) {
        if (visited[to] == 0) {
            dfs_rec(g, to, visited, order, has_cycle);
        }
        else if (visited[to] == 1) {
            has_cycle = true;
            return;
        }
    }
    order.push_back(id + 1);
    visited[id] = 2;
}

std::vector<int> dfs(const Graph& g) {
    std::vector<int> visited(g.size(), 0);
    std::vector<int> order;
    bool has_cycle = false;
    order.reserve(g.size());
    for (int i = 0; i < g.size(); ++i) {
        dfs_rec(g, i, visited, order, has_cycle);
        if (has_cycle) {
            return {};
        }
    }    
    assert(order.size() == g.size());
    return order;
}

void print_res(const std::vector<int>& x) {
    if (x.empty()) {
        std::cout << -1 << std::endl;
        return;
    }

    for (auto it = x.crbegin(); it != x.crend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

int main()
{
    int N, M;
    std::cin >> N >> M;
    Graph g(N);
    for (int i = 0; i < M; ++i) {
        int x, y;
        std::cin >> x >> y;
        g.add(x, y);

    }
    print_res(dfs(g));
    return 0;
}
