#include <iostream>
#include <cstdlib>

using namespace std;

int main(void)
{
    int a = 0;

    cin >> a;

    if(a < 1000 || a > 3000) {
        cout << "Invalid value: a(" << a << ")" << endl;
        return -1;
    }

    // bulgi => seogi
	cout << a - 543 << endl;

	return 0;
}
