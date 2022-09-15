#include <iostream>
#include <cstdlib>

using namespace std;

int main(void)
{
    const int MIN = 1;
    const int MAX = 100;
    string star;

    int a = 0;

    cin >> a;
    if(a < MIN || a > MAX) {
        cout << "Invalid value a(" << a << ");" << endl;
        return -1;
    }

    for(int k = 0;k < a;k++) {
        for(int j = 0;j < (k + 1);j++) {
            star.append("*");
        }
        cout.width(a);
        cout << star.c_str() << endl;
        star.clear();
    }

	return 0;
}