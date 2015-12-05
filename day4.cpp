#include <iostream>
#include <sstream>
#include <string>
#include "md5.h"

using namespace std;

string key("iwrupvqb");

bool zero_test(string s) {
    return s.substr(0,6) == "000000";
}

int main() {
    int c = 1;
    while(true) {
        ostringstream ss;
        ss << key << c;
        string hash = md5(ss.str());
        if(zero_test(hash)) {
            break;
        }
        c++;
    }
    cout << c << endl;
    return 0;
}