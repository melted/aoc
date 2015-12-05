#include <iostream>
#include <sstream>
#include <string>
#include "md5.h"
#include <functional>

using namespace std;

string key("iwrupvqb");

bool zero_test6(string s) {
    return s.substr(0,6) == "000000";
}

bool zero_test5(string s) {
    return s.substr(0,5) == "00000";
}

int find_match(function<bool(string)> test) {
    int c = 1;
    while(true) {
        ostringstream ss;
        ss << key << c;
        string hash = md5(ss.str());
        if (test(hash)) {
            break;
        }
        c++;
    }
    return c;
}

int main()  {
    cout << find_match(zero_test5) << " " << find_match(zero_test6) << endl;
    return 0;
}