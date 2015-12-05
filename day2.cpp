#include <iostream>
#include <fstream>
#include <algorithm>
#include <tuple>
#include <cstdio>
#include <cstdlib>

using namespace std;

int area(int l, int w, int h) {
    return 2*l*w + 2*w*h + 2*h*l +  min({l*w, w*h, h*l });
}

int ribbon(int l, int w, int h) {
    return l*w*h + 2*min({l + h, w + h, w + l });
}

pair<int, int> process_line(ifstream& f) {
    char buffer[80];
    f.getline(buffer, 80);
    int l, w, h;
    int res = sscanf(buffer, "%dx%dx%d", &l, &w, &h);
    if (res != 3) {
        if (f.gcount() > 0) {
            cerr << "bad input" << endl;
        }
        return pair<int, int>(0, 0);
    }
    return pair<int, int>(area(l, w, h), ribbon(l, w, h));
}

int main() {
    ifstream f("input2.txt");
    int total = 0;
    int ribbon = 0;
    while(!f.eof()) {
        int t, r;
        tie(t, r) = process_line(f);
        total += t;
        ribbon += r;
    }
    cout << total << " " << ribbon << endl;
    return 0;
}