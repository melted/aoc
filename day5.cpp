#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

bool vowels(string &s) {
    static set<char> vowels = { 'a', 'e', 'i', 'o', 'u' };
    return count_if(s.begin(), s.end(),
                    [&](char c) { return vowels.find(c) != vowels.end();  }) > 2;
}

bool duped(string &s, int space) {
    for (int i = space + 1; i < s.length(); i++) {
        if (s[i - 1 - space] == s[i]) {
            return true;
        }
    }
    return false;
}

bool clear(string &s) {
    return s.find("ab") == string::npos &&
           s.find("cd") == string::npos &&
           s.find("pq") == string::npos &&
           s.find("xy") == string::npos;
}

bool two_repeat(string &s) {
    for (int i = 1; i < s.length(); i++) {
        if (s.find(s.substr(i - 1, 2), i + 1) != string::npos) {
            return true;
        }
    }
    return false;
}

int main() {
    ifstream f("input5.txt");
    int nice1 = 0;
    int nice2 = 0;
    while (!f.eof()) {
        string s;
        f >> s;
        if (vowels(s) && duped(s, 0) && clear(s)) {
            nice1++;
        }
        if (two_repeat(s) && duped(s, 1)) {
            nice2++;
        }
    }
    cout << nice1 << " " << nice2 << endl;
    return 0;
}