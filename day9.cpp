#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <utility>

using namespace std;

vector<string> places;
map<pair<int, int>, int> dists;

int get_place(const string& s) {
    auto i = find(places.begin(), places.end(), s);
    if (i == places.end()) {
        places.push_back(s);
        i = find(places.begin(), places.end(), s);
    }
    return (int)distance(places.begin(), i);
}

void read_data() {
    ifstream f("input9.txt");
    while (!f.eof()) {
        string from, s, to, c;
        int d;
        f >> from >> s >> to >> c >> d;
        if (from == "") break;
        if (s != "to" && c != "=") {
            cerr << "bad format";
            break;
        }
        int f = get_place(from);
        int t = get_place(to);
        dists[make_pair(f, t)] = d;
        dists[make_pair(t, f)] = d;
    }
}

int calc_distance(vector<int> v) {
    int d = 0;
    for (int i = 1; i < v.size(); i++) {
        d += dists[make_pair(v[i-1], v[i])];
    }
    return d;
}

int main() {
    read_data();
    int min_value = INT32_MAX;
    int max_value = 0;
    vector<int> order(places.size());
    iota(order.begin(), order. end(), 0);
    do {
        int d = calc_distance(order);
        if (d < min_value) {
            min_value = d;
        }
        if (d > max_value) {
            max_value = d;
        }
    } while (next_permutation(order.begin(), order.end()));
    cout << min_value << " " << max_value << endl;
    return 0;
}