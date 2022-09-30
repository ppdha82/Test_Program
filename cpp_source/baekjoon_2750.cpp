
#include <iostream>
#include <cstdlib>
#include <vector>
#include <climits>
#include <string>

using namespace std;

vector<int> sortNumber(vector<int>& src)
{
    vector<int> result;

    for(int i = 0;i < src.size() - 1;i++) {
        // cout << "[" << __FILE__ << ":" << __LINE__ << "] Stamp i = " << i << '\n';
        for(int j = i + 1;j < src.size();j++) {
            // cout << "[" << __FILE__ << ":" << __LINE__ << "] Stamp i:j = " << i << ":" << j << '\n';
            if(src.at(i) > src.at(j)) {
                int tmp = src.at(i);
                src.at(i) = src.at(j);
                src.at(j) = tmp;
            }
        }
    }
    result = src;

    return result;
}

int main(void)
{
    enum {
        MIN = 0,
        MAX = 1000,
        N_MIN = -1000,
        N_MAX = 1000,
    };

    int input = -1;
    vector<int> result;
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
    result = sortNumber(buf);

    for(int j = 0;j < result.size();j++) {
        cout << result.at(j) << ' ';
    }

    return 0;
}