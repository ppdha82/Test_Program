#include <iostream>
#include <cstdlib>
#include <climits>
#include <ctime>

using namespace std;

int main(void)
{
    enum {
        COL_SIZE = 3,
    };

    const unsigned long long MIN = 0;
    const unsigned long long MAX = 1000000000000;

    int size = 0;
    unsigned long long sum = 0;
    unsigned long long a[COL_SIZE] = { 0, };

    cin.tie(NULL);
    ios::sync_with_stdio(false);

    size = COL_SIZE;
    for(int i = 0;i < size;i++) {
        cin >> a[i];
        if(a[i] <= MIN || a[i] > MAX) {
            cout << "Invalid value a[" << i << "](" << a[i] << ");" << endl;
            return -1;
        }
        sum += a[i];
    }

    cout << sum << "\n";

    return 0;
}