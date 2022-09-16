#include <iostream>
#include <cstdlib>
#include <vector>
#include <climits>

using namespace std;

int findMinNum(vector<int> *num)
{
    int min = INT_MAX;

    for(vector<int>::iterator iter_begin = num->begin();iter_begin != num->end();++iter_begin) {
        if(min > *iter_begin) {
            min = *iter_begin;
        }
    }

    return min;
}

int findMaxNum(vector<int> *num)
{
    int max = INT_MIN;

    for(vector<int>::iterator iter_begin = num->begin();iter_begin != num->end();++iter_begin) {
        if(max < *iter_begin) {
            max = *iter_begin;
        }
    }

    return max;
}

int main(void)
{
    enum { COL_SIZE = 1, };
    enum { C_MIN, C_MAX, COL_LIST, };
    const int MIN = 0;
    const int MAX = 1000000;
    int a[COL_SIZE] = { MAX };
    int size = 0;
    int num[COL_LIST] = { 0, };
    vector<int> buf;

    cin >> a[0];
    if(a[0] < MIN || a[0] > MAX) {
        cout << "Invalid value a[0](" << a[0] << ");" << endl;
        return -1;
    }

    size = a[0];
    for(int i = 0;i < size;i++) {
        cin >> a[0];
        buf.push_back(a[0]);
    }

    num[C_MIN] = findMinNum(&buf);
    num[C_MAX] = findMaxNum(&buf);

    cout << num[C_MIN] << " " << num[C_MAX] << endl;

	return 0;
}