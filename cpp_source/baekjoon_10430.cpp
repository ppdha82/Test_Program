#include <iostream>
#include <cstdlib>

using namespace std;

int main(void)
{
	int a = 0;
	int b = 0;
	int c = 0;

    cin >> a >> b >> c;

    if(a < 2 || a > 10000 || b < 2 || b > 10000 || c < 2 || c > 10000) {
        cout << "Range Over a(" << a << "); b(" << b << "); c(" << c << ");" << endl;
        return -1;
    }

	cout << (a + b) % c << endl;
	cout << ((a % c) + (b % c)) % c << endl;
	cout << (a * b) % c << endl;
	cout << ((a % c) * (b % c)) % c << endl;

	return 0;
}
