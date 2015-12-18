#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;
vector<int> grid(10000);

void read_state(bool stuck) {
    ifstream f("input18.txt");
    for (int i = 0; i < grid.size(); i++) {
        char ch;
        f >> ch;
        grid[i] = ch == '#' ? 1 : 0;
    }
    if (stuck) {
        grid[0] = 1;
        grid[99] = 1;
        grid[9900] = 1;
        grid[9999] = 1;
    }
}

int neighbours(int cell) {
    int row = cell / 100;
    int col = cell % 100;
    return ((col > 0) && (row > 0) ? grid[cell - 101] : 0) + (row > 0 ? grid[cell - 100] : 0)
        + ((row > 0) && (col < 99) ? grid[cell - 99] : 0) + (col > 0 ? grid[cell - 1] : 0)
        + (col < 99 ? grid[cell + 1] : 0) + ((row < 99) && (col > 0) ? grid[cell + 99] : 0)
        + (row < 99 ? grid[cell + 100] : 0) + ((row < 99) && (col < 99) ? grid[cell + 101] : 0);
}

void update(bool stuck) {
    vector<int> ncounts(10000);
    for(int i = 0; i < 10000; i++) {
        ncounts[i] = neighbours(i);
    }
    for(int i = 0; i < 10000; i++) {
        int n = ncounts[i];
        if (grid[i] == 1) {
            if (n < 2 || n > 3) grid[i] = 0;
        } else {
            if (n == 3) grid[i] = 1;
        }
    }
    if (stuck) {
        grid[0] = 1;
        grid[99] = 1;
        grid[9900] = 1;
        grid[9999] = 1;
    }
}

int main() {
    read_state(false);
    for(int i = 0; i < 100; i++) {
        update(false);
    }
    auto c = count(grid.begin(), grid.end(), 1);
    read_state(true);
    for(int i = 0; i < 100; i++) {
        update(true);
    }
    cout << c << " " << count(grid.begin(), grid.end(), 1) << endl;
    return 0;
}