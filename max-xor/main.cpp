// https://contest.yandex.ru/contest/36783/problems/T/

#include <iostream>
#include <vector>
#include <memory>
#include <unordered_set>

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


int getMaxXOR2(vector<int> list) {
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

int getMaxXOR(vector<int> nums) {
    int result = 0, mask = 0;
    for (int i = 31; i >= 0; i--) {
        //The mask will grow like  100..000 , 110..000, 111..000,  then 1111...111
        //for each iteration, we only care about the left parts
        mask = mask | (1 << i);
        unordered_set <int> s;
        for (int num : nums) {
            s.insert(num & mask);
        }
        int temp = result | (1 << i);
        // if a ^ b = c, then a ^ c = b;, we see if greedy result is possible
        for (int prefix : s) {
            if (s.count(temp ^ prefix)) {
                result = temp;
                break;
            }
        }

    }
    return result;
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
