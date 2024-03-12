#include <iostream>
#include <string>
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

int main()
{
    const int INF = 400 * 101;
    int N;
    std::cin >> N;
    std::vector<State> k2;
    k2.reserve(N + 1);
    k2.push_back(State());
    int sum = 0;
    for (int j = 0; j < N; ++j) {
        int x;
        std::cin >> x;
        if (x > 100) {
            std::vector<State> nextLev;
            nextLev.reserve(k2.size() + 1);
            State sPrev(-1, 0, INF);
            for (int i = 0; i < k2.size() + 1; ++i) {
                // State sCur = k2[i - 1];

                if ((i + 1 < k2.size()) && (sPrev.amount + x > k2[i + 1].amount)) {
                    State sK = k2[i + 1];
                    sK.k2 += 1;
                    sK.k1 -= 1;
                    sK.days.push_back(j + 1);
                    assert(sK.k1 == i);
                    nextLev.push_back(std::move(sK));
                    // k2[i].k1 = sK.k1 - 1;
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
            k2 = nextLev;

        }
        else {
            for (int i = 0; i < k2.size(); ++i) {
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

    for (int ind = 0; ind < k2.size() - 1; ++ind) {
        if (k2[ind].amount >= INF) {
            // assert(ind < 2);
            continue;
        }
        assert(k2[ind].amount <= k2[ind + 1].amount);
    }


    int ind = 0;
    for (; ind < k2.size() - 1; ++ind) {
        if (k2[ind].amount >= INF) {
            assert(ind == 0);
            continue;
        }
        if (k2[ind].amount < k2[ind + 1].amount) {
            break;
        }
    }


    std::cout << k2[ind].amount << std::endl;
    std::cout << k2[ind].k1 << " " << k2[ind].k2 << std::endl;
    for (int day : k2[ind].days) {
        std::cout << day << " ";
    }
    std::cout << std::endl;

    return 0;
}

