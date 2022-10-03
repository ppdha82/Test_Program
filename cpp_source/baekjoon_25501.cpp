#include <iostream>
#include <cstdlib>
#include <vector>
#include <climits>
#include <string>

using namespace std;

int recursion(string s, int l, int r, int &count)
{
    int result = 0;
    for(int k = 0;k < s.length();k++) {
        count++;
        if(l + k >= r - k) {
            result = 1;
            break;
        }
        else if(s.at(l + k) != s.at(r - k)) {
            result = 0;
            break;
        }
    }
    return result;
}

vector<vector<int>> isPalindrome(vector<string>& src)
{
    vector<int> palindromeResult;
    vector<vector<int>> result;
    int count = 0;
    int ret = 0;

    for(int i = 0;i < src.size();i++) {
        count = 0;
        palindromeResult.clear();
        ret = recursion(src.at(i), 0, src.at(i).length() - 1, count);
        palindromeResult.push_back(ret);
        palindromeResult.push_back(count);
        result.push_back(palindromeResult);
    }
    return result;
}

int main(void)
{
    enum {
        MIN = 0,
        MAX = 1000,
    };

    int input = -1;
    vector<string> buf;
    int size = 0;
    string strInput;
    vector<vector<int>> result;

    cin.tie(NULL);
    ios::sync_with_stdio(false);
   
    cin >> input;
    if(input < MIN || input > MAX) {
        cout << "Invalid value input(" << input << ");" << endl;
        return -1;
    }
    size = input;

    for(int i = 0;i < size;i++) {
        cin >> strInput;
        if(input < MIN || input > MAX) {
            cout << "Invalid value input(" << strInput << ");" << endl;
            return -1;
        }
        buf.push_back(strInput);
    }
    result = isPalindrome(buf);

    for(int j = 0;j < result.size();j++) {
        // cout.width(10);
        // cout << buf.at(j) << ": " << result.at(j).at(0) << ' ' << result.at(j).at(1) << '\n';
        cout << result.at(j).at(0) << ' ' << result.at(j).at(1) << '\n';
    }

    return 0;
}