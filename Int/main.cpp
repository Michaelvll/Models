#include <iostream>
#include "Int.hpp"
using namespace std;

int main() {
    Int a, b;
    // cout << a << endl;
    // a = s;
    // cout << a;

    cin >> a >> b;
    // cout << a + b << endl;
    // cout << a - b << endl;
    // cout << (a += b) << endl;
    cout << (a %= b) << endl;

    return 0;
}