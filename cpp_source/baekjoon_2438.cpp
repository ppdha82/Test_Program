#include <iostream>
#include <cstdlib>

using namespace std;

int main(void)
{
    const int MIN = 1;
    const int MAX = 100;

    int a = 0;

    cin >> a;
    if(a < MIN || a > MAX) {
        cout << "Invalid value a(" << a << ");" << endl;
        return -1;
    }

    for(int k = 0;k < a;k++) {
        for(int j = 0;j < k + 1;j++) {
            cout << "*";
        }
        cout << endl;
    }

	return 0;
}