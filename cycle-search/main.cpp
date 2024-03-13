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
        assert(x >= 0);
        assert(y >= 0);
        map[x].insert(y);
        // map[y-1].insert(x-1);
    }

    std::unordered_set<int> edges(int id) const {
        return map[id];
    }

    int size() const {
        return N;
    }
};

std::vector<int> getCycle(const std::vector<int>& from, int lastVert) {
    std::vector<int> c = { lastVert + 1 };
    for (int v = from[lastVert]; v != lastVert; v = from[v]) {
        c.push_back(v + 1);
    }
    return c;
}

void dfs_rec(const Graph& g, int id, std::vector<int>& visited, std::vector<int>& from, std::vector<int>& cycle) {
    if (visited[id] || !cycle.empty()) {
        return;
    }
    visited[id] = 1;
    int fr = from[id];
    for (int to : g.edges(id)) {
        if (to == fr) {
            continue;
        }
        if (visited[to] == 0) {
            from[to] = id;
            dfs_rec(g, to, visited, from, cycle);
            if (!cycle.empty()) {
                return;
            }
        }
        else if (visited[to] == 1) {
            from[to] = id;
            cycle = getCycle(from, to);
            return;
        }
    }
    visited[id] = 2;
}

std::vector<int> dfs(const Graph& g) {
    std::vector<int> visited(g.size(), 0);
    std::vector<int> from(g.size(), -1);
    std::vector<int> cycle;
    for (int i = 0; i < g.size(); ++i) {
        dfs_rec(g, i, visited, from, cycle);
        if (!cycle.empty()) {
            return cycle;
        }
    }    
    return cycle;
}

void print_res(const std::vector<int>& x) {
    if (x.empty()) {
        std::cout << "NO" << std::endl;
        return;
    }

    std::cout << "YES" << std::endl;
    std::cout << x.size() << std::endl;
    for (auto it = x.cbegin(); it != x.cend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void read_as_matrix(Graph& g) {
    for (int i = 0; i < g.size(); ++i) {
        for (int j = 0; j < g.size(); ++j) {
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
    Graph g(N);
    read_as_matrix(g);
    print_res(dfs(g));
    return 0;
}
