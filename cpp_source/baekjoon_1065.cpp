#include <iostream>
#include <cstdlib>
#include <vector>
#include <climits>

using namespace std;

int findHansuNumbers(int value)
{
    if(value <= 0) {
        cout << "value is invalid (" << value << ");" << endl;
        return -1;
    }
    int count = 0;
    enum {
        DIVIDE_NUM = 10,
    };
    vector<int> tmp;
    int divider = DIVIDE_NUM;

    for(int i = 1;i <= value;i++) {
        tmp.clear();
        tmp.push_back(i % DIVIDE_NUM);
        divider = DIVIDE_NUM;
        while(i / divider != 0) {
            tmp.push_back((i / divider) % DIVIDE_NUM);
            // cout << "[" << i << "] " << selfSum << "; " << divider << "; " << endl;
            divider *= DIVIDE_NUM;
        }

        if(tmp.size() <= 2) {
            count++;
        }
        else {
            // cout << "[" << i << "] tmp.size() = " << tmp.size() << ";" << endl;
            int diff = tmp.at(0) - tmp.at(1);
            int foundHansu = 1;
            for(int j = 1;j < tmp.size() - 1;j++) {
                if(diff != (tmp.at(j) - tmp.at(j + 1))) {
                    foundHansu = 0;
                    break;
                }
            }
            if(foundHansu == 1) {
                count++;
            }
        }
    }
    return count;
}

int main(void)
{
    enum {
        COL_SIZE = 1,
        MIN = 0,
        MAX = 10000,
    };
    int a[COL_SIZE] = { INT_MAX };
    int hansuCount = 0;
    int value = 0;

    cin >> a[0];
    if(a[0] < MIN || a[0] > MAX) {
        cout << "Invalid value a[0](" << a[0] << ");" << endl;
        return -1;
    }

    value = a[0];
    hansuCount = findHansuNumbers(value);

    cout << hansuCount << endl;

	return 0;
}