#include <iostream>

using namespace std;

int main(void)
{
    double a = .0;
    double b = .0;

    cin >> a >> b;
    if(a < .0 || a > 10.0 || b <= .0 || b > 10.0) {
        cout << "Invalid input. a(" << a << "); b(" << b << ");" << endl;
        return -1;
    }

    cout << fixed;
    cout.precision(9);
    cout << a / b << endl;

	return 0;
}
