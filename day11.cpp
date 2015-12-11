#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

string start = "vzbxkghb";

string increment(string s) {
    bool carry = false;
    int i = s.size() - 1;
    do {
        if (s[i] == 'z') {
            s[i] = 'a';
            carry = true;
        } else {
            s[i]++;
            if (s[i] == 'i' || s[i] == 'l' || s[i] == 'o') {
                for (int j = s.size() - 1; j > i; j--) s[j] = 'a';
                s[i]++;
            }
            carry = false;
        }
        i--;
    } while (carry);
    return s;
}

bool two_pairs(string s) {
    auto i = adjacent_find(s.begin(), s.end());
    if (i != s.end()) {
        i += 2;
        i = adjacent_find(i, s.end());
        return i != s.end();
    }
    return false;
}

bool increasing(string s) {
    string diff(s);
    adjacent_difference(s.begin(), s.end(), diff.begin());
    return search_n(diff.begin(), diff.end(), 2, 1) != diff.end();
}

bool no_forbidden(string s) {
    static string forbidden = "ilo";
    return s.find_first_of(forbidden) == string::npos;
}

bool is_valid(string s) {
    return increasing(s) && no_forbidden(s) && two_pairs(s);
}

string get_next(string s) {
    do {
        s = increment(s);
    } while (!is_valid(s));
    return s;
}

int main() {
    string password = get_next(start);
    cout << password << " " << get_next(password) << endl;
    return 0;
}