#include <iostream>
#include <cstdlib>
#include <vector>
#include <climits>

using namespace std;

int main(void)
{
    enum {
        COL_SIZE = 1,
        N_MIN = 0,
        N_MAX = 1000,
        M_MIN = 0,
        M_MAX = 8,
    };
    int a[COL_SIZE] = { INT_MAX };
    int size = 0;
    int subSize = 0;
    string buf;
    string result;
    vector<string> results;

    cin >> a[0];
    if(a[0] < N_MIN || a[0] > N_MAX) {
        cout << "Invalid value a[0](" << a[0] << ");" << endl;
        return -1;
    }

    size = a[0];
    for(int i = 0;i < size;i++) {
        cin >> a[0];
        if(a[0] < M_MIN || a[0] > M_MAX) {
            cout << "Invalid value a[0](" << a[0] << ");" << endl;
            return -1;
        }

        subSize = a[0];
        result.clear();
        cin >> buf;
        if(buf.empty() || buf.length() <= 0) {
            cout << "Invalid empty or value buf(" << buf.c_str() << ");" << endl;
            return -1;
        }
        for(int j = 0;j < buf.length();j++) {
            for(int k = 0;k < subSize;k++) {
                result.push_back(buf.at(j));    
            }
        }
        results.push_back(result);
    }

    for(int m = 0;m < results.size();m++) {
        cout << results.at(m) << endl;
    }

	return 0;
}