#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <cassert>

struct State {
    State() : k1(0), k2(0), amount(0) {};
    State(int _k1, int _k2, int _amount) : k1(_k1), k2(_k2), amount(_amount) {};
    int k1;
    int k2;
    int amount;
    std::vector<int> days;
};

size_t find_best_ind(const std::vector<State>& k2, int limit) {
    assert(!k2.empty());
    size_t ind = 0;
    for (; ind < k2.size() - 1; ++ind) {
        if (k2[ind].amount >= limit) {
            assert(ind == 0);
            continue;
        }
        if (k2[ind].amount < k2[ind + 1].amount) {
            break;
        }
    }
    return ind;
}

void check_sanity(const std::vector<State>& k2, int limit) {
    assert(!k2.empty());
    for (size_t ind = 0; ind < k2.size() - 1; ++ind) {
        if (k2[ind].amount >= limit) {
            continue;
        }
        assert(k2[ind].amount <= k2[ind + 1].amount);
    }
}

void print_result(const std::vector<State>& k2, size_t ind) {
    std::cout << k2[ind].amount << std::endl;
    std::cout << k2[ind].k1 << " " << k2[ind].k2 << std::endl;
    for (int day : k2[ind].days) {
        std::cout << day << " ";
    }
    std::cout << std::endl;
}

int main()
{
    const int INF = 400 * 101;
    int N;
    std::cin >> N;
    std::vector<State> k2;
    k2.reserve(N + 1);
    k2.push_back(State());
    for (int j = 0; j < N; ++j) {
        int x;
        std::cin >> x;
        if (x > 100) {
            std::vector<State> nextLev;
            nextLev.reserve(k2.size() + 1);
            State sPrev(-1, 0, INF);
            for (size_t i = 0; i < k2.size() + 1; ++i) {
                if ((i + 1 < k2.size()) && (sPrev.amount + x > k2[i + 1].amount)) {
                    State sK = k2[i + 1];
                    sK.k2 += 1;
                    sK.k1 -= 1;
                    sK.days.push_back(j + 1);
                    assert(sK.k1 == i);
                    nextLev.push_back(std::move(sK));
                }
                else {
                    sPrev.amount += x;
                    sPrev.k1 += 1;
                    assert(sPrev.k1 == i);
                    nextLev.push_back(std::move(sPrev));
                }
                if (i < k2.size()) {
                    sPrev = k2[i];
                }
            }
            k2 = std::move(nextLev);
        }
        else {
            for (size_t i = 0; i < k2.size(); ++i) {
                State& sBuy = k2[i];
                if ((i + 1 < k2.size()) && (sBuy.amount + x > k2[i + 1].amount)) {
                    State sK = k2[i + 1];
                    sBuy.amount = sK.amount;
                    sBuy.k2 = sK.k2 + 1;
                    sBuy.days = sK.days;
                    sBuy.days.push_back(j + 1);
                    assert(sBuy.k1 + 1 == sK.k1);
                }
                else {
                    sBuy.amount += x;
                }
            }
        }
    }

    check_sanity(k2, INF);
    size_t ind = find_best_ind(k2, INF);
    print_result(k2, ind);
    return 0;
}

