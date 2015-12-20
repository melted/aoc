#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <unordered_set>
#include <algorithm>

using namespace std;
string target;
string final_state;

map<string, vector<string>> rules;
map<string, string> rev;

string get_atom(string s, unsigned long long pos) {
    if (islower(s[pos+1])) {
        return s.substr(pos, 2);
    }
    return s.substr(pos, 1);
}

void read_data() {
    ifstream f("input19.txt");
    map<string, char> atoms;
    char current_atom = 'A';
    if(!f.eof()) {
        string from, s, to;
        do {
            s = "";
            f >> from >> s >> to;
            if (s == "") break;
            if(atoms.count(from) == 0) {
                atoms[from] = current_atom++;
            }
            from = atoms[from];
            int pos = 0;
            string to2;
            while (pos < to.size()) {
                string a = get_atom(to, pos);
                pos+=a.size();
                if(atoms.count(a) == 0) {
                    atoms[a] = current_atom++;
                }
                to2 += atoms[a];
            }
            rev[to2] = from;
            rules[from].push_back(to2);
        } while (s == "=>");
        int pos = 0;
        while (pos < from.size()) {
            string a = get_atom(from, pos);
            pos+=a.size();
            target += atoms[a];
        }
        final_state = atoms["e"];
    }
}

vector<string> mutate() {
    vector<string> mutations;
    unsigned long long pos = 0;
    do {
        string atom = get_atom(target, pos);
        for (auto rule : rules[atom]) {
            string m(target);
            m.replace(pos, atom.size(), rule);
            mutations.push_back(m);
        }
        pos += atom.size();
    } while (pos < target.size());
    sort(mutations.begin(), mutations.end());
    auto i = unique(mutations.begin(), mutations.end());
    mutations.erase(i, mutations.end());
    return mutations;
}

int breakdown(string prefix, string s, int t) {
    if (prefix == "" && s == final_state) return t;
    for(auto p : rev) {
        int r = INT_MAX;
        auto mm = mismatch(p.first.begin(), p.first.end(), s.begin());
        if(mm.first != p.first.begin()) {
            if (mm.first == p.first.end()) {
                string m(prefix);
                string a(s);
                a.replace(0, p.first.size(), p.second);
                m.append(a);
                r = breakdown("", m, t + 1);
            } else {
                string pr(prefix);
                pr.append(p.first.begin(), mm.first);
                string m(mm.second, s.end());
                if (m.size() > 1 && s.size() > m.size())
                    r = breakdown(pr, m, t);
            }
        } else if (prefix != "") {
            string ps(prefix);
            ps.append(s);
            auto pos = ps.find(p.first);
            if (pos != string::npos) {
                ps.replace(pos, p.first.size(), p.second);
                r = breakdown("", ps, t + 1);
            }
        }
        if (r != INT_MAX) return r;
    }
    return INT_MAX;
}

int main() {
    read_data();
    vector<string> output = mutate();
    cout << output.size() << " " << breakdown("", target, 0) << endl;
    return 0;
}