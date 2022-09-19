#include <iostream>
#include <cstdlib>
#include <vector>
#include <climits>

using namespace std;

int main(void)
{
    enum { COL_SIZE = 1 };
    enum {
        N_MIN = 0,
        N_MAX = 1000,
        G_MIN = 0,
        G_MAX = 100,
    };
    int a[COL_SIZE] = { INT_MAX };
    int size = 0;
    int subSize = 0;
    int total = 0;
    int count = 0;
    double average = 0.0;
    vector<int> score;
    vector< vector<int> > scores;

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

        subSize = a[0];
        total = 0;
        score.clear();
        for(int j = 0;j < subSize;j++) {
            cin >> a[0];
            total += a[0];
            score.push_back(a[0]);
        }
        scores.push_back(score);
    }

    cout << fixed;
    cout.precision(3);

    for(int m = 0;m < size;m++) {
        total = 0;
        count = 0;
        subSize = scores.at(m).size();
        for(int k = 0;k < subSize;k++) {
            // cout << scores.at(m).at(k) << " ";
            total += scores.at(m).at(k);
        }
        // cout << endl;
        average = total / subSize;
        // cout << "[" << m << "] " << average << endl;
        for(int k = 0;k < subSize;k++) {
            if(average < scores.at(m).at(k)) {
                count++;
            }
        }
        cout << (double)count / subSize * 100.0 << "%" << endl;
    }

	return 0;
}