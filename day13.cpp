#include <string>
#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> people;

map<pair<string, string>, int> likes;

void read_input() {
    ifstream f("input13.txt");
    while (!f.eof()) {
        string actor, target, dir, s;
        int val;
        f >> actor >> s >> dir >> val >> s >> s >> s >> s >> s >> s >> target;
        if (actor == "") break;
        if (dir == "lose") val = -val;
        target.pop_back();
        if (find(people.begin(), people.end(), actor) == people.end())
            people.push_back(actor);
        likes[make_pair(actor, target)] = val;
    }
    sort(people.begin(), people.end());
}

int eval_likes(vector<string> pos) {
    int len = pos.size();
    int sum = 0;
    for (int i = 0; i < len; i++) {
        int left = i == 0?len-1:i-1;
        int right = i == len - 1?0:i+1;
        sum += likes[make_pair(pos[i], pos[left])];
        sum += likes[make_pair(pos[i], pos[right])];
    }
    return sum;
}

void insert_blank_man() {
    string name="Nobody";
    for (auto p : people) {
        likes[make_pair(p, name)] = 0;
        likes[make_pair(name, p)] = 0;
    }
    people.push_back(name);
    sort(people.begin(), people.end());
}

int sum_happiness() {
    vector<string> position = people;
    int happy = eval_likes(position);
    while (next_permutation(position.begin()+1, position.end())) {
        happy = max(happy, eval_likes(position));
    }
    return happy;
}

int main() {
    read_input();
    int happy = sum_happiness();
    insert_blank_man();
    int happy2 = sum_happiness();
    cout << happy << " " << happy2 << endl;
    return 0;
}