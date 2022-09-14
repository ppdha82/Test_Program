#include <iostream>
#include <cstdlib>

using namespace std;

int main(void)
{
    const int MIN = -1000;
    const int MAX = 1000;
    int a = 0;
    int b = 0;

    cin >> a >> b;

    if(a < MIN || a > MAX || b < MIN || b > MAX || a == 0 || b == 0) {
        cout << "Invalid value a(" << a << "); b(" << b << ");" << endl;
        return -1;
    }

    if(a < 0 && b < 0) {
        cout << "3" << endl;
    }
    else if(a < 0 && b > 0) {
        cout << "2" << endl;
    }
    else if(a > 0 && b < 0) {
        cout << "4" << endl;
    }
    else  {
        cout << "1" << endl;
    }

	return 0;
}