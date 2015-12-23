#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <tuple>

using namespace std;

struct inst {
    enum type { hlf, tpl, inc, jmp, jie, jio };
    type t;
    int reg;
    int offset;
};

vector<inst> code;

inst parse(string s) {
    static map<string, inst::type> lookup = { { "hlf", inst::hlf },
                                              { "tpl", inst::tpl },
                                              { "inc", inst::inc },
                                              { "jmp", inst::jmp },
                                              { "jie", inst::jie },
                                              { "jio", inst::jio } };
    istringstream is(s);
    string ins, arg1;
    int off = 0;
    inst out;
    is >> ins;
    out.t = lookup[ins];
    switch (out.t) {
        case inst::hlf:
        case inst::tpl:
        case inst::inc:
            is >> arg1;
            break;
        case inst::jmp:
            is >> off;
            break;
        case inst::jie:
        case inst::jio:
            is >> arg1 >> off;
            break;
    }
    if (arg1 != "") out.reg = arg1[0] == 'a'? 0 : 1;
    out.offset = off;
    return out;
}

void read_program() {
    ifstream f("input23.txt");
    while(!f.eof()) {
        string s;
        getline(f, s);
        if (s == "") continue;
        inst i = parse(s);
        code.push_back(i);
    }
}

pair<int, int> execute(int a) {
    int reg[2] = { a, 0 };
    int pc = 0, next;
    while(pc < code.size()) {
        inst i = code[pc];
        next = pc + 1;
        switch (i.t) {
            case inst::hlf:
                reg[i.reg] /= 2;
                break;
            case inst::tpl:
                reg[i.reg] *= 3;
                break;
            case inst::inc:
                reg[i.reg]++;
                break;
            case inst::jmp:
                next = pc + i.offset;
                break;
            case inst::jio:
                if (reg[i.reg] == 1) {
                    next = pc + i.offset;
                }
                break;
            case inst::jie:
                if ((reg[i.reg] % 2) == 0) {
                    next = pc + i.offset;
                }
                break;
        }
        pc = next;
    }
    return make_pair(reg[0], reg[1]);
}

int main() {
    read_program();
    auto p = execute(0);
    cout << p.second << " ";
    p = execute(1);
    cout << p.second << endl;
    return 0;
}