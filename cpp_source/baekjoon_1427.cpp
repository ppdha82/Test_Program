#include <iostream>
#include <cstdlib>
#include <vector>
#include <climits>
#include <string>

using namespace std;

void swap(string& src, int s1, int s2, int line)
{
    int tmp = src.at(s1);
    src.at(s1) = src.at(s2);
    src.at(s2) = tmp;
#if defined(__DEBUG_ON__)
    cout << "[" << __FILE__ << ":" << line << "]";
    cout << "Swap s1:s2 = " << s1 << "(" << src.at(s1) << "):" << s2 << "(" << src.at(s2) << ")\n";
#endif  /* __DEBUG_ON__ */
}

void arrangeString(string& buf)
{
    for(int i = 0;i < buf.length() - 1;i++) {
#if defined(__DEBUG_ON__)
        cout << "[" << __FILE__ << ":" << __LINE__ << "] ";
        cout << "Stamp i = " << i << '\n';
#endif  /* __DEBUG_ON__ */
        for(int j = i + 1;j < buf.length();j++) {
#if defined(__DEBUG_ON__)
            cout << "[" << __FILE__ << ":" << __LINE__ << "] ";
            cout << "Stamp i:j = " << i << ":" << j << '\n';
#endif  /* __DEBUG_ON__ */
            if(buf.at(i) < buf.at(j)) {
                swap(buf, i, j, __LINE__);
            }
        }
    }
}

int main(void)
{
    enum {
        MIN = 0,
    };
    string buf;

#if !defined(__DEBUG_ON__)
    cin.tie(NULL);
    ios::sync_with_stdio(false);
#endif  /* __DEBUG_ON__ */

    cin >> buf;
    if(buf.empty() || buf.length() <= MIN) {
        cout << "Invalid value input(" << buf << ");" << endl;
        return -1;
    }

    arrangeString(buf);

    cout << buf << "\n";

    return 0;
}
