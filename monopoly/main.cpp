// https://contest.yandex.ru/contest/36783/problems/O/

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <cassert>
#include <set>

using namespace std;


struct Building {
    int needCapital;
    int addedCapital;

    Building(int c, int p): needCapital(c), addedCapital(p){
    }
};


long long getMaxFinalCapital(vector<Building> buildings, int startCapital, int maxNumberOfBuildings) {
    long long res = startCapital;
    std::sort(buildings.begin(), buildings.end(), 
        [](const auto& a, const auto& b) { return std::tie(b.addedCapital, a.needCapital) < std::tie(a.addedCapital, b.needCapital); });
    int cur = 0;
    vector<int> visited(buildings.size(), 0);
    map<long long, int> cost_to_index;
    set<int> unseen;
    int pure_unseen = 0;
    while(cur < (int)buildings.size()) {
        const Building& b = buildings[cur];
        if (b.needCapital <= res) {
            assert(visited[cur] == 0);
            visited[cur] = 1;
            --maxNumberOfBuildings;
            res += b.addedCapital;
            if (cur == pure_unseen) {
                ++pure_unseen;
            }
            if (maxNumberOfBuildings == 0) {
                break;
            }
            unseen.erase(cur);
            if (!cost_to_index.empty()) {
                auto it = cost_to_index.upper_bound(res);
                if (it == cost_to_index.begin()) {
                    cur = pure_unseen;
                }
                else {
                    --it;
                    cur = it->second;
                    cost_to_index.erase(it);
                }
            }
            else {
                if (unseen.empty()) {
                    cur = pure_unseen;
                }
                else {
                    cur = *unseen.cbegin();
                }
            }
        }
        else {
            if (cost_to_index.empty() || cost_to_index.cbegin()->first > b.needCapital) {
                unseen.erase(cur);
                cost_to_index[b.needCapital] = cur;
            }
            else {
                unseen.insert(cur);
            }
            if (cur == pure_unseen) {
                ++pure_unseen;
            }
            cur = pure_unseen;
        }
    }
    return res;
}


vector<Building> readBuildings(int n) {
    vector<Building> buildings;
    for (int i = 0; i < n; i++) {
        int c, p;
        cin >> c >> p;
        buildings.emplace_back(c, p);
    }
    return buildings;
}

int main() {
    int n;
    cin >> n;
    int k;
    cin >> k;
    vector<Building> buildings = readBuildings(n);
    int M;
    cin >> M;
    cout << getMaxFinalCapital(std::move(buildings), M, k) << endl;
}
