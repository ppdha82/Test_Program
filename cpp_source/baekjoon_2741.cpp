#include <iostream>
#include <cstdlib>
#include <climits>
#include <ctime>

using namespace std;

int main(void)
{
    enum {
        COL_SIZE = 1,
    };

    const long long MIN = 1;
    const long long MAX = 100000;

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

    for (int j = 1;j <= a[0];j++) {
        cout << j << "\n";
    }

    return 0;
}