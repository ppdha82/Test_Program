#include <iostream>
#include <cstdlib>
#include <vector>
#include <climits>

using namespace std;

void convertDigit(int *dst, int *src)
{
    enum {
        DIVIDER = 10,
    };
    int _divider = 1;
    int _multiplier = 100;
    *dst = (*src % DIVIDER) * _multiplier;
    // cout << *dst << "; " << (*src % DIVIDER) * _multiplier <<endl;
    _divider *= DIVIDER;
    _multiplier /= DIVIDER;
    *dst += ((*src / _divider) % DIVIDER) * _multiplier;
    // cout << *dst << "; " << ((*src / _divider) % DIVIDER) * _multiplier <<endl;
    _multiplier /= DIVIDER;
    _divider *= DIVIDER;
    *dst += ((*src / _divider) % DIVIDER) * _multiplier;
    // cout << *dst << "; " << ((*src / _divider) % DIVIDER) * _multiplier <<endl;
}

int main(void)
{
    enum {
        MIN = 111,
        MAX = 999,
        SIZE = 2,
    };
    int input[SIZE];
    int count = 0;
    int result[SIZE];

    cin >> input[0] >> input[1];
    if(input[0] < MIN || input[0] > MAX || input[1] < MIN || input[1] > MAX) {
        cout << "Invalid value buf(" << input[0] << ", " << input[1] << ");" << endl;
        return -1;
    }

    for(int i = 0;i < SIZE;i++) {
        convertDigit(&result[i], &input[i]);
        // cout << "(" << i << ")" << "result = " << result[i] << "; input = " << input[i] << ";" << endl;
    }

    cout << ((result[0]>result[1])?result[0]:result[1]) << endl;
    return 0;
}
