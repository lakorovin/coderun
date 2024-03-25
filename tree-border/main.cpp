// https://contest.yandex.ru/contest/36783/problems/P/

#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

struct Vertex {
    int left;
    int right;

    Vertex(int left, int right) : left(left), right(right) {
    }
};

void fill_levels(vector<vector<int>>& levels, const vector<Vertex>& tree, int node, int level, unordered_set<int>& res) {
    if (node == -1) {
        return;
    }
    const Vertex& v = tree[node];
    if (v.left == -1 && v.right == -1) {
        res.insert(node);
    }
    if (levels.size() == level) {
        levels.push_back({ node });
    }
    else {
        levels[level].push_back(node);
    }

    fill_levels(levels, tree, v.left, level + 1, res);
    fill_levels(levels, tree, v.right, level + 1, res);
}

unordered_set<int> getTreeBorder(vector<Vertex> tree, int root) {
    vector<vector<int>> levels;
    unordered_set<int> res;
    fill_levels(levels, tree, root, 0, res);
    for (const auto& level : levels) {
        res.insert(level.front());
        res.insert(level.back());
    }
    return res;
}

void outputAnswer(const unordered_set<int>& treeBorder) {
    for (int elem : treeBorder) {
        cout << elem << " ";
    }
    cout << endl;
}

vector<Vertex> readTree(int n) {
    vector<Vertex> tree;
    for (int i = 0; i < n; i++) {
        int left, right;
        cin >> left >> right;
        tree.emplace_back(left, right);
    }
    return tree;
}

int main() {
    int n;
    cin >> n;
    int root;
    cin >> root;
    vector<Vertex> tree = readTree(n);
    outputAnswer(getTreeBorder(std::move(tree), root));
}
