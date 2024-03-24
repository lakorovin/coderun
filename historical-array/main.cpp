#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <cassert>

using namespace std;


struct HistoricalArray {
    int size;
    vector<unordered_map<int, int>> data;
    unordered_map<int, int> era_to_ind;
    unordered_map<int, int> curr_era;
    int curr_era_ind;

    unordered_map<int, set<int>> index_map;

    HistoricalArray(int n) : size(n), curr_era_ind(0) {
    }

    void beginNewEra(int eraId) {
        era_to_ind[curr_era_ind] = (int)data.size();
        // assert(eraId > curr_era_ind);
        data.push_back(std::move(curr_era));
        curr_era.clear();
        curr_era_ind = eraId;
    }

    void set1(int index, int value) {
        curr_era[index] = value;
        index_map[index].insert((int)data.size());
        /*auto it = curr_era.find(index);
        if (it != curr_era.end()) {
            it->second = value;
            index_map[index].insert(curr_era_ind);
        }
        else if (value != 0) {
            curr_era[index] = value;
            index_map[index].insert(curr_era_ind);
        }*/
    }

    int get(int index, int eraId) const {
        auto index_it = index_map.find(index);
        if (index_it == index_map.end()) {
            return 0;
        }
        const auto& s = index_it->second;
        if (s.empty()) {
            return 0;
        }
        int era_ind = era_to_ind.at(eraId);

        auto era_it = s.upper_bound(era_ind);
        if (era_it == s.begin()) {
            return 0;
        }
        --era_it;
        const auto& era = data.at(*era_it);
        auto it = era.find(index);
        if (it != era.end()) {
            return it->second;
        }
        return 0;
    }
};


int main() {
    int n;
    cin >> n;
    HistoricalArray arr(n);
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        string queryType;
        cin >> queryType;
        if (queryType == "set") {
            int index, value;
            cin >> index >> value;
            arr.set1(index, value);
        }
        else if (queryType == "begin_new_era") {
            int eraId;
            cin >> eraId;
            arr.beginNewEra(eraId);
        }
        else if (queryType == "get") {
            int index, eraId;
            cin >> index >> eraId;
            cout << arr.get(index, eraId) << endl;
        }
    }
}
