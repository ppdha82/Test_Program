#include <iostream>
#include <cstdlib>
#include <climits>

using namespace std;

int main(void)
{
    enum { COL_SIZE = 1, };
    const int MIN = 0;
    const int MAX = 100;
    int a[COL_SIZE] = { INT_MAX };
    int count = 0;
    int max_count = 0;
    int max_value = INT_MIN;

    while(!cin.eof()) {
        cin >> a[0];
        if(a[0] < MIN || a[0] > MAX) {
            cout << "Invalid value a[0](" << a[0] << ");" << endl;
            return -1;
        }

        count++;
        if(a[0] > max_value) {
            max_value = a[0];
            max_count = count;
        }
    }

    cout << max_value << " " << max_count << endl;

	return 0;
}