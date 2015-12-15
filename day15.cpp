#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <atomic>
#include <thread>
#include <algorithm>

using namespace std;

using props = array<int, 5>;
vector<props> ingredients;
atomic_int global_max(0), global_diet_max(0);

void read_data() {
    ifstream f("input16.txt");
    while(!f.eof()) {
        string s;
        int c, d, fl, t, cal;
        f >> s >> s >> c >> s >> s >> d >> s >> s >> fl
            >> s >> s >> t >> s >> s >> cal;
        if (f.eof()) break;
        ingredients.push_back({ c, d, fl, t, cal });
    }
}

int scoring(const vector<int> &a) {
    int score = 1;
    for (int j = 0; j < 4; j++) {
        int s = 0;
        for (int i = 0; i < a.size(); i++) {
            s += (ingredients[i])[j] * a[i];;
        }
        score *= max(0,s);
    }
    return score;
}

int count_calories(vector<int>& a) {
    int cals = 0;
    for (int i = 0; i < a.size(); i++) {
        cals+=a[i]*ingredients[i][4];
    }
    return cals;
}

void update(vector<int> &a) {
    auto m = a.size() - 2;
    while (++a[m] > (100 - accumulate(a.begin(), a.begin() + m, 0)) && m > 0) a[m--] = 0;
    a[a.size() - 1] = 100 - accumulate(a.begin(), a.end()-1, 0);
}

void find_max(int start, int stop) {
    int local_max = 0;
    int local_diet_max = 0;
    vector<int> a(ingredients.size(), 0);
    a[0] = start;
    a[a.size() - 1] = 100 - start;
    while (a[0] < stop) {
        int score = scoring(a);
        local_max = max(local_max, score);
        if (count_calories(a) == 500) local_diet_max = max(local_diet_max, score);
        update(a);
    }
    bool finished = true;
    do {
        int gm = global_max;
        int gdm = global_diet_max;
        if (gm < local_max) finished = global_max.compare_exchange_strong(gm, local_max);
        if (gdm < local_diet_max) finished &= global_diet_max.compare_exchange_strong(
                    gdm, local_diet_max);
    } while(!finished);
}

int main() {
    read_data();
    vector<thread> threads;
    threads.emplace_back(&find_max, 0, 26);
    threads.emplace_back(&find_max, 26, 51);
    threads.emplace_back(&find_max, 51, 76);
    threads.emplace_back(&find_max, 76, 101);
    for(auto& t : threads) {
        t.join();
    }
    cout << global_max << " " << global_diet_max << endl;
    return 0;
}