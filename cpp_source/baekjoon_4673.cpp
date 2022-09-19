#include <iostream>
#include <cstdlib>
#include <vector>
#include <climits>

using namespace std;

vector<int> findSelfNumbers(vector<int> &src)
{
    vector<int> dummy;
    if(src.empty() || src.size() <= 0) {
        cout << "src is empty or has invalid size" << endl;
        return dummy;
    }

    enum {
        DIVIDE_NUM = 10,
    };
    int selfSum = 0;
    int divider = DIVIDE_NUM;
    for(int i = 0;i < src.size();i++) {
        selfSum = i + i % DIVIDE_NUM;
        divider = DIVIDE_NUM;
        while(i / divider != 0) {
            selfSum += (i / divider) % DIVIDE_NUM;
            // cout << "[" << i << "] " << selfSum << "; " << divider << "; " << endl;
            divider *= DIVIDE_NUM;
        }
        // cout << "[" << i << "] " << selfSum << "; " << divider << "; " << endl;
        if(selfSum < src.size()) {
            src.at(selfSum) = -1;
        }
    }

    return src;
}

int main(void)
{
    enum {
        MIN = 0,
        MAX = 10000,
    };

    vector<int> buf;

    for(int i = 0;i < MAX;i++) {
        buf.push_back(i);
    }
    buf = findSelfNumbers(buf);

    for(int j = 0;j < buf.size();j++) {
        if(buf.at(j) <= 0) {
            continue;
        }
        cout << buf.at(j) << endl;
    }
	return 0;
}