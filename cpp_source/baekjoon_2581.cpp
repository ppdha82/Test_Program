#include <iostream>
#include <cstdlib>
#include <vector>
#include <climits>
#include <string>

using namespace std;

vector<int> findPrimeNumber(vector<int>& src)
{
    vector<int> result;
    int count = 0;
    int minValue = INT_MAX;
    int sum = 0;

    int startNumber = src.at(0);
    int endNumber = src.at(1);

    for(int i = startNumber;i <= endNumber;i++) {
        if(i == 1) {
            continue;
        }
        count = 0;
        for(int j = 2;j <= i / 2;j++) {
            if(i % j == 0) {
                count++;
            }
            if(count > 1) {
                break;
            }
            // cout << "i:j:count = " << i << ":" << j << ":" << count << endl;
        }
        if(count == 0) {
            if(i < minValue) {
                minValue = i;
            }
            sum += i;
            // cout << "i:sum:minValue = " << i << ":" << sum << ":" << minValue << endl;
        }
    }
    if(minValue == INT_MAX) {
        result.push_back(-1);
    }
    else {
        result.push_back(sum);
        result.push_back(minValue);
    }
    return result;
}

int main(void)
{
    enum {
        SIZE = 2,
        MIN = 0,
        MAX = 10000,
    };
    int input = 0;
    vector<int> result;
    vector<int> buf;

    
    for(int i = 0;i < SIZE;i++) {
        cin >> input;
        if(input < MIN || input > MAX) {
            cout << "Invalid value input(" << input << ");" << endl;
            return -1;
        }

        buf.push_back(input);
    }
    result = findPrimeNumber(buf);
    for(int j = 0;j < result.size();j++) {
        cout << result.at(j) << endl;
    }

    return 0;
}
