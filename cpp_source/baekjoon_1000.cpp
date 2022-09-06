#include <iostream>
#include <cstdlib>

using namespace std;

int main(void)
{
	int a = 0;
	int b = 0;

    cin >> a >> b;

    if(a < 0 || a > 10 || b < 0 || b > 10) {
        cout << "Range Over a(" << a << "); b(" << b << ")" << endl;
        return -1;
    }

	cout << a + b << endl;

	return 0;
}
