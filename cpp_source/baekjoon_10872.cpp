#include <iostream>
#include <cstdlib>
#include <vector>
#include <climits>
#include <string>

using namespace std;

int calcFactorial(int src)
{
    int result = 1;

    if(src == 0) {
        return 1;
    }

    for(int i = 1;i <= src;i++) {
        result *= i;
    }

    return result;
}

int main(void)
{
    enum {
        MIN = 0,
        MAX = 12,
    };
    int input = 0;
    int result;

    
    cin >> input;
    if(input < MIN || input > MAX) {
        cout << "Invalid value input(" << input << ");" << endl;
        return -1;
    }

    result = calcFactorial(input);
    cout << result << '\n';

    return 0;
}
