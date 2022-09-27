#include <iostream>
#include <cstdlib>
#include <vector>
#include <climits>
#include <string>

using namespace std;

vector<int> calcFactorization(int src)
{
    vector<int> result;
    int tmp = src;

    if(src == 1) {
        return result;
    }

    for(int i = 2;i <= src / 2;i++) {
        while(1) {
            if(tmp % i == 0 && tmp != 0) {
                tmp /= i;
                result.push_back(i);
                // cout << "tmp:i = " << tmp << ":" << i << endl;
            }
            else {
                break;
            }
        }
    }
    if(result.size() == 0) {
        result.push_back(src);
    }

    return result;
}

int main(void)
{
    enum {
        MIN = 1,
        MAX = 10000000,
    };
    int input = 0;
    vector<int> result;

    
    cin >> input;
    if(input < MIN || input > MAX) {
        cout << "Invalid value input(" << input << ");" << endl;
        return 0;
    }

    result = calcFactorization(input);
    for(int j = 0;j < result.size();j++) {
        cout << result.at(j) << endl;
    }

    return 0;
}
