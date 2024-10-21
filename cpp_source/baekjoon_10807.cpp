#include <iostream>
#include <cstdlib>
#include <climits>
#include <ctime>
#include <vector>

using namespace std;

int main(void)
{
    const int MIN = -100;
    const int MAX = 100;

    int size = 0;
    int value = 0;
    vector<unsigned int> input;
    int count = 0;
    int target = 0;

    cin.tie(NULL);
    ios::sync_with_stdio(false);

    cin >> size;

    for(int i = 0;i < size;i++) {
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

    do {
        cin >> value;
        if (value < MIN || value > MAX) {
            cout << "Invalid value value[" << value << "]\n";
            continue;
        }
        target = value;
    } while(0);

    for (int j = 0;j < size;j++) {
        if (input.at(j) == target) {
            count++;
        }
    }
    cout << count << "\n";

    return 0;
}