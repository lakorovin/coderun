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

void dfs_rec(const Graph& g, int id, std::vector<int>& visited, std::set<int>& clik) {
    if (visited[id]) {
        return;
    }
    visited[id] = 1;
    clik.insert(id + 1);
    for (int el : g.edges(id)) {
        dfs_rec(g, el, visited, clik);
    }
}

std::vector< std::set<int> > dfs(const Graph& g) {
    std::vector<int> visited(g.size(), 0);
    std::vector< std::set<int> > ans;
    for (int i = 0; i < g.size(); ++i) {
        std::set<int> clik;
        dfs_rec(g, i, visited, clik);
        if (!clik.empty()) {
            ans.push_back(std::move(clik));
        }
    }
    
    return ans;
}

void print_res(const std::vector< std::set<int> >& x) {
    std::cout << x.size() << std::endl;

    for (const auto& click : x) {
        std::cout << click.size() << std::endl;
        for (auto el : click) {
            std::cout << el << " ";
        }
        std::cout << std::endl;
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
