#include <iostream>
#include <cstdlib>
#include <vector>
#include <climits>

using namespace std;

int findOptimizingPack(int src)
{
    int result = -1;

    if(src < 5 || src < 3) {
        if(src < 3) {
            return -1;
        }
        if(src % 3 != 0) {
            return -1;
        }
        else {
            return 1;
        }
    }

    int start = src / 5;
    for(int i = start;i > 0;i--) {
        int tmp = src - (5 * i);
        if(tmp < 0) {
            break;
        }
        if(tmp % 3 == 0) {
            result = i + (tmp / 3);
            // cout << "i:result:tmp = " << i << ":" << result << ":" << tmp << endl;
            break;
        }
    }

    if(result == -1) {
        if(src % 3 == 0) {
            result = src / 3;
        }
    }
    return result;
}

int main(void)
{
    enum {
        MIN = 3,
        MAX = 5000,
    };

    int input = 0;
    int result = 0;

    cin >> input;
    if(input < MIN || input > MAX) {
        cout << "Invalid value input(" << input << ");" << endl;
        return -1;
    }

    result = findOptimizingPack(input);
    cout << result << endl;

    return 0;
}
