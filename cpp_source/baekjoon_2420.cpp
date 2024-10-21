#include <iostream>
#include <cstdlib>
#include <climits>
#include <ctime>

using namespace std;

int main(void)
{
    enum {
        COL_SIZE = 2,
    };

    const long long MIN = -2000000000;
    const long long MAX = 2000000000;

    int size = 0;
    long long diff = 0;
    long long a[COL_SIZE] = { 0, };

    cin.tie(NULL);
    ios::sync_with_stdio(false);

    size = COL_SIZE;
    for(int i = 0;i < size;i++) {
        cin >> a[i];
        if(a[i] < MIN || a[i] > MAX) {
            cout << "Invalid value a[" << i << "](" << a[i] << ");" << endl;
            return -1;
        }
    }

    diff = a[0] - a[1];
    if (diff < 0) {
        diff = -diff;
    }

    cout << diff << "\n";

    return 0;
}