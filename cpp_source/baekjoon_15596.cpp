#include <iostream>
#include <cstdlib>
#include <vector>
#include <climits>

using namespace std;

long long sum(std::vector<int> &a)
{
    long long total = 0;

    if(a.empty() || a.size() <= 0) {
        cout << "a is empty or has invalid size" << endl;
        return INT_MIN;
    }

    for(int i = 0;i < a.size();i++) {
        total += a.at(i);
    }

    return total;
}

int main(void)
{
    enum { COL_SIZE = 1 };
    enum {
        N_MIN = 0,
        N_MAX = 1000,
    };
    int a[COL_SIZE] = { INT_MAX };
    int size = 0;
    vector<int> value;
    int total = 0;

    cin >> a[0];
    if(a[0] < N_MIN || a[0] > N_MAX) {
        cout << "Invalid value a[0](" << a[0] << ");" << endl;
        return -1;
    }

    size = a[0];
    for(int i = 0;i < size;i++) {
        cin >> a[0];
        if(a[0] < N_MIN || a[0] > N_MAX) {
            cout << "Invalid value a[0](" << a[0] << ");" << endl;
            return -1;
        }
        value.push_back(a[0]);
    }

    total = sum(value);
    cout << total << endl;

	return 0;
}