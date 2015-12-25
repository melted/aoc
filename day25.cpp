#include <iostream>

using namespace std;

int seq(int row, int col) {
    return (row + col - 2)*(row + col - 1)/2 + col;
}

long long next(long long n) {
    return (n * 252533) % 33554393;
}

long long get_code(int row, int col) {
    int p = seq(row, col);
    long long n = 20151125;
    for (int i = 1; i < p; i++) {
        n = next(n);
    }
    return n;
}

int main() {
    cout << get_code(2978,3083) << endl;
    return 0;
}