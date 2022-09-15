#include <iostream>
#include <cstdlib>

using namespace std;

int main(void)
{
    const int MIN = 0;
    const int MAX = 10000;

    int a = 0;
    int sum = 0;

    cin >> a;
    if(a < MIN || a > MAX) {
        cout << "Invalid value a(" << a << ");" << endl;
        return -1;
    }

#if 0
    for(int i = 1;i <= a;i++) {
        sum += i;
    }
#else
    int half = (1 + a) / 2;

    if((1 + a) % 2 == 0) {
        sum = ((1 + a) * half) - half;
    }
    else {
        sum = (1 + a) * half;
    }
#endif
    cout << sum << endl;

	return 0;
}