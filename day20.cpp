#include <iostream>
#include <vector>

using namespace std;

int target = 36000000;

vector<int> houses(1000000);

void fill_houses() {
    for(int i = 1; i < houses.size(); i++) {
        for(int j = i; j < houses.size(); j+=i) {
            houses[j] += i*10;
        }
    }
}

void fill_houses2() {
    houses = vector<int>(1000000);
    for(int i = 1; i < houses.size(); i++) {
        for(int j = i, c = 0; j < houses.size() && c < 50; j+=i, c++) {
            houses[j] += i*11;
        }
    }
}

int first_house() {
    for (int i = 1; i < houses.size(); i++) {
        if (houses[i] >= target) return i;
    }
    return -1;
}

int main() {
    fill_houses();
    int house1 = first_house();
    fill_houses2();
    int house2 = first_house();
    cout << house1 << " " << house2 << endl;
    return 0;
}
