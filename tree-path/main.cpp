// https://contest.yandex.ru/contest/36783/problems/G/

#include <vector>
#include <iostream>

using namespace std;

const int UNDEFINED = -1317;


struct Vertex {
    int w;
    int p;

    Vertex(int w, int p) {
        w = w;
        p = p;
    }
};


int getNumberOfUpgoingPaths(vector<Vertex> tree, int x) {
    // your code goes here
    vector<int> weight(tree.size(), UNDEFINED);

    return 0;
}

vector<Vertex> readTree(int n) {
    vector<Vertex> tree;
    for (int i = 0; i < n; i++) {
        int parent, weight;
        cin >> parent >> weight;
        tree.push_back(Vertex(weight, parent));
    }
    return tree;
}

int main() {
    int n;
    cin >> n;
    int x;
    cin >> x;
    vector<Vertex> tree = readTree(n);
    cout << getNumberOfUpgoingPaths(std::move(tree), x);

}
