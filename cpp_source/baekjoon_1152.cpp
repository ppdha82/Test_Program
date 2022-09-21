#include <iostream>
#include <cstdlib>
#include <vector>
#include <climits>

using namespace std;

int main(void)
{
    enum {
        MIN = 0,
        MAX = 1000000,
    };
    string buf;
    int count = 0;

    getline(cin, buf);
    if(buf.empty() || buf.length() < MIN || buf.length() > MAX) {
        cout << "Invalid value buf(" << buf.c_str() << ");" << endl;
        return -1;
    }

    // cout << buf.c_str() << endl;
    string::size_type n;
    n = buf.find(" ");
    // cout << "[" << __LINE__ << "] pos = " << n << endl;
    if(n != 0 && n != string::npos) {
        count++;
        // cout << "[" << __LINE__ << "] count = " << count << endl;
    }
    for(;n != string::npos;) {
        n = buf.find(" ", n + 1);
        if(n != string::npos) {
            // cout << "[" << __LINE__ << "] pos = " << n << endl;
            if(n != 0) {
                count++;
                // cout << "[" << __LINE__ << "] count = " << count << endl;
            }
        }
    }
    n = buf.rfind(" ");
    if(n == buf.size() - 1) {
        count--;
        // cout << "[" << __LINE__ << "] count = " << count << endl;
    }

    cout << count + 1 << endl;

    return 0;
}
