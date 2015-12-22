#include <iostream>
#include <vector>
#include <random>
#include <map>

using namespace std;

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> dis(0, 4);

int play_out(vector<int> spells) {
    auto i = spells.begin();
    int hp = 50;
    int mana = 500;
    int mana_used = 0;
    int opp_hp = 51;
    int shield_time = 0;
    int poison_time = 0;
    int recharge_time = 0;
    while (true) {
        int spell =*i++;
        hp--;
        if (hp < 1) return INT_MAX;
        if (poison_time > 0) {
            poison_time--;
            opp_hp -= 3;
            if (opp_hp < 1) return mana_used;
        }
        if (recharge_time > 0) {
            recharge_time--;
            mana += 101;
        }
        switch(spell) {
            case 0:
                mana -= 53;
                mana_used += 53;
                opp_hp -= 4;
                break;
            case 1:
                mana -= 73;
                mana_used += 73;
                hp += 2;
                opp_hp -= 2;
                break;
            case 2:
                mana -= 113;
                mana_used += 113;
                shield_time = 6;
                break;
            case 3:
                mana -= 173;
                mana_used += 173;
                poison_time = 6;
                break;
            case 4:
                mana -= 229;
                mana_used += 229;
                recharge_time = 5;
                break;
        }
        if (mana < 0) return INT_MAX;
        if (poison_time > 0) {
            poison_time--;
            opp_hp -= 3;
        }
        if (opp_hp < 1) return mana_used;
        if (recharge_time > 0) {
            recharge_time--;
            mana += 101;
        }
        hp -= shield_time > 0?2:9;
        if (shield_time > 0) shield_time -= 2;
        if (hp < 1) return INT_MAX;
    }
}

vector<int> generate(int len) {

    map<int, int> effect;
    vector<int> out;

    for(int i = 0; i < 30; i++) {
        int s;
        while(true) {
            s = dis(gen);
            if (effect[s] == 0) break;
        }
        out.push_back(s);
        if (s > 1) effect[s] = 3;
        for(int j = 2; j < 5; j++) effect[j] = max(0, effect[j] - 1);
    }
    return out;
}

int main() {
    int min_mana = INT_MAX;
    for (int i = 0; i < 1000000; i++) {
        int s = play_out(generate(30));
        min_mana = min(min_mana, s);
    }
    cout << min_mana << endl;
    return 0;
}