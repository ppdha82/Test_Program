#include <iostream>
#include <cstdlib>
#include <vector>
#include <climits>

using namespace std;

int main(void)
{
    enum { COL_SIZE = 1 };
    const int MIN = 0;
    const int MAX = 1000;
    int a[COL_SIZE] = { INT_MAX };
    int size = 0;
    int count = 0;
    int weight = 1;
    int total = 0;
    string strBuf;
    vector<int> arrTotal;

    cin >> a[0];
    if(a[0] < MIN || a[0] > MAX) {
        cout << "Invalid value a[0](" << a[0] << ");" << endl;
        return -1;
    }

    size = a[0];
    for(int i = 0;i < size;i++) {
        cin >> strBuf;
        total = 0;
        weight = 1;
        if(strBuf.empty() || strBuf.length() <= 0) {
            cout << "Invalid value strBuf(" << strBuf.c_str() << ");" << endl;
            return -1;
        }
        for(int j = 0;j < strBuf.size();j++) {
            if(strBuf.c_str()[j] == 'O') {
                total += weight;
                // cout << "[" << j << "] total = " << total << "; weigth = " << weight << ";" << endl;
                weight++;
            }
            else {
                weight = 1;
            }
        }
        arrTotal.push_back(total);
    }

    for(int j = 0;j < size;j++) {
        cout << arrTotal.at(j) << endl;
    }

	return 0;
}