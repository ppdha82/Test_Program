#include <iostream>
#include <cstdlib>
#include <vector>
#include <climits>

using namespace std;

int main(void)
{
    enum {
        COL_SIZE = 1,
        MIN = 0,
        MAX = 255,
    };
    char a[COL_SIZE] = { CHAR_MIN };
    int hansuCount = 0;
    int value = 0;

    cin >> a[0];
    if(a[0] < MIN || a[0] > MAX) {
        cout << "Invalid value a[0](" << a[0] << ");" << endl;
        return -1;
    }

    value = a[0];
    if((value >= '0' && value <= '9') || (value >= 'A' && value <= 'z')) {
        cout << (int)value << endl;
    }
    else {
        cout << "[ELSE]: " << value << endl;
    }

	return 0;
}