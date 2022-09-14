#include <iostream>
#include <cstdlib>

using namespace std;

int main(void)
{
    const int MIN = 0;
    const int MAX = 4000;
    int a = 0;

    cin >> a;

    if(a < MIN || a > MAX) {
        cout << "Invalid value a(" << a << ");" << endl;
        return -1;
    }

    if(a % 4 != 0) {
        cout << "0" << endl;
    }
    else if(a % 100 == 0 && a % 400 != 0) {
        cout << "0" << endl;
    }
    else {
        cout << "1" << endl;
    }

	return 0;
}