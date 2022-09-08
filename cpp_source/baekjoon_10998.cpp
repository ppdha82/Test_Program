#include <iostream>

using namespace std;

int main(void)
{
    int a = 0;
    int b = 0;

    cin >> a >> b;
    if(a < 0 || a > 10 || b < 0 || b > 10) {
        cout << "Invalid input. a(" << a << "); b(" << b << ");" << endl;
        return -1;
    }

    cout << a * b << endl;

	return 0;
}
