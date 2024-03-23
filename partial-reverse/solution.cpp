#include "solution.h"
#include <cassert>

using namespace std;

/** Comment it before submitting
struct Node {
    int val;
    Node* next;
    Node(int val_, Node* next_) {
        val = val_;
        next = next_;
    }
};
**/


Node* Reverse(Node* head, int left, int right) {
    assert(left <= right);
    Node fakehead(0, head);
    Node* before_begin = &fakehead;
    Node* cur = head;
    for (int i = 1; i < left; ++i) {
        before_begin = cur;
        cur = cur->next;
    }
    Node* begin = cur;
    Node* prev = begin;
    for (int i = left; i < right + 1; ++i) {
        Node* next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    before_begin->next = prev;
    begin->next = cur;
    return fakehead.next;
}
