#include <iostream>
#include <cstdlib>
#include <vector>
#include <climits>

using namespace std;

int countCroatiaAlphabet(string& src)
{
    vector<string> croatiaAlphabets;
    string croatiaAlphabet;
    int count = 0;
    int filterCount = 0;
    croatiaAlphabet = "c=";
    croatiaAlphabets.push_back(croatiaAlphabet);
    croatiaAlphabet = "c-";
    croatiaAlphabets.push_back(croatiaAlphabet);
    croatiaAlphabet = "dz=";
    croatiaAlphabets.push_back(croatiaAlphabet);
    croatiaAlphabet = "d-";
    croatiaAlphabets.push_back(croatiaAlphabet);
    croatiaAlphabet = "lj";
    croatiaAlphabets.push_back(croatiaAlphabet);
    croatiaAlphabet = "nj";
    croatiaAlphabets.push_back(croatiaAlphabet);
    croatiaAlphabet = "s=";
    croatiaAlphabets.push_back(croatiaAlphabet);
    croatiaAlphabet = "z=";
    croatiaAlphabets.push_back(croatiaAlphabet);

    for(int i = 0;i < src.length();i++) {
        // cout << "i = " << i << ";" << endl;
        for(int j = 0;j < croatiaAlphabets.size();j++) {
            string tmp = croatiaAlphabets.at(j);
            // cout << "j = " << j << "; tmp = " << tmp << ";" << endl;
            if(i + tmp.length() > src.length()) {
                // cout << "continue; " << i + tmp.length() << "; " << src.length() << endl;
                continue;
            }
            count = 0;
            for(int k = 0;k < tmp.length();k++) {
                if(src.at(i + k) == tmp.at(k)) {
                    count++;
                }
                else {
                    break;
                }
            }
            if(count == tmp.length()) {
                i += tmp.length() - 1;
                // cout << tmp << "; i = " << i << endl;
                break;
            }
        }
        filterCount++;
    }

    // cout << endl;
    return filterCount;
}

int main(void)
{
    enum {
        MIN = 0,
        MAX = 100,
    };
    string input;
    int count = 0;

    cin >> input;
    if(input.empty() || input.length() < MIN || input.length() > MAX) {
        cout << "Invalid value input(" << input << ");" << endl;
        return -1;
    }

    // cout << input << endl;
    count = countCroatiaAlphabet(input);
    cout << count << endl;

    return 0;
}
