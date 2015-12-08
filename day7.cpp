#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <sstream>

using namespace std;

struct token {
    enum type {
        signal, id, op_and, op_or, op_lshift, op_rshift, op_not, op_arrow
    };

    type t;
    unsigned short sig;
    string name;
    token (type tp) : t(tp) {}
    token (unsigned short n) : t(signal), sig(n) {}
    token (string s) : t(id), name(s) {}
};

struct rule {
    unsigned short result = 0;
    bool has_result = false;

    unsigned short eval() {
        if (!has_result) {
            result = calc();
            has_result = true;
        }
        return result;
    }

    virtual void reset() {
        has_result = false;
    }

    virtual unsigned short calc() = 0;
};

map<string, rule*> rules;

struct in_rule : rule {
    string l;

    virtual unsigned short calc() { return rules[l]->eval(); }

    virtual void reset() {
        if (l != "") { has_result = false; }
    }

    in_rule(unsigned short n)  {
        result = n;
        has_result = true;
    }
    in_rule(string s) : l(s) {}
};

struct or_rule : rule {
    string l, r;

    virtual unsigned short calc() { return rules[l]->eval() | rules[r]->eval(); }

    or_rule(string a, string b) : l(a), r(b) {}
};

struct and_rule : rule {
    string l, r;

    virtual unsigned short calc() { return rules[l]->eval() & rules[r]->eval(); }

    and_rule(string a, string b) : l(a), r(b) {}
};

struct lshift_rule : rule {
    string r;
    unsigned short sh;

    virtual unsigned short calc() { return rules[r]->eval() << sh; }

    lshift_rule(string a, unsigned short b) : r(a), sh(b) { }
};

struct rshift_rule : rule {
    string r;
    unsigned short sh;

    virtual unsigned short calc() { return rules[r]->eval() >> sh; }

    rshift_rule(string a, unsigned short b) : r(a), sh(b) { }
};

struct not_rule : rule {
    string r;

    virtual unsigned short calc() { return ~rules[r]->eval(); }

    not_rule(string a) : r(a) {}
};

token tokenize(string s) {
    static map<string, token::type> lookup_ops = {{"NOT",    token::op_not},
                                                  {"LSHIFT", token::op_lshift},
                                                  {"RSHIFT", token::op_rshift},
                                                  {"AND",    token::op_and},
                                                  {"OR",     token::op_or},
                                                  {"->",     token::op_arrow}};
    auto i = lookup_ops.find(s);
    if (i == lookup_ops.end()) {
        if (isdigit(s[0])) {
            unsigned short n;
            istringstream is(s);
            is >> n;
            return token(n);
        } else {
            return token(s);
        }
    }
    return token((*i).second);
}

vector<token> read_input() {
    ifstream f("input7.txt");
    vector<token> result;
    while (!f.eof()) {
        string s;
        f >> s;
        if (s != "") result.push_back(tokenize(s));
    }
    return result;
}

void build_rules(vector<token>& tokens) {
    auto i = tokens.begin();
    while(i != tokens.end()) {
        rule* r = nullptr;
        if((*i).t == token::op_not) {
            r = new not_rule((*++i).name);
        } else {
            token a = (*i);
            token op = (*++i);
            if (op.t == token::op_arrow) {
                i--;
                if (a.t == token::signal) {
                    r = new in_rule(a.sig);
                } else if (a.t == token::id) {
                    r = new in_rule(a.name);
                } else {
                    cerr << "bad signal" << endl;
                }
            } else {
                token a2 = *(++i);
                if (a.t == token::signal && op.t == token::op_and) {
                    ostringstream os;
                    os << a.sig;
                    rules.insert(make_pair(os.str(), new in_rule(a.sig)));
                    a = token(os.str());
                }
                switch (op.t) {
                    case token::op_or:
                        r = new or_rule(a.name, a2.name);
                        break;
                    case token::op_and:
                        r = new and_rule(a.name, a2.name);
                        break;
                    case token::op_lshift:
                        r = new lshift_rule(a.name, a2.sig);
                        break;
                    case token::op_rshift:
                        r = new rshift_rule(a.name, a2.sig);
                        break;
                    default:
                        cerr << "bad token in op" << endl;
                        break;
                }
            }

        }
        if ((*++i).t != token::op_arrow) {
            cerr << "missing arrow"<< endl;
        }
        token res = *++i;
        if (r != nullptr) {
            rules.insert(make_pair(res.name, r));
        } else {
            cerr << "no rule " << endl;
        }
        i++;
    }
}

int main() {
    vector<token> input = read_input();
    build_rules(input);
    auto res = rules["a"]->eval();
    cout << res << endl;
    for(auto& p : rules) {
        p.second->reset();
    }
    rules["b"] = new in_rule(res);
    cout << rules["a"]->eval() << endl;
    return 0;
}
