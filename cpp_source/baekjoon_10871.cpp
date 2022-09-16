#include <iostream>
#include <cstdlib>

using namespace std;

int main(void)
{
    const int MIN = 1;
    const int MAX = 10000;
    string star;

    int a = 0;
    int b = 0;
    int *buf = NULL;
    int size = 0;
    int num = 0;

    cin >> a >> b;
    if(a < MIN || a > MAX || b < MIN || b > MAX) {
        cout << "Invalid value a(" << a << "); b(" << b << ");" << endl;
        return -1;
    }

    size = a;
    num = b;

    buf = new int[size];
    for(int i = 0;i < size;i++) {
        cin >> b;
        if(b < MIN || b > MAX) {
            cout << "Invalid value [" << i << "] b(" << b << ");" << endl;
            return -1;
        }
        buf[i] = b;
    }

    for(int k = 0;k < size;k++) {
        if(buf[k] < num) {
            cout << buf[k] << " ";
        }
    }
    cout << endl;

	return 0;
}