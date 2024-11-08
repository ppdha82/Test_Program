#include <iostream>
#include <cstdlib>
#include <climits>
#include <ctime>
#include <vector>

using namespace std;

int main(void)
{
    const int MIN = 1;
    const int MAX = 30;

    const int SIZE = 28;

    int value = 0;
    vector<int> reference;
    vector<int> input;
    int count = 0;
    int target = 0;

    cin.tie(NULL);
    ios::sync_with_stdio(false);

    for(int k = 1;k <= MAX;k) {
        reference.push_back(k);
    }

    for(int i = 0;i < SIZE;i++) {
        cin >> value;
        if (value < MIN || value > MAX) {
            if (i > 0) {
                cout << "Invalid value value[" << i << "](" << input.at(i) << ")\n";
            }
            i--;
            continue;
        }
        input.push_back(value);
    }

    for (int j = 0;j < SIZE;j++) {
        if (input.at(j) == target) {
            count++;
        }
    }
    cout << count << "\n";

    return 0;
}