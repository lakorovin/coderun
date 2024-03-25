// https://contest.yandex.ru/contest/36783/problems/L/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Segment {
    int left;
    int right;

    Segment(int left, int right) : left(left), right(right) {
    }
};

vector<Segment> readSegments() {
    int n;
    cin >> n;
    vector<Segment> segments;
    for (int i = 0; i < n; i++) {
        int left, right;
        cin >> left >> right;
        segments.push_back(Segment(left, right));
    }
    return segments;
}

vector<Segment> getIntersection(const vector<Segment>& firstSequence, const vector<Segment>& secondSequence) {
    vector<Segment> res;
    auto it = firstSequence.cbegin();
    auto it2 = secondSequence.cbegin();
    while (it != firstSequence.cend() && it2 != secondSequence.cend()) {
        if (it->right < it2->left) {
            ++it;
            continue;
        }
        if (it->left > it2->right) {
            ++it2;
            continue;
        }
        if (it->right < it2->right) {
            res.emplace_back(std::max(it2->left, it->left), it->right);
            ++it;
        }
        else {
            res.emplace_back(std::max(it2->left, it->left), it2->right);
            ++it2;
        }
    }
    return res;
}


void outputAnswer(const vector<Segment>& intersection) {
    for (const Segment& segment : intersection) {
        cout << segment.left << " " << segment.right << endl;
    }
}

int main() {
    vector<Segment> firstSequence = readSegments();
    vector<Segment> secondSequence = readSegments();

    vector<Segment> intersection = getIntersection(firstSequence, secondSequence);
    outputAnswer(intersection);
}
