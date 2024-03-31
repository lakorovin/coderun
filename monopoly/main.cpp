// https://contest.yandex.ru/contest/36783/problems/O/

#include <iostream>
#include <vector>
#include <queue>


struct Building {
    int needCapital;
    int addedCapital;

    Building(int c, int p) : needCapital(c), addedCapital(p) {
    }
};

int readInt() {
    int x;
    std::cin >> x;
    return x;
}

typedef std::priority_queue<Building, std::vector<Building>, bool (*)(const Building&, const Building&)> buildings_queue;

long long getMaxFinalCapital(std::vector<Building> buildings, int startCapital, int maxNumberOfBuildings) {
    long long res = startCapital;

    buildings_queue tr([](const Building& a, const Building& b) {
        return a.needCapital > b.needCapital;
        }, std::move(buildings));
    buildings_queue best([](const Building& a, const Building& b) {
        return a.addedCapital < b.addedCapital;
        }, std::vector<Building>());

    while (maxNumberOfBuildings > 0) {
        while (!tr.empty() && tr.top().needCapital <= res) {
            best.push(tr.top());
            tr.pop();
        }
        if (best.empty()) {
            break;
        }
        res += best.top().addedCapital;
        best.pop();
        --maxNumberOfBuildings;
    }
    return res;
}


std::vector<Building> readBuildings(int n) {
    std::vector<Building> buildings;
    for (int i = 0; i < n; i++) {
        int c, p;
        std::cin >> c >> p;
        buildings.emplace_back(c, p);
    }
    return buildings;
}

int main() {
    int n = readInt();
    int k = readInt();
    std::vector<Building> buildings = readBuildings(n);
    int M = readInt();
    std::cout << getMaxFinalCapital(std::move(buildings), M, k) << std::endl;
    return 0;
}
