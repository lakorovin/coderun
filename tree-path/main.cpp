// https://contest.yandex.ru/contest/36783/problems/G/

#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

struct Vertex {
    int w;
    int p;

    Vertex(int _w, int _p) : w(_w), p(_p) {}
};

std::pair<int, vector<vector<long>>> createReverseTree(const vector<Vertex>& treeOrig) {
    int root = 0;
    int n = (int)treeOrig.size();
    vector<vector<long>> reverseTree(n);

    for (int i = 0; i < n; i++) {
        int parent = treeOrig[i].p;

        if (parent < 0)
        {
            root = i;
            continue;
        }
        reverseTree[parent].push_back(i);
    }

    return { root, reverseTree };
}


// Функция для рекурсивного обхода дерева от корня до листьев
long traverseTree(
    const vector<vector<long>>& reverseTree,
    const vector<Vertex>& treeOrig,
    long node,
    long k,
    long sum_so_far,
    std::unordered_map<long, long>& map
)
{
    const Vertex& curVertex = treeOrig.at(node);
    sum_so_far += curVertex.w;


    // получаем количество путей с суммой `k`, которые заканчиваются текущим узлом
    long count = map[sum_so_far - k];
    map[sum_so_far] += 1;

    for (long child : reverseTree[node])
    {
        count += traverseTree(reverseTree, treeOrig, child, k, sum_so_far, map);
    }

    map[sum_so_far] -= 1;

    return count;
}

long getNumberOfUpgoingPaths(const vector<Vertex>& treeOrig, int x) {
    auto [root, tree] = createReverseTree(treeOrig);
    unordered_map<long, long> map;
    map[0] = 1;
    long sum_so_far = 0;
    return traverseTree(tree, treeOrig, root, x, sum_so_far, map);
}

vector<Vertex> readTree(int n) {
    vector<Vertex> tree;
    tree.reserve(n);
    for (int i = 0; i < n; i++) {
        int parent, weight;
        cin >> parent >> weight;
        tree.emplace_back(weight, parent);
    }
    return tree;
}

int main() {
    int n;
    cin >> n;
    long x;
    cin >> x;
    vector<Vertex> tree = readTree(n);
    cout << getNumberOfUpgoingPaths(tree, x);
}
