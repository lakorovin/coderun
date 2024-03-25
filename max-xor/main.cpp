// https://contest.yandex.ru/contest/36783/problems/T/

#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class Node {
public:
    unique_ptr<Node> left;
    unique_ptr<Node> right;
};

class BitwiseTrie {
    unique_ptr<Node> root;
public:
    BitwiseTrie() : root(new Node()){
    }

    void insert(int n) {
        Node* temp = root.get();
        for (int i = 31; i >= 0; i--) {
            int bit = (n >> i) & 1;
            if (bit == 0) {
                if (!temp->left) {
                    temp->left = make_unique<Node>();
                }
                temp = temp->left.get();
            }
            else {
                if (!temp->right) {
                    temp->right = make_unique<Node>();
                }
                temp = temp->right.get();
            }
        }
    }

    int getMaxXOR(int value) const {
        int currAns = 0;
        Node* temp = root.get();

        for (int i = 31; i >= 0; i--) {
            int bit = (value >> i) & 1;
            if (bit == 0) {
                if (temp->right) {
                    temp = temp->right.get();
                    currAns += (1 << i);
                }
                else {
                    temp = temp->left.get();
                }
            }
            else {
                if (temp->left) {
                    temp = temp->left.get();
                    currAns += (1 << i);
                }
                else {
                    temp = temp->right.get();
                }
            }
        }
        return currAns;
    }
};


int getMaxXOR(vector<int> list) {
    if (list.empty()) {
        return 0;
    }
    BitwiseTrie t;
    int maxXor = 0;
    for (int v : list) {
        t.insert(v);
        int currXor = t.getMaxXOR(v);
        maxXor = max(maxXor, currXor);
    }
    return maxXor;
}

vector<int> readList() {
    int n;
    cin >> n;
    vector<int> res(n);
    for (int i = 0; i < n; i++) {
        cin >> res[i];
    }
    return res;
}

int main() {
    vector<int> list = readList();
    cout << getMaxXOR(std::move(list));
}
