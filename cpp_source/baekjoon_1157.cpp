#include <iostream>
#include <cstdlib>
#include <vector>
#include <climits>

using namespace std;

int main(void)
{
    enum {
        ALPHABET_RANGE = 'Z' - 'A',
        CASE_OFFSET = 'a' - 'A',
        MIN = 0,
        MAX = 1000000,
    };
    string buf;
    char comp = 'a';
    int count = 0;
    int sameCount = 0;
    vector<int> result;
    vector<char> index;

    cin >> buf;
    if(buf.empty() || buf.length() < MIN || buf.length() > MAX) {
        cout << "Invalid value buf(" << buf.c_str() << ");" << endl;
        return -1;
    }

    for(int j = 0;j <= ALPHABET_RANGE;j++) {
        count = 0;
        // cout << "comp = " << (char)comp << "; COMP = " << (char)(comp - CASE_OFFSET) << ";" << endl;
        for(int i = 0;i < buf.length();i++) {
            if(comp == buf.at(i) || (comp - CASE_OFFSET) == buf.at(i)) {
                count++;
                // cout << "[i = " << i << "] comp = " << (char)comp << "; COMP = " << (char)(comp - CASE_OFFSET) << "; buf.at(" << i << ") = " << buf.at(i) << "; count = " << count << ")" << endl;
            }
        }

        if(count > 0) {
            result.push_back(count);
            index.push_back(comp - CASE_OFFSET);
            // cout << "[j = " << j << "] " << (char)(j + 'A') << "; count = " << count << endl;
        }
        comp++;
    }

    int maxIndex = 0;
    int maxCount = -1;
    for(int k = 0;k < index.size();k++) {
        // cout << "[k = " << k << "]; result.at(" << k << ") = " << result.at(k) << ";" << endl;
        if(result.at(k) != 0) {
            // cout << "result.at(" << (char)(index.at(k)) << ") = " << result.at(k) << endl;
        }

        if(maxCount < result.at(k)) {
            maxCount = result.at(k);
            maxIndex = index.at(k);
            sameCount = 0;
        }
        else if(maxCount == result.at(k)) {
            if(maxCount == -1) {
                continue;
            }
            else {
                sameCount = 1;
            }
        }
    }
   
    if(sameCount == 0) {
        cout << (char)(maxIndex) << endl;
    }
    else {
        cout << "?" << endl;
    }

    return 0;
}
