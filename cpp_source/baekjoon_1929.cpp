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

vector<int> findPrimeNumber(vector<int>& src)
{
    vector<int> result;
    int count = 0;
    int minValue = INT_MAX;
    int startNumber = src.at(0);
    int endNumber = src.at(1);

#if 1
    vector<int> primeNumbers;
    int i = 2;
    while(i * i < endNumber) {
        i++;
    }
    // cout << "i = " << i << endl;

    primeNumbers = findSquareNumber(i + 1);
    if(primeNumbers.size() == 0) {
        // cout << "[" << __FILE__ << ":" << __LINE__ << "] Not Found primenumbers" << endl;
        return result;
    }

    if(startNumber % 2 == 0) {
        int found = 0;
        for(int m = 2;m <= startNumber / 2;m++) {
            if(startNumber % m == 0) {
                found = 1;
                break;
            }
        }
        if(found == 0) {
            result.push_back(startNumber);
        }
        startNumber++;
    }
    else if(startNumber == 1) {
        startNumber += 2;
        result.push_back(2);
    }

    for(int k = startNumber;k <= endNumber;k += 2) {
        if(k == 1) {
            result.push_back(-1);
        }
        else {
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
                result.push_back(k);
            }
        }
    }
#if 0
    for(int q = 0;q < primeNumbers.size();q++) {
        cout << "(q = " << q << ") primeNumbers = " << primeNumbers.at(q) << endl;;
    }
#endif

#else
    for(int i = startNumber;i <= endNumber;i++) {
        if(i == 1) {
            continue;
        }
        count = 0;

        for(int j = 2;j <= i / 2;j++) {
            if(i % j == 0) {
                count++;
                break;
            }
            // cout << "i:j:count = " << i << ":" << j << ":" << count << endl;
        }

        if(count == 0) {
            result.push_back(i);
            // cout << "i:sum:minValue = " << i << ":" << sum << ":" << minValue << endl;
        }
    }
#endif
    return result;
}

int main(void)
{
    enum {
        SIZE = 2,
        MIN = 1,
        MAX = 1000000,
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
        if(result.at(j) < 0) {
            continue;
        }
        cout << result.at(j) << '\n';
    }

    return 0;
}