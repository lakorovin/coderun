// https://contest.yandex.ru/contest/36783/problems/G/

#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

const int UNDEFINED = -13175438;


struct Vertex {
    int w;
    int p;

    Vertex(int _w, int _p) : w(_w), p(_p) {}
};

vector<vector<long>> createReverseTree(const vector<Vertex>& treeOrig) {
    int n = (int)treeOrig.size();
    vector<vector<long>> reverseTree(n);

    for (int i = 0; i < n; i++) {
        int parent = treeOrig[i].p;

        if (parent < 0)
        {
            continue;
        }
        reverseTree[parent].push_back(i);
    }

    return reverseTree;
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

int root = 0;

vector<Vertex> readTree(long n)
{
    vector<Vertex> tree;

    for (long i = 0; i < n; i++)
    {
        long parent, weight;
        cin >> parent >> weight;
        Vertex v(weight, parent);

        if (parent < 0)
        {
            root = i;
        }
        tree.push_back(v);
    }
    return tree;
}


long long calcWeight(int ind, const vector<Vertex>& tree, vector<long long>& weight) {
    if (ind < 0) {
        return 0;
    }
    if (weight[ind] != UNDEFINED) {
        return weight[ind];
    }
    Vertex v = tree[ind];
    weight[ind] = v.w + calcWeight(v.p, tree, weight);
    return weight[ind];
}

int getNumberOfUpgoingPaths(const vector<Vertex>& treeOrig, int x) {
    long resVal = 0;

    auto tree = createReverseTree(treeOrig);

    unordered_map<long, long> map;
    map[0] = 1;

    resVal = traverseTree(tree, treeOrig, root, x, 0, map);

    return resVal;

}

//vector<Vertex> readTree(int n) {
//    vector<Vertex> tree;
//    tree.reserve(n);
//    for (int i = 0; i < n; i++) {
//        int parent, weight;
//        cin >> parent >> weight;
//        tree.emplace_back(weight, parent);
//    }
//    return tree;
//}

int main() {
    int n;
    cin >> n;
    int x;
    cin >> x;
    vector<Vertex> tree = readTree(n);
    cout << getNumberOfUpgoingPaths(tree, x);

}
