#include <iostream>
#include <cstdlib>

using namespace std;

int main(void)
{
    const int H_MIN = 0;
    const int H_MAX = 24;
    const int M_MIN = 0;
    const int M_MAX = 60;
    const int MIN = 0;
    const int MAX = 1000;

    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;

    cin >> a >> b >> c;

    if(a < H_MIN || a >= H_MAX || b < M_MIN || b >= M_MAX || c < MIN || c > MAX) {
        cout << "Invalid value a(" << a << "); b(" << b << "); c(" << c << ");" << endl;
        return -1;
    }

    if(c > M_MAX) {
        d = (c / M_MAX) % H_MAX;
        c %= M_MAX;
    }

    b += c;
    if(b >= M_MAX) {
        b -= M_MAX;
        if(a >= 23) {
            a = 0;
        }
        else {
            a++;
        }
    }
    a = (a + d) % H_MAX;

    cout << a << " " << b << endl;

	return 0;
}