#include <iostream>
#include <cstdlib>
#include <vector>
#include <climits>
#include <string>

using namespace std;

int findPrimeNumber(vector<int>& src)
{
    int result = 0;
    int count = 0;

    for(int i = 0;i < src.size();i++) {
        count = 0;
        int tmp = src.at(i);
        for(int j = 1;j <= src.at(i);j++) {
            if(tmp % j == 0) {
                count++;
            }
        }
        if(count == 2) {
            result++;
        }
    }
    return result;
}

int main(void)
{
    enum {
        MIN = 0,
        MAX = 100,
        N_MAX = 1000,
    };
    int input = 0;
    int size = 0;;
    int result;
    vector<int> buf;

    cin >> input;
    if(input < MIN || input > MAX) {
        cout << "Invalid value input(" << input << ");" << endl;
        return -1;
    }
    size = input;

    for(int i = 0;i < size;i++) {
        cin >> input;
        if(input < MIN || input > N_MAX) {
            cout << "Invalid value (i = " << i << ") input(" << input << ");" << endl;
            return -1;
        }
        buf.push_back(input);
    }
    result = findPrimeNumber(buf);
    cout << result << endl;
    return 0;
}
