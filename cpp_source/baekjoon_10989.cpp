#include <iostream>
#include <cstdlib>
#include <vector>
#include <climits>
#include <string>

using namespace std;

void fillSameNumber(int number, int* orig)
{
    int index = -1;

    orig[number]++;
#if defined(__DEBUG_ON__)
    cout << "[" << __FILE__ << ":" << __LINE__ << "] number:orig = " << number << ":" << orig[number] << "\n";
#endif  /* __DEBUG_ON__ */
}

int main(void)
{
    enum {
        MIN = 0,
        MAX = 10000000,
        N_MIN = 1,
        N_MAX = 10000,
    };

    int input = -1;
    int* orig;
    int size = 0;

    cin.tie(NULL);
    ios::sync_with_stdio(false);

    cin >> input;
    if(input < MIN || input > MAX) {
        cout << "Invalid value input(" << input << ");" << endl;
        return -1;
    }

    size = input;
    orig = new int[N_MAX + 1];

    for(int i = 0;i < size;i++) {
        cin >> input;
        if(input < N_MIN || input > N_MAX) {
            cout << "Invalid value input(" << input << ");" << endl;
            return -1;
        }
        fillSameNumber(input, orig);
    }
#if defined(__DEBUG_ON__)
    for(int m = 0;m < N_MAX;m++) {
        if(orig[m] != 0) {
            cout << "[" << __FILE__ << ":" << __LINE__ << "] m:orig = " << m << ":" << orig[m] << "\n";
        }
    }
#endif  /* __DEBUG_ON__ */
    for(int n = 1;n <= N_MAX;n++) {
        if(orig[n] == 0) {
            continue;
        }
        for(int p = 0;p < orig[n];p++) {
            cout << n << "\n";
        }
    }

    return 0;
}
