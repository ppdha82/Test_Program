#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

int calcNum(int oriNum)
{
    int result = 0;
    result = (oriNum % 10) * 10;
    result += ((oriNum % 10) + (oriNum / 10)) % 10;
    return result;
}

int main(void)
{
    enum { COL_SIZE = 1, };
    const int MIN = 0;
    const int MAX = 100;
    int count = 0;
    int result = 0;
    int a[COL_SIZE] = { MAX };

    cin >> a[0];
    if(a[0] < MIN || a[0] > MAX) {
        cout << "Invalid value a[0](" << a[0] << ");" << endl;
        return -1;
    }

    result = a[0];
    do {
        result = calcNum(result);
        count++;
    } while(a[0] != result);

    cout << count << endl;

	return 0;
}