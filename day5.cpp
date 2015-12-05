#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

bool vowels(string &s) {
    int count = count_if(s.begin(), s.end(), [](char c) {
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    });
    return count > 2;
}

bool duped(string &s) {
    for (int i = 1; i < s.length(); i++) {
        if (s[i - 1] == s[i]) {
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
        string t = s.substr(i + 1);
        string ss = s.substr(i - 1, 2);
        if (t.find(ss) != string::npos) {
            return true;
        }
    }
    return false;
}


bool hole_pair(string &s) {
    for (int i = 2; i < s.length(); i++) {
        if (s[i - 2] == s[i]) {
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
        if (vowels(s) && duped(s) && clear(s)) {
            nice1++;
        }
        if (two_repeat(s) && hole_pair(s)) {
            nice2++;
        }
    }
    cout << nice1 << " " << nice2 << endl;
    return 0;
}