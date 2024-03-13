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
        map[y-1].insert(x-1);
    }

    std::unordered_set<int> edges(int id) const {
        return map[id];
    }

    int size() const {
        return N;
    }
};

void dfs_rec(const Graph& g, int id, std::vector<int>& visited) {
    if (visited[id]) {
        return;
    }
    visited[id] = 1;
    for (int el : g.edges(id)) {
        dfs_rec(g, el, visited);
    }
}

std::set<int> dfs(const Graph& g, int id) {
    std::vector<int> visited(g.size(), 0);
    dfs_rec(g, id, visited);
    std::set<int> clik;
    for (int i = 0; i < visited.size(); ++i) {
        if (visited[i]) {
            clik.insert(i + 1);
        }
    }
    return clik;
}

void print_res(const std::set<int>& x) {
    std::cout << x.size() << std::endl;
    for (int el : x) {
        std::cout << el << " ";
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
    std::set<int> ans = dfs(g, 0);
    print_res(ans);
    return 0;
}
