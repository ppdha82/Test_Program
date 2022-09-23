#include <iostream>
#include <cstdlib>
#include <vector>
#include <climits>

using namespace std;

void appendNumberToString(int number, string &src)
{
    do {
        string tmp;
        tmp.push_back(number % 10 + '0');
        src.insert(0, tmp);
        number /= 10;
    } while(number != 0);
}
// fraction rule
// 1/1: 1(1) => 1/2~2/1: 3(4) => 1/3~3/1: 5(9) => 1/4~4/1: 7(16) ...
// count odd: denominator, even: numerator
string findFraction(int src)
{
    string result;
    int count = 1;
    int increaser = 1;
    int lastNumber = 1;
    int remainNumber = src;
    int number = 0;

    for(int i = 0;;i++) {
        if(src <= lastNumber) {
            count = i;
            // cout << "inc = " << increaser << "; last = " << lastNumber << endl;
            break;
        }

        if(remainNumber > increaser) {
            remainNumber -= increaser;
        }
        // cout << "remain:increase = " << remainNumber << ":" << increaser << endl;
        increaser++;
        lastNumber += increaser;
        
    }

    if(count % 2 == 0) {
        // numberator > denominator
        number = remainNumber;
        appendNumberToString(number, result);
        result.insert(0, "/");
        number = count + 2 - (remainNumber);
        appendNumberToString(number, result);
        // cout << "count:lastNumber:increaser:remainNumber = " << count << ":" << lastNumber << ":" << increaser << ":" << remainNumber << endl;
        // cout << count + 2 - (remainNumber) << "/" << remainNumber << endl;
    }
    else {
        // numberator < denominator
        number = count + 2 - (remainNumber);
        appendNumberToString(number, result);
        result.insert(0, "/");
        number = remainNumber;
        appendNumberToString(number, result);
        // cout << "count:lastNumber:increaser:remainNumber = " << count << ":" << lastNumber << ":" << increaser << ":" << remainNumber << endl;
        // cout << remainNumber << "/" << count + 2 - (remainNumber) << endl;
    }
    return result;
}

int main(void)
{
    enum {
        MIN = 1,
        MAX = 10000000,
    };

    string result;
    int input = 0;

    cin >> input;
    if(input < MIN || input > MAX) {
        cout << "Invalid value input(" << input << ");" << endl;
        return -1;
    }

    result = findFraction(input);
    cout << result << endl;

    return 0;
}
