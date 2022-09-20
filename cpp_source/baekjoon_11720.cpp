#include <iostream>
#include <cstdlib>
#include <vector>
#include <climits>

using namespace std;

int main(void)
{
    enum {
        COL_SIZE = 1,
        MIN = 0,
        MAX = 100,
    };
    int a[COL_SIZE] = { INT_MIN };
    int size = 0;
    int sum = 0;
    string buf;

    cin >> a[0];
    if(a[0] < MIN || a[0] > MAX) {
        cout << "Invalid value a[0](" << a[0] << ");" << endl;
        return -1;
    }

    size = a[0];
    cin >> buf;
    if(buf.empty() || buf.length() <= 0) {
        cout << "Invalid value buf(" << buf.c_str() << ");" << endl;
        return -1;
    }

    for(int i = 0;i < size;i++) {
        sum += buf[i] - '0';
    }

    cout << sum << endl;

	return 0;
}