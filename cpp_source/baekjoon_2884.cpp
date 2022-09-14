#include <iostream>
#include <cstdlib>

using namespace std;

int main(void)
{
    const int H_MIN = 0;
    const int H_MAX = 24;
    const int M_MIN = 0;
    const int M_MAX = 60;
    const int M_ADJ = 45;
    int a = 0;
    int b = 0;

    cin >> a >> b;

    if(a < H_MIN || a >= H_MAX || b < M_MIN || b >= M_MAX) {
        cout << "Invalid value a(" << a << "); b(" << b << ");" << endl;
        return -1;
    }

    if(b >= M_ADJ) {
        b -= M_ADJ;
    }
    else {
        b = M_MAX + b - M_ADJ;
        if(a > 0) {
            a--;
        }
        else {
            a = H_MAX - 1;
        }
    }

    cout << a << " " << b << endl;

	return 0;
}