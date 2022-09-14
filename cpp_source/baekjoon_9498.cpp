#include <iostream>
#include <cstdlib>

using namespace std;

int main(void)
{
    enum {
        _A = 90,
        _B = 80,
        _C = 70,
        _D = 60,
    };
    const int MIN = 0;
    const int MAX = 100;
    int a = 0;

    cin >> a;

    if(a < MIN || a > MAX) {
        cout << "Invalid value a(" << a << ");" << endl;
        return -1;
    }

    if(a >= _A) {
        cout << "A" << endl;
    }
    else if(a >= _B) {
        cout << "B" << endl;
    }
    else if(a >= _C) {
        cout << "C" << endl;
    }
    else if(a >= _D) {
        cout << "D" << endl;
    }
    else {
        cout << "F" << endl;
    }

	return 0;
}