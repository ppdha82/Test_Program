#include <iostream>
#include <cstdlib>

using namespace std;

int countSameNumber(int a, int b, int c)
{
    int count = 0;
    if(a == b) {
        count++;
        if(b == c) {
            count++;
        }
    }
    else if(b == c) {
        count++;
        if(a == c) {
            count++;
        }
    }
    else if(a == c) {
        count++;
        if(b == c) {
            count++;
        }
    }
    return count;
}

int findBiggerNumber(int a, int b, int c)
{
    if(a > b) {
        if(a > c) {
            return a;
        }
    }
    else {
        if(b > c) {
            return b;
        }
    }
    return c;
}

int findSameNumber(int a, int b, int c)
{
    int number = 0;

    if(a == b) {
        number = a;
    }
    else if(b == c) {
        number = b;
    }
    else if(c == a) {
        number = c;
    }
    else {
        number = findBiggerNumber(a, b, c);
    }

    return number;
}

int main(void)
{
    const int MIN = 1;
    const int MAX = 6;

    int a = 0;
    int b = 0;
    int c = 0;
    int sameCount = 0;
    int sameNumber = 0;

    cin >> a >> b >> c;

    if(a < MIN || a > MAX || b < MIN || b > MAX || c < MIN || c > MAX) {
        cout << "Invalid value a(" << a << "); b(" << b << "); c(" << c << ");" << endl;
        return -1;
    }

    sameNumber = findSameNumber(a, b, c);
    sameCount = countSameNumber(a, b, c);

    if(sameCount == 2) {
        cout << 10000 + 1000 * sameNumber << endl;
    }
    else if(sameCount == 1) {
        cout << 1000 + 100 * sameNumber << endl;
    }
    else {
        cout << 100 * sameNumber << endl;
    }

	return 0;
}