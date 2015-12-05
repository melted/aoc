#include <iostream>
#include <fstream>
#include <map>
#include <tuple>

using namespace std;

int main() {
    ifstream f("input3.txt");
    map<pair<int,int>,int> locs;
    int x = 0, y = 0;
    int rx = 0, ry = 0;
    (locs[pair<int, int>(x, y)])++;
    for(int i = 0; !f.eof(); i++) {
        unsigned long ch = f.get();
        int dx = ch == '<' ? -1 : ch == '>' ? 1 : 0;
        int dy = ch == '^' ? 1 : ch == 'v' ? -1 : 0;
        if (i % 2) {
            rx += dx;
            ry += dy;
            (locs[pair<int, int>(rx, ry)])++;
        } else {
            x += dx;
            y += dy;
            (locs[pair<int, int>(x, y)])++;
        }
    }
    cout << locs.size() << endl;
    return 0;
}