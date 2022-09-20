#include <iostream>
#include <cstdlib>
#include <vector>
#include <climits>

using namespace std;

int main(void)
{
    enum {
        ALPHABET_SIZE = 'Z' - 'A',
    };
    int sum = 0;
    string buf;
    char comp = 'a';
    int found = 0;
    vector<int> result;

    cin >> buf;
    if(buf.empty() || buf.length() <= 0) {
        cout << "Invalid value buf(" << buf.c_str() << ");" << endl;
        return -1;
    }

    for(int j = 0;j <= ALPHABET_SIZE;j++) {
        found = -1;
        for(int i = 0;i < buf.length();i++) {
            if(comp == buf.at(i)) {
                found = i;
                break;
            }
        }
        result.push_back(found);
        // cout << "[" << j << "] " << (char)comp << endl;
        comp++;
    }

    for(int k = 0;k <= ALPHABET_SIZE;k++) {
        cout << result.at(k) << " ";
    }
    cout << endl;

	return 0;
}