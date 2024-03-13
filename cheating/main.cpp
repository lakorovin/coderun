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

void dfs_rec(const Graph& g, int id, std::vector<int>& visited, int color, bool& isBipartite) {
    if (visited[id]) {
        return;
    }
    visited[id] = color;
    for (int to : g.edges(id)) {
        if (visited[to] == 0) {
            dfs_rec(g, to, visited, 3 - color, isBipartite);
        }
        else if (visited[to] == color) {
            isBipartite = false;
        }
    }
}

bool dfs(const Graph& g) {
    std::vector<int> visited(g.size(), 0);
    bool isBipartite = true;
    for (int i = 0; i < g.size(); ++i) {
        dfs_rec(g, i, visited, 2, isBipartite);
        if (!isBipartite) {
            return false;
        }
    }
    
    return isBipartite;
}

void print_res(bool isBipartite) {
    if (isBipartite) {
        std::cout << "YES" << std::endl;
    }
    else {
        std::cout << "NO" << std::endl;
    }
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
