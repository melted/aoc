#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <json/json.h>

using namespace std;
using namespace Json;

int sum_json(Value val, bool no_red) {
    int sum = 0;
    if (val.isArray()) {
        for (auto v : val) {
            sum += sum_json(v, no_red);
        }
    } else if (val.isObject()) {
        Value::Members members = val.getMemberNames();
        if (no_red) {
            for (auto m : members) {
                if (val[m].isString() && val[m].asString() == "red") {
                    return 0;
                }
            }
        }
        for (auto m : members) {
            sum += sum_json(val[m], no_red);
        }
    } else if (val.isConvertibleTo(ValueType::intValue)) {
        sum = val.asInt();
    }
    return sum;
}

int main() {
    ifstream f("input12.txt");
    Value root;
    f >> root;
    cout << sum_json(root, false) << " " << sum_json(root, true) << endl;
    return 0;
}