#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

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

vector<vector<int>> solve_subset(vector<int>& state, const vector<int>& subset, int left) {
    vector<vector<int>> out;
    if (left == 0) {
        out.push_back(state);
    } else if (subset.size() > 0) {
        auto elem = subset.back();
        vector<int> state_new(state);
        state_new.push_back(elem);
        vector<int> subsubset(subset);
        subsubset.pop_back();
        vector<vector<int>> s = solve_subset(state_new, subsubset, left - elem);
        vector<vector<int>> s2 = solve_subset(state, subsubset, left);
        out.insert(out.begin(), s.begin(), s.end());
        out.insert(out.begin(), s2.begin(), s2.end());
    }
    return out;
}


int main() {
    read_data();
    vector<int> start;
    vector<vector<int>> sols = solve_subset(start, containers, 150);
    map<int, int> ways;
    for(auto s : sols) {
        ways[s.size()]++;
    }
    cout << sols.size() << " " << (*ways.upper_bound(0)).second << endl;
    return 0;
}