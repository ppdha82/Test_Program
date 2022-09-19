#include <iostream>
#include <cstdlib>

using namespace std;

int main(void)
{
    const int MIN = 0;
    const int MAX = 9;
    int a = 0;
 
    cin >> a;

    if(a < MIN || a > MAX) {
        cout << "Invalid value a(" << a << ");" << endl;
        return -1;
    }

    for(int i = 1;i <= MAX;i++) {
        cout << a << " * " << i << " = " << a * i << endl;
    }

	return 0;
}