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

    int **buf = new int*[loop];
    for(int j = 0;j < loop;j++) {
        buf[j] = new int[2];
    }

    for(int i = 0;i < loop;i++) {
        cin >> a >> b;
        if(a < MIN || a > MAX || b < MIN || b > MAX) {
            cout << "Invalid value [" << i << "] a(" << a << "); b(" << b << ");" << endl;
            return -1;
        }

        buf[i][0] = a;
        buf[i][1] = b;
    }

    for(int k = 0;k < loop;k++) {
        cout << "Case #" << k + 1 << ": " << buf[k][0] << " + " << buf[k][1] << " = " << buf[k][0] + buf[k][1] << endl;
    }

    for(int j = 0;j < loop;j++) {
        delete[] buf[j];
    }
    delete[] buf;

	return 0;
}