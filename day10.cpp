#include <string>
#include <iostream>
#include <sstream>

using namespace std;

string input = "3113322113";

string look_and_say(string& s) {
    ostringstream os;
    char ch = s[0];
    int count = 0;
    for(char c : s) {
        if (c != ch) {
            os << count << ch;
            count = 0;
            ch = c;
        }
        count++;
    }
    os << count << ch;
    return os.str();
}

int main() {
    string result = input;
    for(int i = 0; i < 50; i++) {
        result = look_and_say(result);
        if (i == 39) cout << result.size() << " ";
    }
    cout << result.size() << endl;
    return 0;
}