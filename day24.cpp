#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <functional>
#include <set>

using namespace std;

using solution = tuple<set<int>, set<int>, set<int>>;

vector<int> packets;
vector<solution> solutions;

vector<int> read_data() {
    ifstream f("input24.txt");
    vector<int> out;
    while (!f.eof()) {
        int i = 0;
        f >> i;
        if (i != 0) out.push_back(i);
    }
    return out;
}

vector<vector<int>> get_group(vector<int> from, vector<int> acc, int target, int max_size) {
    vector<vector<int>> out;
    if (acc.size() > max_size) {
        return out;
    }
    if (find(from.begin(), from.end(), target) != from.end()) {
        acc.push_back(target);
        out.push_back(acc);
    } else if (from.size() > 1) {
        auto i = from.back();
        vector<int> wi(from);
        wi.pop_back();
        if (i <= target) {
            vector<int> ai(acc);
            ai.push_back(i);
            auto nn = get_group(wi, ai, target - i, max_size);
            out.insert(out.end(), nn.begin(), nn.end());
        }
        auto nw = get_group(wi, acc, target, max_size);
        out.insert(out.end(), nw.begin(), nw.end());
    }
    return out;
}

void solve() {
    int t = accumulate(packets.begin(), packets.end(), 0)/3;
    set<int> s(packets.begin(), packets.end());
    auto part = get_group(packets, vector<int>(), t, 6);
    sort(part.begin(), part.end(), [](vector<int> a, vector<int> b) {
        return a.size() < b.size();
    });
    cout << part.size() << endl;
    vector<vector<int>> candidates;
    auto size = part.begin()->size();
    auto i = part.begin();
    while(i != part.end()) {
        vector<int> rest(packets.size() - (*i).size());
        sort((*i).begin(), (*i).end());
        set_difference(packets.begin(), packets.end(),
                       (*i).begin(),(*i).end(), rest.begin());
        auto sols = get_group(rest, vector<int>(), t, rest.size());
        if (sols.size() > 0) {
            candidates.push_back(*i);
        }
        i++;
        if (candidates.size() > 0 && (*i).size() > size) break;
        size = (*i).size();
    }
    long long min_qe = LONG_LONG_MAX;
    for(auto c : candidates) {
        long long qe = 1;
        for (auto j : c) {
            qe *= j;
            cout << j << " ";
        }
        cout << qe << endl;
        min_qe = min(min_qe, qe);
    }
    cout << min_qe << endl;
}

void solve2() {
    int t = accumulate(packets.begin(), packets.end(), 0)/4;
    set<int> s(packets.begin(), packets.end());
    auto part = get_group(packets, vector<int>(), t, 6);
    sort(part.begin(), part.end(), [](vector<int> a, vector<int> b) {
        return a.size() < b.size();
    });
    cout << part.size() << endl;
    vector<vector<int>> candidates;
    auto size = part.begin()->size();
    auto i = part.begin();
    while(i != part.end()) {
        vector<int> rest(packets.size() - (*i).size());
        sort((*i).begin(), (*i).end());
        set_difference(packets.begin(), packets.end(),
                       (*i).begin(),(*i).end(), rest.begin());
        auto sols = get_group(rest, vector<int>(), t, rest.size()/3);
        if (sols.size() > 0) {
            for(auto s : sols) {
                vector<int> rest2(rest.size() - s.size());
                sort(s.begin(), s.end());
                set_difference(rest.begin(), rest.end(),
                               s.begin(),s.end(), rest2.begin());
                auto sols2 = get_group(rest2, vector<int>(), t, rest.size()/3);
                if (sols2.size() > 0) {
                    candidates.push_back(*i);
                    break;
                }
            }
        }
        i++;
        if (candidates.size() > 0 && (*i).size() > size) break;
        size = (*i).size();
    }
    long long min_qe = LONG_LONG_MAX;
    for(auto c : candidates) {
        long long qe = 1;
        for (auto j : c) {
            qe *= j;
            cout << j << " ";
        }
        cout << qe << endl;
        min_qe = min(min_qe, qe);
    }
    cout << min_qe << endl;
}

int main() {
    packets = read_data();
    solve2();
    return 0;
}
