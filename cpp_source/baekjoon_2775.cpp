#include <iostream>
#include <cstdlib>
#include <vector>
#include <climits>

using namespace std;

vector<int> findRoomNumber(vector< vector<int> >& src)
{
    vector<int> origin;
    vector<int> result;
    vector<int> resultTmp;

    for(int i = 0;i < src.size();i++) {
        vector<int> tmp = src.at(i);
        int sum = 0;
        // cout << "tmp.at(" << i << ") = " << tmp.at(i) << endl;
        origin.clear();
        for(int k = 0;k < tmp.at(1);k++) {
            origin.push_back(k + 1);
        }
        int n = 0;
        do {
            resultTmp.clear();
            for(int j = 0;j < tmp.at(1);j++) {
                sum = 0;
                for(int m = 0;m <= j;m++) {
                    sum += origin.at(m);
                }
                resultTmp.push_back(sum);
            }
            n++;
            origin = resultTmp;
        } while(n < tmp.at(0));
        result.push_back(origin.back());
    }

    // for(int k = 0;k < result.size();k++) {
    //     cout << "(k = " << k << ") = " << result.at(k) << endl;
    // }

    return result;
}

int main(void)
{
    enum {
        SIZE = 2,
        MIN = 1,
        MAX = 14,
        N_MAX = 1000,
    };

    int input = 0;
    int size = 0;
    vector<int> buf;
    vector< vector<int> > bufs;
    vector<int> result;

    cin >> input;
    if(input < MIN || input > N_MAX) {
        cout << "Invalid value input(" << input << ");" << endl;
        return -1;
    }

    size = input;
    for(int i = 0;i < size;i++) {
        buf.clear();
        for(int j = 0;j < SIZE;j++) {
            cin >> input;
            if(input < MIN || input > MAX) {
                cout << "Invalid value (i = " << i << "); input(" << input << ");" << endl;
                return -1;
            }
            buf.push_back(input);
        }
        bufs.push_back(buf);
    }

    result = findRoomNumber(bufs);
    for(int j = 0;j < result.size();j++) {
        cout << result.at(j) << " ";
    }
    cout << endl;

    return 0;
}
