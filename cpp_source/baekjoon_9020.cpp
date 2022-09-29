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
    for(int i = result.size() / 2;i < result.size() / 2 + 10;i++) {
        cout << "pos:result... " << i << ":" << result.at(i) << '\n';
    }

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

vector<vector<int>> findGoldbachNumber(vector<int>& src)
{
    vector<vector<int>> result;
    vector<int> tmpResult;
    vector<int> primeNumbers;
    int found = 0;

    primeNumbers = findSquareNumber(10000);
    for(int i = 0;i < src.size();i++) {
        int srcNumber = src.at(i);
        tmpResult.clear();
#if 0
        primeNumbers.clear();
        int p = 2;
        while(p * p < srcNumber) {
            p++;
        }
        primeNumbers = findSquareNumber(p + 1);
#endif
        if(primeNumbers.size() == 0) {
            // cout << "[" << __FILE__ << ":" << __LINE__ << "] Not Found primenumbers" << endl;
            continue;
        }

        int refencePos = 0;

        for(int i = 0;i < primeNumbers.size();i++) {
            if(primeNumbers.at(i) >= srcNumber / 2) {
                refencePos = i;
                break;
            }
        }

        for(int j = refencePos;j < primeNumbers.size();j++) {
            // cout << "j:prime.size = " << j << ":" << primeNumbers.size() << '\n';
            for(int k = refencePos;k >= 0;k--) {
                // cout << "i:j:k:src:prime-j:prime-k = " << i << ":" << j << ":" << k << ":" << src.at(i) << ":" << primeNumbers.at(j) << ":" << primeNumbers.at(k) << '\n';
                if(srcNumber == primeNumbers.at(j) + primeNumbers.at(k)) {
                    if(tmpResult.size() == 0) {
                        tmpResult.push_back(primeNumbers.at(k));
                        tmpResult.push_back(primeNumbers.at(j));
                    }
                    else {
                        int diff1 = primeNumbers.at(j) - primeNumbers.at(k);
                        int diff2 = tmpResult.at(0) - tmpResult.at(1);
                        if(diff1 < 0) {
                            diff1 *= -1;
                        }
                        if(diff2 < 0) {
                            diff2 *= -1;
                        }
                        if(diff1 < diff2) {
                            if(primeNumbers.at(j) > primeNumbers.at(k)) {
                                tmpResult.at(0) = primeNumbers.at(k);
                                tmpResult.at(1) = primeNumbers.at(j);
                            }
                            else {
                                tmpResult.at(0) = primeNumbers.at(j);
                                tmpResult.at(1) = primeNumbers.at(k);
                            }
                        }
                    }
                    break;
                }
                else if(srcNumber > primeNumbers.at(j) + primeNumbers.at(k)) {
                    break;
                }
            }
        }
        if(tmpResult.size() != 0) {
#if 0
            for(int m = 0;m < tmpResult.size();m++) {
                cout << "m:tmpResult = " << m << ":" << tmpResult.at(m) << '\n';
            }
#endif
            result.push_back(tmpResult);
        }
    }

    return result;
}

int main(void)
{
    enum {
        MIN = 0,
        MAX = 10000,
        N_MIN = 4,
        N_MAX = 10000,
    };

    int input = -1;
    vector<vector<int>> result;
    vector<int> buf;
    int size = 0;
    
    cin >> input;
    if(input < MIN || input > MAX) {
        cout << "Invalid value input(" << input << ");" << endl;
        return -1;
    }
    size = input;

    for(int i = 0;i < size;i++) {
        cin >> input;
        if(input < N_MIN || input > N_MAX) {
            cout << "Invalid value input(" << input << ");" << endl;
            return -1;
        }
        buf.push_back(input);
    }
    result = findGoldbachNumber(buf);

    for(int j = 0;j < result.size();j++) {
        for(int k = 0;k < result.at(j).size();k++) {
            cout << result.at(j).at(k) << ' ';
        }
        cout << '\n';
    }

    return 0;
}