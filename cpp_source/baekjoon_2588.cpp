#include <iostream>
#include <cstdlib>

using namespace std;

int main(void)
{
	int a = 0;
	int b = 0;

    cin >> a >> b;

    if(a < 100 || a > 1000 || b < 100 || b > 1000) {
        cout << "Range Over a(" << a << "); b(" << b << ")" << endl;
        return -1;
    }

    cout << a * (b % 10) << endl;
    cout << a * ((b / 10) % 10) << endl;
    cout << a * (b / 100) << endl;
    cout << a * b << endl;

	return 0;
}
