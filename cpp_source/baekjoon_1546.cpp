#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

int main(void)
{
    enum { COL_SIZE = 1, };
    const int MIN = 0;
    const int MAX = 1000;
    vector< vector<int> > vBuf;
    vector<int> vCol;

    int size = 0;
    double sum = 0.0;
    int max = 0;
    int a[COL_SIZE] = { MAX, };

    cin >> a[0];
    if(a[0] < MIN || a[0] > MAX) {
        cout << "Invalid value a[0](" << a[0] << ");" << endl;
        return -1;
    }

    size = a[0];
    for(int i = 0;i < size;i++) {
        cin >> a[0];
        if(a[0] < MIN || a[0] > MAX) {
            cout << "Invalid value [" << i << "] a[0](" << a[0] << ");" << endl;
            return -1;
        }
        sum += a[0];
        if(max < a[0]) {
            max = a[0];
        }
    }

    cout << fixed;
    cout.precision(7);
    cout << (double)(sum / size) / max * 100.0 << endl;

	return 0;
}