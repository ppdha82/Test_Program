#include <iostream>
#include <cstdlib>
#include <vector>
#include <climits>
#include <string>

using namespace std;

int calcFibonacci(int src)
{
    int result = 0;
    int num1 = 0;
    int num2 = 1;

    if(src == 1) {
        return 1;
    }

    if(src == 0) {
        return 0;
    }

    for(int i = 0;i < src - 1;i++) {
        result = num1 + num2;
        num1 = num2;
        num2 = result;
    }

    return result;
}

int main(void)
{
    enum {
        MIN = 0,
        MAX = 20,
    };
    int input = 0;
    int result;

    
    cin >> input;
    if(input < MIN || input > MAX) {
        cout << "Invalid value input(" << input << ");" << endl;
        return -1;
    }

    result = calcFibonacci(input);
    cout << result << '\n';

    return 0;
}
