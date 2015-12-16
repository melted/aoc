#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>

using namespace std;

map<string, int> target = {
        {"children:", 3},
        {"cats:", 7},
        {"samoyeds:", 2},
        {"pomeranians:", 3},
        {"akitas:", 0},
        {"vizslas:", 0},
        {"goldfish:", 5},
        {"trees:", 3},
        {"cars:", 2},
        {"perfumes:", 1}
};

bool check(string prop, int val) {
    if (prop == "cats:" || prop == "trees:" ) {
        return target[prop] < val;
    }
    if (prop == "pomeranians:" || prop == "goldfish:") {
        return target[prop] > val;
    }
    return target[prop] == val;
}

int process_sues(bool corrected) {
    ifstream f("input16.txt");
    while(!f.eof()) {
        string t, p1, p2, p3;
        int number, v1, v2, v3;
        f >> t >> number >> t >> p1 >> v1 >> t >> p2 >> v2 >> t >> p3 >> v3;
        if (t == "") break;
        if (corrected) {
            if (check(p1, v1) && check(p2, v2) && check(p3, v3)) return number;
        } else {
            if (target[p1] == v1 && target[p2] == v2 && target[p3] == v3) return number;
        }
    }
    return -1;
}

int main() {
    cout << process_sues(false) << " " << process_sues(true) << endl;
    return 0;
}