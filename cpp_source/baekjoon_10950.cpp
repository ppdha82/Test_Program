#include <iostream>
#include <cstdlib>

using namespace std;

int main(void)
{
    const int MIN = 0;
    const int MAX = 10;

    int a = 0;
    int b = 0;
    int loop = 0;

    cin >> loop;

    if(loop < MIN) {
        cout << "Invalid value loop(" << loop << ");" << endl;
        return -1;
    }

    int *buf = new int[loop];

    for(int i = 0;i < loop;i++) {
        cin >> a >> b;
        if(a < MIN || a > MAX || b < MIN || b > MAX) {
            cout << "Invalid value [" << i << "] a(" << a << "); b(" << b << ");" << endl;
            delete[] buf;
            return -1;
        }
        *(buf + i) = a + b;
    }

    for(int k = 0;k < loop;k++) {
        cout << *(buf + k) << endl;
    }
    delete[] buf;

	return 0;
}