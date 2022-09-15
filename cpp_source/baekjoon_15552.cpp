#include <iostream>
#include <cstdlib>

using namespace std;

int main(void)
{
    const int L_MIN = 0;
    const int L_MAX = 1000000;
    const int N_MIN = 0;
    const int N_MAX = 1000;

    int a = 0;
    int b = 0;
    int loop = 0;

    cin.tie(NULL);
    ios::sync_with_stdio(false);

    cin >> loop;

    if(loop < L_MIN || loop > L_MAX) {
        cout << "Invalid value loop(" << loop << ");" << endl;
        return -1;
    }

    int *buf = new int[loop];

    for(int i = 0;i < loop;i++) {
        cin >> a >> b;
        if(a < N_MIN || a > N_MAX || b < N_MIN || b > N_MAX) {
            cout << "Invalid value [" << i << "] a(" << a << "); b(" << b << ");" << endl;
            delete[] buf;
            return -1;
        }
        *(buf + i) = a + b;
    }

    for(int k = 0;k < loop;k++) {
        cout << *(buf + k) << "\n";
    }
    delete[] buf;

	return 0;
}