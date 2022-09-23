#include <iostream>
#include <cstdlib>
#include <vector>
#include <climits>

using namespace std;

int calcBreakEven(vector<int>& src)
{
    enum {
        FIXED_COST,
        VAR_COST,
        SALES_PRICE,
    };
    vector<char> store;
    int result = 0;
    int profit = 0;

    profit = src.at(SALES_PRICE) - src.at(VAR_COST);
    if(profit <= 0) {
        // cout << "No way break-even point !!!" << endl;
        return -1;
    }

    result = src.at(FIXED_COST) / profit;
    result++;

    // cout << endl;
    return result;
}

int main(void)
{
    enum {
        MIN = 0,
        MAX = INT_MAX,
        SIZE = 3,
    };
    vector<int> buf;
    int result = 0;
    int input = 0;

    for(int i = 0;i < SIZE;i++) {
        cin >> input;
        if(input < MIN || input > MAX) {
            cout << "Invalid value input(" << input << ");" << endl;
            return -1;
        }
        // cout << "(i = " << i << "); " << input << endl;
        buf.push_back(input);
    }

    result = calcBreakEven(buf);
    cout << result << endl;

    return 0;
}
