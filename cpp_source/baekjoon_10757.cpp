#include <iostream>
#include <cstdlib>
#include <vector>
#include <climits>
#include <string>
#include <cmath>

using namespace std;

vector<int> calcBigNumber(vector<string>& src)
{
    int size = 0;
    vector<int> result;
    vector<string> buf;
    vector<vector<string>> bufs;
    string test;

    size = INT_MAX;
    test = to_string(size);
    int cutNumber = test.length() - 1;

    // cout << "test:size:cutNumber = " << test << ":" << test.size() << ":" << cutNumber << endl;
    for(int j = 0;j < src.size();j++) {
        int lastNumber = src.at(j).size();
        int cutOffset = 0;
        buf.clear();
        for(int i = 1;;i++) {
            if(lastNumber - cutNumber < 0) {
                cutOffset = cutNumber - lastNumber;
                lastNumber = cutNumber;
            }
            string tmp = src.at(j).substr(lastNumber - cutNumber, cutNumber - cutOffset);
            buf.push_back(tmp);
            // cout << "(i = " << i << ") tmp:buf:lastNumber:cutNumber = " << tmp << ":" << buf.back() << ":" << lastNumber << ":" << cutNumber << endl;
            lastNumber -= cutNumber;
            if(lastNumber <= 0) {
                // cout << "lastNumber:src.size() = " << lastNumber << ":" << src.at(j).size() << endl;
                break;
            }
        }
        bufs.push_back(buf);
    }

    for(int k = 0;k < bufs.size();k++) {
        vector<string> tmpResult = bufs.at(k);
        for(int m = 0;m < tmpResult.size();m++) {
            // cout << "(k = " << k << "; m = " << m << ") bufs = " << bufs.at(k).at(m) << endl;
        }
    }

    int j = 0;
    int tmp1 = 0;
    int tmp2 = 0;
    int sumFlag = 0;
    int sumMax = pow(10, cutNumber);

    while(1) {
        if(j >= bufs.at(0).size() && j >= bufs.at(1).size()) {
            if(sumFlag > 0) {
                result.push_back(1);
            }
            break;
        }
        if(j < bufs.at(0).size()) {
            tmp1 = stoi(bufs.at(0).at(j));
        }
        else {
            tmp1 = 0;
        }
        if(j < bufs.at(1).size()) {
            tmp2 = stoi(bufs.at(1).at(j));
        }
        else {
            tmp2 = 0;
        }
        int sum = tmp1 + tmp2 + sumFlag;
        sumFlag = 0;
        if(sum >= sumMax) {
            sum -= sumMax;
            sumFlag = 1;
        }
        // cout << "(j = " << j << ") tmp1:tmp2:sum:sumFlag:sumMax = " << tmp1 << ":" << tmp2 << ":" << sum << ":" << sumFlag << ":" << sumMax << endl;
        j++;
        result.push_back(sum);
    }

    return result;
}

int main(void)
{
    enum {
        SIZE = 2,
        MIN = 0,
        MAX = INT_MAX,
    };
    int size = 0;
    string test;
    size = INT_MAX;
    test = to_string(size);

    string input;
    vector<string> bufs;
    vector<int> result;

    for(int i = 0;i < SIZE;i++) {
        cin >> input;
        if(input.length() <= MIN) {
            cout << "Invalid value input(" << input << ");" << endl;
            return -1;
        }
        bufs.push_back(input);
    }

    result = calcBigNumber(bufs);
    for(int j = result.size() - 1;j >= 0 ;j--) {
        // cout << "(j = " << j << ") = " << result.at(j) << endl;
        if(j == result.size() - 1) {
            cout.width(0);
        }
        else {
            cout.width(test.length() - 1);
        }
        cout.fill('0');
        cout << right << result.at(j);
    }
    cout << endl;
    for(int j = result.size() - 1;j >= 0 ;j--) {
        // cout << "(j = " << j << ") = " << result.at(j) << endl;
    }
    return 0;
}
