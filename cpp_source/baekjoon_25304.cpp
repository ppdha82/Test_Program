#include <iostream>
#include <cstdlib>

using namespace std;

int main(void)
{
    const int N_MIN = 0;
    const int N_MAX = 100;
    const int R_MIN = 0;
    const int R_MAX = 1000000000;

    int a = 0;
    int b = 0;
    int loop = 0;
    int receipt_sum = 0;
    int sum = 0;

    cin >> receipt_sum >> loop;

    if(loop < N_MIN || loop > N_MAX || receipt_sum < R_MIN || receipt_sum > R_MAX) {
        cout << "Invalid value loop(" << loop << "); receipt_sum(" << receipt_sum << ");" << endl;
        return -1;
    }

    int *buf = new int[loop];

    for(int i = 0;i < loop;i++) {
        cin >> a >> b;
        if(a < R_MIN || a > R_MAX || b < N_MIN || b > N_MAX) {
            cout << "Invalid value [" << i << "] a(" << a << "); b(" << b << ");" << endl;
            delete[] buf;
            return -1;
        }
        *(buf + i) = a * b;
    }

    for(int k = 0;k < loop;k++) {
        sum += *(buf + k);
    }

    if(sum == receipt_sum) {
        cout << "Yes" << endl;
    }
    else {
        cout << "No" << endl;
    }
    delete[] buf;

	return 0;
}