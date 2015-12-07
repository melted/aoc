#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;


vector<bool> lights(1000000);
vector<int> brights(1000000);

struct inst {
    enum actions { on, off, toggle };
    actions action;
    int x, y, x2, y2;

    inst(actions a, int ax, int ay, int bx, int by) : action(a), x(ax), y(ay), x2(bx), y2(by) {}
};

vector<inst> instructions;

void read_instructions() {
    ifstream f("input6.txt");
    while(!f.eof())  {
        inst::actions a;
        string s;
        char c, c2;
        f >> s;
        if(s == "turn") {
            string s2;
            f >> s2;
            if (s2 == "on") {
                a = inst::on;
            } else if (s2 == "off") {
                a = inst::off;
            } else {
                cerr << "bad input " << instructions.size() << endl;
                break;
            }
        } else if (s == "toggle") {
            a = inst::toggle;
        } else {
            if (s != "") {
                cerr << "bad input " << instructions.size() << endl;
            }
            break;
        }
        int x, y, x2, y2;
        f >> x >> c >> y >> s >> x2 >> c >> y2;
        instructions.emplace_back(a, x, y, x2, y2);
    }
}

void execute_instruction(inst& in) {
    int i, j;
    for(i = in.y; i < (in.y2+1); i++) {
        for(j = in.x; j < (in.x2+1); j++) {
            int cell=i*1000+j;
            switch(in.action) {
                case inst::on:
                    brights[cell]++;
                    lights[cell] = true;
                    break;
                case inst::off:
                    brights[cell]--;
                    if(brights[cell] < 0) {
                        brights[cell] = 0;
                    }
                    lights[cell] = false;
                    break;
                case inst::toggle:
                    brights[cell]+=2;
                    lights[cell] = !lights[cell];
                    break;
            }
        }
    }
}

int main() {
    read_instructions();
    for (auto& i : instructions) {
        execute_instruction(i);
    }
    auto lit = count(lights.begin(), lights.end(), true);
    auto brite = 0;
    for (auto c : brights) {
        brite += c;
    }
    cout << lit << " " << brite << endl;
    return 0;
}