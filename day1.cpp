#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ifstream f("input1.txt");
    int i = 0;
    int first_basement = 0;
    for (int p = 1; !f.eof(); p++) {
        unsigned long c = f.get();
        i += c == '(' ? 1 : c== ')' ? -1 : 0;
        if (i < 0 && first_basement == 0) {
            first_basement = p;
        }
    }
    cout << i << " " << first_basement << endl;
    return 0;
}