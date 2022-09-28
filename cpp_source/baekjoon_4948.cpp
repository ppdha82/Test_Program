#include <iostream>
#include <cstdlib>
#include <vector>
#include <climits>
#include <string>

using namespace std;

vector<int> findSquareNumber(int number)
{
    vector<int> result;

    for(int j = 2;j <= number;j++) {
        int found = 0;
        for(int m = 2;m <= j / 2;m++) {
            if(j % m == 0) {
                found = 1;
                break;
            }
        }
        if(found == 0) {
            result.push_back(j);
        }
    }
#if 0
    for(int k = 0;k < result.size();k++) {
        cout << "k:result = " << k << ":" << result.at(k) << "; ";
        if((k + 1) % 5 == 0) {
            cout << endl;
        }
    }
    cout << endl;
#endif
    return result;
}

vector<int> countPrimeNumber(vector<int>& src)
{
    vector<int> result;
    vector<int> tmpResult;
    vector<int> primeNumbers;
    // int count = 0;
    int startNumber = 0;
    int endNumber = 0;

    for(int i = 0;i < src.size();i++) {
        startNumber = src.at(i);
        endNumber = src.at(i) * 2;

        int p = 2;
        while(p * p < endNumber + 1) {
            p++;
        }
        // cout << "i = " << i << endl;

        tmpResult.clear();
        primeNumbers.clear();
        // count = 0;
        primeNumbers = findSquareNumber(p + 1);
        if(primeNumbers.size() == 0) {
            // cout << "[" << __FILE__ << ":" << __LINE__ << "] Not Found primenumbers" << endl;
            continue;
        }

        if(startNumber == 1 || startNumber == 2) {
            startNumber += 2;
            // count++;
            tmpResult.push_back(2);
        }
        else if(startNumber % 2 == 0) {
            int found = 0;
            for(int m = 2;m <= startNumber / 2;m++) {
                if(startNumber % m == 0) {
                    found = 1;
                    break;
                }
            }
            if(found == 0) {
                // count++;
                tmpResult.push_back(startNumber);
            }
            startNumber++;
        }

        for(int k = startNumber;k <= endNumber;k += 2) {
            // cout << "k:src = " << k << ":" << src.at(i) << '\n';
            if(k == src.at(i)) {
                continue;
            }
            int found = 0;
            for(int n = 0;n < primeNumbers.size();n++) {
                int tmp = primeNumbers.at(n);
                // cout << "[" << __FILE__ << ":" << __LINE__ << "] Stamp (k:n:tmp = " << k << ":" << n << ":" << tmp << ")" << endl;
                if(k % tmp == 0 && tmp != k) {
                    found = 1;
                    break;
                }
            }
            if(found == 0) {
                // cout << "[" << __FILE__ << ":" << __LINE__ << "] Stamp (k = " << k << ")" << endl;
                tmpResult.push_back(k);
                // count++;
            }
        }
    #if 0
        for(int q = 0;q < primeNumbers.size();q++) {
            cout << "(q = " << q << ") primeNumbers = " << primeNumbers.at(q) << endl;;
        }
    #endif
        result.push_back(tmpResult.size());
    #if 0
        cout << "start:end = " << src.at(i) << ":" << src.at(i) * 2 << '\n';
        for(int r = 0;r < tmpResult.size();r++) {
            cout << tmpResult.at(r) << " ";
        }
        cout << "(" << tmpResult.size() << ")" << '\n';
        // result.push_back(count);
    #endif
    }


    return result;
}

int main(void)
{
    enum {
        MIN = 0,
        MAX = 123456,
    };

    int input = -1;
    vector<int> result;
    vector<int> buf;

    while(input != 0) {
        cin >> input;
        if(input < MIN || input > MAX) {
            cout << "Invalid value input(" << input << ");" << endl;
            return -1;
        }

        if(input == 0) {
            continue;
        }
        buf.push_back(input);
    }

    result = countPrimeNumber(buf);

    for(int j = 0;j < result.size();j++) {
        cout << result.at(j) << '\n';
    }

    return 0;
}