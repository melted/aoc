#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <tuple>

using namespace std;

pair<int, int> lengths(string& s) {
    auto pos = 0ULL;
    int len = s.size() - 2;
    int enc_len = s.size() + 4;
    while (true) {
        auto xpos = s.find('\\', pos);
        if (xpos == string::npos) break;
        switch (s[xpos + 1]) {
            case '\\':
            case '"':
                len--;
                enc_len += 2;
                break;
            case 'x':
                len -= 3;
                enc_len++;
                xpos += 2;
                break;
            default:
                cerr << "bad escape " << s << endl;
        }
        pos = xpos + 2;
    }
    return make_pair(len, enc_len);
}

int main() {
    fstream f("input8.txt");
    int diff = 0;
    int diff2 = 0;
    while(!f.eof()) {
        int l, e;
        string s;
        f >> s;
        if (s != "") {
            tie(l, e) = lengths(s);
            diff += s.size() - l;
            diff2 += e - s.size();
        }
    }
    cout << diff << " " << diff2 << endl;
    return 0;
}