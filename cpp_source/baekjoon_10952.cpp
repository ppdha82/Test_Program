#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

int main(void)
{
    enum { COL_SIZE = 2, };
    const int MIN = 0;
    const int MAX = 10000;
    vector< vector<int> > vBuf;
    vector<int> vCol;

    int a[COL_SIZE] = { MAX, MAX };

    do {
        cin >> a[0] >> a[1];
        if(a[0] < MIN || a[0] > MAX || a[1] < MIN || a[1] > MAX) {
            cout << "Invalid value a[0](" << a[0] << "); a[1](" << a[1] << ");" << endl;
            return -1;
        }

        if(a[0] != 0 && a[1] != 0) {
            vCol.push_back(a[0]);
            vCol.push_back(a[1]);
            vBuf.push_back(vCol);
            vCol.clear();
        }
    } while(a[0] != 0 && a[1] != 0);

    for(int k = 0;k < vBuf.size();k++) {
        cout << vBuf.at(k).at(0) + vBuf.at(k).at(1) << endl;
    }

	return 0;
}