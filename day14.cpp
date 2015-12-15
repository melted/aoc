#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <map>
#include <algorithm>
#include <functional>

using namespace std;

using deer = tuple<string, int, int, int>;
vector<deer> reindeer;

void read_data() {
    ifstream f("input14.txt");
    while(!f.eof()) {
        string n, s;
        int speed, time, rest;
        f >> n >> s >> s >> speed >> s >> s >> time
            >> s >> s >> s >> s >> s >> s >> rest >> s;
        if (n == "") break;
        reindeer.push_back(make_tuple(n, speed, time, rest));
    }
}

int dist(deer d, int t) {
    int cycle = get<2>(d) + get<3>(d);
    int whole = t / cycle;
    int partial = min(get<2>(d), t % cycle);
    return get<1>(d)*(whole*get<2>(d) + partial);
}

int find_best(int time) {
    int maxd = 0;
    for (auto d : reindeer) {
        int ds = dist(d, time);
        maxd = max(maxd, ds);
    }
    return maxd;
}

vector<deer> race(int t) {
    vector<deer> out;
    int maxd = 0;
    for (auto d : reindeer) {
        int ds = dist(d, t);
        if (ds == maxd) {
            out.push_back(d);
        } else if (ds > maxd) {
            out.clear();
            out.push_back(d);
            maxd = ds;
        }
    }
    return out;
}

int points(int time) {
    map<deer, int> scoreboard;
    for(int t = 1; t < time + 1; t++) {
        auto winners = race(t);
        for (auto d : winners) {
            scoreboard[d]++;
        }
    }
    return max_element(scoreboard.begin(), scoreboard.end(), [](auto a, auto b) {
                            return a.second < b.second;
                       })->second;
}

int main() {
    read_data();
    cout << find_best(2503) << " " << points(2503) << endl;
    return 0;
}