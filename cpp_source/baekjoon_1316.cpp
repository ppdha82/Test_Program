#include <iostream>
#include <cstdlib>
#include <vector>
#include <climits>

using namespace std;

int countGroupWord(vector<string>& src)
{
    int groupCount = 0;
    int lastOrder = 0;
    int found = 0;
    vector<char> store;

    for(int i = 0;i < src.size();i++) {
        string tmp = src.at(i);
        // cout << "(" << i << ") tmp = " << tmp << endl;
        store.clear();
        if(tmp.length() <= 2) {
            groupCount++;
            continue;
        }
    
        for(lastOrder = 0;lastOrder < tmp.length() - 1;lastOrder++) {
            found = 0;
            for(int k = 0;k < store.size();k++) {
                if(store.at(k) == tmp.at(lastOrder)) {
                    found = 1;
                }
            }
            if(found == 1) {
                continue;
            }
            for(int j = lastOrder + 1;j < tmp.length();j++) {
                store.push_back(tmp.at(lastOrder));
                // cout << "[" << __LINE__ << "] tmp.at ==> lastOrder(" << lastOrder << ") = " << tmp.at(lastOrder) << "; j(" << j << ") = " << tmp.at(j) << ";" << endl;
                if(tmp.at(lastOrder) == tmp.at(j)) {
                    if(j - lastOrder == 1) {
                        // cout << "[" << __LINE__ << "] tmp.at ==> lastOrder(" << lastOrder << ") = " << tmp.at(lastOrder) << "; j(" << j << ") = " << tmp.at(j) << ";" << endl;
                        lastOrder = j;
                    }
                    else {
                        // cout << "[" << __LINE__ << "] tmp.at ==> lastOrder(" << lastOrder << ") = " << tmp.at(lastOrder) << "; j(" << j << ") = " << tmp.at(j) << ";" << endl;
                        lastOrder = -1;
                        break;
                    }
                }
            }
            if(lastOrder < 0 ) {
                break;
            }
        }

        if(lastOrder > 0) {
            groupCount++;
            // cout << "[" << __LINE__ << "] " << groupCount << endl;
        }
    }

    // cout << endl;
    return groupCount;
}

int main(void)
{
    enum {
        MIN = 0,
        MAX = 100,
    };
    int size = 0;
    string buf;
    vector<string> bufs;
    int count = 0;

    cin >> size;
    if(size < MIN || size > MAX) {
        cout << "Invalid value size(" << size << ");" << endl;
        return -1;
    }

    for(int i = 0;i < size;i++) {
        cin >> buf;
        if(buf.empty() || buf.length() < MIN || buf.length() > MAX) {
            cout << "Invalid value input(" << buf << ");" << endl;
            return -1;
        }
        bufs.push_back(buf);
    }

    // cout << input << endl;
    count = countGroupWord(bufs);
    cout << count << endl;

    return 0;
}
