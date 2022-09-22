#include <iostream>
#include <cstdlib>
#include <vector>
#include <climits>

using namespace std;

int filterCharacter(char c)
{
    enum {
        AtoC = 2,
        DtoF = 5,
        GtoI = 8,
        JtoL = 11,
        MtoO = 14,
        PtoS = 18,
        TtoV = 21,
        WtoZ = 25,
    };
    char sample = 'A';
    int result = 0;

    if(c >= sample && c <= sample + AtoC) {
        result = 2;
    }
    else if(c > sample + AtoC && c <= sample + DtoF) {
        result = 3;
    }
    else if(c > sample + DtoF && c <= sample + GtoI) {
        result = 4;
    }
    else if(c > sample + GtoI && c <= sample + JtoL) {
        result = 5;
    }
    else if(c > sample + JtoL && c <= sample + MtoO) {
        result = 6;
    }
    else if(c > sample + MtoO && c <= sample + PtoS) {
        result = 7;
    }
    else if(c > sample + PtoS && c <= sample + TtoV) {
        result = 8;
    }
    else if(c > sample + TtoV && c <= sample + WtoZ) {
        result = 9;
    }
    return result;
}

int convertInput(vector<int> &dst, string& src)
{
    int number = 0;
    int timelapse = 0;

    for(int i = 0;i < src.length();i++) {
        number = filterCharacter(src.at(i));
        dst.push_back(number);
    }

    for(int j = 0;j < dst.size();j++) {
        // cout << dst.at(j);
        timelapse += (dst.at(j) + 1);
    }
    // cout << endl;
    return timelapse;
}

int main(void)
{
    enum {
        MIN = 2,
        MAX = 15,
    };
    string input;
    vector<int> midResult;
    int count = 0;
    int timelapse = 0;

    cin >> input;
    if(input.empty() || input.length() < MIN || input.length() > MAX) {
        cout << "Invalid value input(" << input << ");" << endl;
        return -1;
    }

    // cout << input << endl;
    timelapse = convertInput(midResult, input);
    cout << timelapse << endl;

    return 0;
}
