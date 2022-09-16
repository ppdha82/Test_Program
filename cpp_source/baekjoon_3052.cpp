#include <iostream>
#include <cstdlib>
#include <vector>
#include <climits>

using namespace std;

int main(void)
{
    enum { COL_SIZE = 1, LOOP_COUNT = 10, };
    const int MIN = 0;
    const int MAX = 1000;
    int a[COL_SIZE] = { INT_MAX };
    int count = 0;
    int diff_count = 0;
    int *buf;
    int diff_value = 0;

    buf = new int[LOOP_COUNT];
    for(int i = 0;i < LOOP_COUNT;i++) {
        cin >> a[0];
        if(a[0] < MIN || a[0] > MAX) {
            cout << "Invalid value a[0](" << a[0] << ");" << endl;
            return -1;
        }

        buf[i] = a[0] % 42;
    }

    for(int j = 0;j < LOOP_COUNT;j++) {
        if(buf[j] < 0) {
            continue;
        }
        diff_value = buf[j];
        buf[j] = -1;
        diff_count++;
        for(int k = j;k < LOOP_COUNT;k++) {
            if(diff_value == buf[k]) {
                buf[k] = -1;
            }
        }
    }

    cout << diff_count << endl;

	return 0;
}