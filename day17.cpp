#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

using solution = set<int>;
vector<int> containers;

void read_data() {
    ifstream f("input17.txt");
    while (!f.eof()) {
        int size = -1;
        f >> size;
        if (size > 0)
            containers.push_back(size);
    }
}

set<solution> solve_subset(set<int> subset, int left) {
    set<solution> out;
    for(auto elem : subset) {
        if (left - containers[elem] == 0) {
            solution s = { elem };
            out.insert(s);
        }
        if (left > containers[elem]) {
            int rem = left - containers[elem];
            set<int> subsubset(subset);
            subsubset.erase(elem);
            set<solution> s = solve_subset(subsubset, rem);
            for (auto sol : s) {
                sol.insert(elem);
                out.insert(sol);
            }
        }
    }
    return out;
}

int main() {
    read_data();
    vector<int> items(containers.size());
    iota(items.begin(), items.end(), 0);
    set<int> container_set(items.begin(), items.end());
    set<solution> sols = solve_subset(container_set, 150);
    map<int, int> ways;
    for(auto s : sols) {
        ways[s.size()]++;
    }
    cout << sols.size() << " " << (*ways.upper_bound(0)).second << endl;
    return 0;
}