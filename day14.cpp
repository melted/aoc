#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <map>

using namespace std;

using deer = tuple<string, int, int, int>;

vector<deer> reindeers;

void read_data() {
    ifstream f("input14.txt");
    while(!f.eof()) {
        string n, s;
        int speed, time, rest;
        f >> n >> s >> s >> speed >> s >> s >> time
            >> s >> s >> s >> s >> s >> s >> rest >> s;
        if (n == "") break;
        reindeers.push_back(make_tuple(n, speed, time, rest));
    }
}

int dist(deer d, int t) {
    int ds = 0;
    while (t > 0) {
        int rt = min(t, get<2>(d));
        ds += rt * get<1>(d);
        t -= rt;
        t -= get<3>(d);
    }
    return ds;
}

int find_best(int time) {
    int maxd = 0;
    for (auto d : reindeers) {
        int ds = dist(d, time);
        maxd = max(maxd, ds);
    }
    return maxd;
}

vector<deer> race(int t) {
    vector<deer> out;
    int maxd = 0;
    for (auto d : reindeers) {
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
    int best = 0;
    for (auto d : scoreboard) {
        best = max(d.second, best);
    }
    return best;
}

int main() {
    read_data();
    cout << find_best(2503) << " " << points(2503) << endl;
    return 0;
}