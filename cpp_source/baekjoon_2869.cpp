#include <iostream>
#include <cstdlib>
#include <vector>
#include <climits>

using namespace std;

int calcClimbingTime(vector<int>& src)
{
    enum {
        CLIMB_UP,
        SLIDE_DOWN,
        HEIGHT,
    };
    int result = 0;
    int diff = (src.at(CLIMB_UP) - src.at(SLIDE_DOWN));
    int height = src.at(HEIGHT);
    int back = 0;

    result = height / diff;
    if(height % diff != 0) {
        result++;
    }

    back = src.at(CLIMB_UP)/diff;
    if(src.at(CLIMB_UP) % diff != 0) {
        back++;
    }
    // cout << "result:back = " << result << ":" << back << endl;

    int count = 0;

    for(int j = result - back;j < result;j++) {
        if(height - (diff * j + src.at(CLIMB_UP)) <= 0) {
            count++;
            // cout << "height:diff*j:src.at(CLIMB_UP) = " << height << ":" << diff * j << ":" << src.at(CLIMB_UP) << endl;
            break;
        }
        count++;
    }

    // cout << "result:count = " << result << ":" << count << endl;
    result = result - back + count;
    
    return result;
}

int main(void)
{
    enum {
        SIZE = 3,
        MIN = 1,
        MAX = 1000000000,
    };

    int input = 0;
    vector<int> buf;
    int result;

    for(int i = 0;i < SIZE;i++) {
        cin >> input;
        if(input < MIN || input > MAX) {
            cout << "Invalid value input(" << i << ")(" << input << ");" << endl;
            return -1;
        }
        buf.push_back(input);
    }

    result = calcClimbingTime(buf);
    cout << result << endl;

    return 0;
}
