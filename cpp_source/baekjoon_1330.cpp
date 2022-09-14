#include <iostream>
#include <cstdlib>

using namespace std;

int main(void)
{
    const int MIN = -10000;
    const int MAX = 10000;
    int a = 0;
    int b = 0;

    cin >> a >> b;

    if(a < MIN || a > MAX || b < MIN || b > MAX) {
        cout << "Invalid value a(" << a << "); b(" << b << ");" << endl;
        return -1;
    }

    if(a > b) {
        cout << ">" << endl;
    }
    else if(a < b) {
        cout << "<" << endl;
    }
    else {
        cout << "==" << endl;
    }

	return 0;
}