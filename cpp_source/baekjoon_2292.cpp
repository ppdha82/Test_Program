#include <iostream>
#include <cstdlib>
#include <vector>
#include <climits>

using namespace std;

// bee house
// 1 => 6(7) => 12(19) => 18(37) ...
// count of bee box in a line: 6 * n
// last number in a line: fibonacci
int findRoute(int src)
{
    enum {
        MULTIPLIER = 6,
    };
    int result = 0;
    int multiplier = 1;
    int lastNumber = 0;

    if(src == 1) {
        return 1;
    }
    else if(src <= 1 + MULTIPLIER) {
        return 2;
    }

    multiplier = MULTIPLIER;
    lastNumber += 1 + multiplier;
    for(int i = 2;;i++) {
        multiplier = MULTIPLIER * i;
        lastNumber += multiplier;
        if(lastNumber >= src) {
            result = i + 1;
            break;
        }
    }

    return result;
}

int main(void)
{
    enum {
        MIN = 1,
        MAX = 1000000000,
    };
    vector<int> buf;
    int result = 0;
    int input = 0;

    cin >> input;
    if(input < MIN || input > MAX) {
        cout << "Invalid value input(" << input << ");" << endl;
        return -1;
    }

    result = findRoute(input);
    cout << result << endl;

    return 0;
}
