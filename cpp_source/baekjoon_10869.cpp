#include <iostream>

using namespace std;

int main(void)
{
    int a = .0;
    int b = .0;

    cin >> a >> b;
    if(a < 0 || a > 10000 || b < 0 || b > 10000) {
        cout << "Invalid input. a(" << a << "); b(" << b << ");" << endl;
        return -1;
    }

	cout << a + b << endl;
	cout << a - b << endl;
    cout << a * b << endl;
    if(b == 0) {
        cout << "Invalid input. b(" << b << ")" << endl;
    }
    else {
        cout.precision(9);
        cout << (double)(a / b) << endl;
    }
    cout << a % b << endl;


	return 0;
}
