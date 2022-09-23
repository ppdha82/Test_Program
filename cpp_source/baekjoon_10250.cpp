#include <iostream>
#include <cstdlib>
#include <vector>
#include <climits>

using namespace std;

vector<int> findRoomNumber(vector< vector<int> >& src)
{
    enum {
        HEIGHT,
        WIDTH,
        CUSTOMER,
    };
    vector<int> result;

    for(int i = 0;i < src.size();i++) {
        vector<int> tmp = src.at(i);
        int number = tmp.at(CUSTOMER) / tmp.at(HEIGHT);
        int floor = tmp.at(CUSTOMER) % tmp.at(HEIGHT) * 100;
        if(floor == 0) {
            floor = tmp.at(HEIGHT) * 100;
            number--;
        }
        number++;

        result.push_back(floor + number);
        // cout << "floor:number = " << floor << ":" << number << endl;
        // cout << "src(" << i << ") = " << tmp.at(HEIGHT) << ":" << tmp.at(WIDTH) << ":" << tmp.at(CUSTOMER) << endl;
    }

    return result;
}

int main(void)
{
    enum {
        SIZE = 3,
        T_MAX = 99 * 99,
        MIN = 1,
        MAX = 99,
    };

    int input = 0;
    int size = 0;
    vector<int> buf;
    vector< vector<int> > bufs;
    vector<int> result;

    cin >> input;
    if(input < MIN || input > T_MAX) {
        cout << "Invalid value input(" << input << ");" << endl;
        return -1;
    }

    size = input;
    for(int i = 0;i < size;i++) {
        buf.clear();
        for(int j = 0;j < SIZE;j++) {
            cin >> input;
            if(j == SIZE - 1) {
                if(input < MIN || input > T_MAX) {
                    cout << "Invalid value (i = " << i << "); input(" << input << ");" << endl;
                    // return -1;
                    return 0;
                }
            }
            else {
                if(input < MIN || input > MAX) {
                    cout << "Invalid value (i = " << i << "); input(" << input << ");" << endl;
                    // return -1;
                    return 0;
                }
            }
            buf.push_back(input);
        }
        if(buf.at(0) * buf.at(1) < buf.at(2)) {
            cout << "buf.at(0:1:2) = " << buf.at(0) << ":" << buf.at(1) << ":" << buf.at(2) << endl;
            return 0;
            // continue;
        }
        bufs.push_back(buf);
    }

    if(bufs.size() <= 0) {
        cout << "bufs is empty" << endl;
        // return -1;
        return 0;
    }
    result = findRoomNumber(bufs);
    for(int j = 0;j < result.size();j++) {
        cout << result.at(j) << " ";
    }
    cout << endl;

    return 0;
}
