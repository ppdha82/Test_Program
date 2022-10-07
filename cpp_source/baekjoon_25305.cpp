#include <iostream>
#include <cstdlib>
#include <vector>
#include <climits>
#include <string>

using namespace std;

void fillSameNumber(int number, int* orig)
{
    int index = -1;

    orig[number]++;
#if defined(__DEBUG_ON__)
    cout << "[" << __FILE__ << ":" << __LINE__ << "] number:orig = " << number << ":" << orig[number] << "\n";
#endif  /* __DEBUG_ON__ */
}

int fillNumberToBuffer(vector<vector<int>>& buf, int* orig, int origSize)
{
    vector<int> manyPos;
    int manyValue = INT_MIN;
    for(int i = 0;i < origSize;i++) {
        if(orig[i] != 0) {
            vector<int> tmpBuf;
#if defined(__DEBUG_ON__)
            cout << "i:orig = " << i << ":" << orig[i] << "\n";
#endif  /* __DEBUG_ON__ */
            tmpBuf.push_back(i - 4000);
            tmpBuf.push_back(orig[i]);
#if defined(__DEBUG_ON__)
            cout << "[" << __FILE__ << ":" << __LINE__ << "] ";
            cout << "tmpBuf = " << tmpBuf.at(0) << ":" << tmpBuf.at(1) << "\n";
#endif  /* __DEBUG_ON__ */

            buf.push_back(tmpBuf);
            if(manyValue < orig[i]) {
                manyValue = orig[i];
                manyPos.clear();
                manyPos.push_back(i - 4000);
            }
            else if(manyValue == orig[i]) {
                manyPos.push_back(i - 4000);
            }
        }
    }

#if defined(__DEBUG_ON__)
    for(int m = 0;m < manyPos.size();m++) {
        cout << "[" << __FILE__ << ":" << __LINE__ << "] ";
        cout << "m:manyPos = " << m << ":" << manyPos.at(m) << "\n";
    }
#endif  /* __DEBUG_ON__ */

    int result = 0;
    if(manyPos.size() > 1) {
        result = manyPos.at(1);
    }
    else {
        result = manyPos.at(0);
    }
    return result;
}

int findCenterPos(vector<vector<int>>& buf, int size)
{
    int sum = 0;
    int result = -1;
    int centerPos = 0;

    if(size % 2 == 0) {
        centerPos = size / 2;
    }
    else {
        centerPos = size / 2 + 1;
    }
#if defined(__DEBUG_ON__)
    cout << "[" << __FILE__ << ":" << __LINE__ << "] ";
    cout << "centerPos = " << centerPos << "\n";
#endif  /* __DEBUG_ON__ */

    for(int i = 0;i < buf.size();i++) {
        sum += buf.at(i).at(1);
#if defined(__DEBUG_ON__)
        cout << "[" << __FILE__ << ":" << __LINE__ << "] ";
        cout << "sum:buf_i0:buf_i1 = " << sum << ":" << buf.at(i).at(0) << ":" << buf.at(i).at(1) << "\n";
#endif  /* __DEBUG_ON__ */
        if(sum >= centerPos) {
            result = buf.at(i).at(0);
            break;
        }
    }
    return result;
}

int main(void)
{
    enum {
        MIN = 1,
        MAX = 500000,
        N_MIN = -4000,
        N_MAX = 4000,
    };

    int input = -1;
    int* orig;
    int origSize = 0;
    vector<vector<int>> buf;
    int size = 0;
    int total = 0;
    int count = 0;
    int manyNumber = 0;

#if !defined(__DEBUG_ON__)
    cin.tie(NULL);
    ios::sync_with_stdio(false);
#endif  /* __DEBUG_ON__ */

    cin >> input;
    if(input < MIN || input > MAX) {
        cout << "Invalid value input(" << input << ");" << endl;
        return -1;
    }
    size = input;

    origSize = 2 * N_MAX + 1;
    orig = new int[origSize];
    for(int i = 0;i < size;i++) {
        cin >> input;
        if(input < N_MIN || input > N_MAX) {
            cout << "Invalid value input(" << input << ");" << endl;
            return -1;
        }
        fillSameNumber(input + 4000, orig);
        count++;
        total += input;
    }

    manyNumber = fillNumberToBuffer(buf, orig, origSize);
#if defined(__DEBUG_ON__)
    for(int j = 0;j < buf.size();j++) {
        cout << "[" << __FILE__ << ":" << __LINE__ << "] ";
        cout << "j:buf_k0:buf_k1 = " << j << ":" << buf.at(j).at(0) << ":" << buf.at(j).at(1) << "\n";
    }
#endif  /* __DEBUG_ON__ */
    double tmpCalcAvg = 0.0;
    double tmpTotal = 0.0;
    int calcAvg = 0;
    tmpCalcAvg = (double)total / count;
    tmpTotal = total / count;
    calcAvg = tmpCalcAvg;
#if defined(__DEBUG_ON__)
    cout << "tmpCalcAvg = " << tmpCalcAvg << "\n";
    cout << "tmpTotal = " << tmpTotal << "\n";
    cout << "calcAvg = " << calcAvg << "\n";
#endif  /* __DEBUG_ON__ */
    if(tmpCalcAvg < 0) {
#if defined(__DEBUG_ON__)
        cout << "tmpCalcAvg - tmpTotal = " << tmpCalcAvg << " - " << tmpTotal << "\n";
#endif  /* __DEBUG_ON__ */
        if((tmpCalcAvg - tmpTotal) < -0.5) {
            calcAvg--;
        }
    }
    else if((tmpCalcAvg - tmpTotal) > 0.5) {
        calcAvg++;
    }

    int centerPos = 0;

    centerPos = findCenterPos(buf, size);
    int range = buf.back().at(0) - buf.front().at(0);
#if defined(__DEBUG_ON__)
    cout << "calcAvg = " << calcAvg << "\n";
    cout << "centerAvg = " << centerPos << "\n";
    cout << "manyNumber = " << manyNumber << "\n";
    cout << "range = " << range << "\n";
#else
    cout << calcAvg << "\n";
    cout << centerPos << "\n";
    cout << manyNumber << "\n";
    cout << range << "\n";
#endif  /* __DEBUG_ON__ */

    delete []orig;

    return 0;
}
