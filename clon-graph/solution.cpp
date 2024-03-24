#include "solution.h"

#include <unordered_map>
#include <cassert>
using namespace std;
/** Comment it before submitting
struct Node {
    int val;
    std::vector<Node*> neighbours;
    Node(int val_) {
        val = val_;
        neighbours = {};
    }
};
**/

Node* cloneGraphRec(Node* node, unordered_map<int, Node*>& map) {
    assert(node != nullptr);
    if (map[node->val] == nullptr) {
        Node* newNode = new Node(node->val);
        map[node->val] = newNode;
        for (Node* n: node->neighbours) {
            newNode->neighbours.push_back(cloneGraphRec(n, map));
        }        
    }
    return map[node->val];    
}

Node* cloneGraph(Node* node) {
    // Your code
    // “ヽ(´▽｀)ノ”
    unordered_map<int, Node*> map;
    return cloneGraphRec(node, map);
}
