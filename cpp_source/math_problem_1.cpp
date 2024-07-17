#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <climits>
#include <string>

using namespace std;

class CTest
{
public:
    enum {
        MAX_NUM = 9,
        // MAX_NUM = 10,
    };

    CTest()
    {
        tryCount = 0;
        validCount = 0;
        condition_1 = 0;
        condition_2 = 0;
        condition_3 = 0;
        condition_4 = 0;
        condition_5 = 0;
        condition_6 = 0;
        condition_7 = 0;
    }

    void runReal()
    {
        for (int i = 1;i <= CTest::MAX_NUM;i++) {
            inputData.push_back(i);
            runLoop(inputData);
            // cout << "[" << __FILE__ << ":" << __LINE__ << "] input.pop_back[" << inputData.back() << "]\n";
            inputData.pop_back();
        }
        cout << "[" << __FILE__ << ":" << __LINE__ << "] validCount / tryCount[" << validCount << "/" << tryCount << "]\n";
        cout << "[" << __FILE__ << ":" << __LINE__ << "] condition_1 / condition_2[" << condition_1 << "/" << condition_2 << "]\n";
        cout << "[" << __FILE__ << ":" << __LINE__ << "] condition_3 / condition_4[" << condition_3 << "/" << condition_4 << "]\n";
        cout << "[" << __FILE__ << ":" << __LINE__ << "] condition_5 / condition_6[" << condition_5 << "/" << condition_6 << "]\n";
        cout << "[" << __FILE__ << ":" << __LINE__ << "] condition_7[" << condition_7 << "]\n";
    }

private:
    void runLoop(vector<int> &input)
    {
        // cout << "[" << __FILE__ << ":" << __LINE__ << "] input.back()[" << input.back() << "]\n";
        bool found;
        for (int i = 1;i <= CTest::MAX_NUM;i++) {
            found = false;
            for (vector<int>::iterator it = input.begin();it != input.end();it++) {
                if (i == *it) {
                    found = true;
                    break;
                }
            }
            if (found == true) {
                // cout << "[" << __FILE__ << ":" << __LINE__ << "] skip push_back[" << i << "]\n";
                continue;
            }
            input.push_back(i);

            if (input.size() < CTest::MAX_NUM) {
                runLoop(input);
            }

            if (input.size() == CTest::MAX_NUM) {
                if (checkAll(input) == false) {
                    // cout << "[" << __FILE__ << ":" << __LINE__ << "] skip\n";
                }
                else {
                    validCount++;
                    showCurrentState(input);
                }
                tryCount++;
            }

            if (input.size() >= 2) {
                // cout << "[" << __FILE__ << ":" << __LINE__ << "] input.pop_back[" << input.back() << "]\n";
                input.pop_back();
            }
        }
    }

    bool checkCondition_1(vector<int> &input)
    {
        for (int i = 0; i < input.size() - 1;i++) {
            int diff = input.at(i) - input.at(i + 1);
            if (diff == -1 || diff == 1) {
                condition_1++;
                return false;
            }
        }
        return true;
    }

    bool checkCondition_2(vector<int> &input)
    {
        for (int i = 0; i < input.size() - 1;i++) {
            int diff = input.at(i) - input.at(i + 1);
            if (diff == -4 || diff == 4) {
                condition_2++;
                return false;
            }
        }
        return true;
    }

    bool checkCondition_3(vector<int> &input)
    {
        enum {
            VALID_POS_SIZE = 2,
            INVALID_POSITION_VALUE = 2,
            FOUND_NUM_1 = 5,
            FOUND_NUM_2 = 6,
        };
        vector<int> pos;
        int diff = 0;

        for (int i = 0;i < input.size();i++) {
            if (input.at(i) == FOUND_NUM_1 || input.at(i) == FOUND_NUM_2) {
                pos.push_back(i);
                if (pos.size() >= VALID_POS_SIZE) {
                    break;
                }
            }
        }
        if (pos.size() != VALID_POS_SIZE) {
            cout << "[" << __FILE__ << ":" << __LINE__ << "] invalid pos.size[" << pos.size() << "]\n";
            condition_3++;
            return false;
        }
        diff = pos.at(0) - pos.at(1);
        if (!(diff == -INVALID_POSITION_VALUE || diff == INVALID_POSITION_VALUE)) {
            condition_3++;
            return false;
        }
        return true;
    }

    bool checkCondition_4(vector<int> &input)
    {
        enum {
            VALID_POS_SIZE = 2,
            INVALID_POSITION_VALUE = 5,
            FOUND_NUM_1 = 4,
            FOUND_NUM_2 = 5,
        };
        vector<int> pos;
        int diff = 0;

        for (int i = 0;i < input.size();i++) {
            if (input.at(i) == FOUND_NUM_1 || input.at(i) == FOUND_NUM_2) {
                pos.push_back(i);
                if (pos.size() >= VALID_POS_SIZE) {
                    break;
                }
            }
        }
        if (pos.size() != VALID_POS_SIZE) {
            cout << "[" << __FILE__ << ":" << __LINE__ << "] invalid pos.size[" << pos.size() << "]\n";
            condition_4++;
            return false;
        }
        diff = pos.at(0) - pos.at(1);
        if (!(diff == -INVALID_POSITION_VALUE || diff == INVALID_POSITION_VALUE)) {
            condition_4++;
            return false;
        }
        return true;
    }

    bool checkCondition_5(vector<int> &input)
    {
        enum {
            VALID_POS_SIZE = 2,
            INVALID_POSITION_VALUE = 5,
            FOUND_NUM_1 = 2,
            FOUND_NUM_2 = 4,
            INVALID_NUMBER = 99,
            PASS_NUMBER = 9,
        };
        vector<int> pos;
        int diff = 0;
        int startNumber = INVALID_NUMBER;
        int endNumber = INVALID_NUMBER;
        int sum = 0;

        for (int i = 0;i < input.size();i++) {
            if (input.at(i) == FOUND_NUM_1 || input.at(i) == FOUND_NUM_2) {
                pos.push_back(i);
                if (pos.size() >= VALID_POS_SIZE) {
                    break;
                }
            }
        }
        if (pos.size() != VALID_POS_SIZE) {
            cout << "[" << __FILE__ << ":" << __LINE__ << "] invalid pos.size[" << pos.size() << "]\n";
            condition_5++;
            return false;
        }

        if (pos.at(0) == pos.at(1)) {
            cout << "[" << __FILE__ << ":" << __LINE__ << "] same pos value pos.at(0) / pos.at(1)[" << pos.at(0) << "/" << pos.at(1) << "]\n";
            condition_5++;
            return false;
        }
        else if (diff == -1 || diff == 1) {
            cout << "[" << __FILE__ << ":" << __LINE__ << "] there is no number between position value pos.at(0) / pos.at(1)[" << pos.at(0) << "/" << pos.at(1) << "]\n";
            condition_5++;
            return false;
        }
        else if (pos.at(0) < pos.at(1)) {
            startNumber = pos.at(0);
            endNumber = pos.at(1);
        }
        else {
            startNumber = pos.at(0);
            endNumber = pos.at(1);
        }
        for (int j = startNumber + 1;j < endNumber;j++) {
            sum += input.at(j);
        }
        if (sum != PASS_NUMBER) {
            condition_5++;
            return false;
        }
        return true;
    }

    bool checkCondition_6(vector<int> &input)
    {
        enum {
            VALID_POS_SIZE = 2,
            FOUND_NUM_1 = 5,
            FOUND_NUM_2 = 6,
        };
        map<int, int> pos;

        for (int i = 0;i < input.size();i++) {
            if (input.at(i) == FOUND_NUM_1 || input.at(i) == FOUND_NUM_2) {
                if (input.at(i) == FOUND_NUM_1) {
                    pos[FOUND_NUM_1] = i;
                }
                if (input.at(i) == FOUND_NUM_2) {
                    pos[FOUND_NUM_2] = i;
                }
                if (pos.size() >= VALID_POS_SIZE) {
                    break;
                }
            }
        }
        if (pos.size() != VALID_POS_SIZE) {
            cout << "[" << __FILE__ << ":" << __LINE__ << "] invalid pos.size[" << pos.size() << "]\n";
            condition_6++;
            return false;
        }

        if (pos.at(FOUND_NUM_1) == pos.at(FOUND_NUM_2)) {
            cout << "[" << __FILE__ << ":" << __LINE__ << "] same pos value pos.at(FOUND_NUM_1) / pos.at(FOUND_NUM_2)[" << pos.at(FOUND_NUM_1) << "/" << pos.at(FOUND_NUM_2) << "]\n";
            condition_6++;
            return false;
        }
        else if (pos.at(FOUND_NUM_1) < pos.at(FOUND_NUM_2)) {
            condition_6++;
            return false;
        }
        return true;
    }

    bool checkCondition_7(vector<int> &input)
    {
        enum {
            VALID_POS_SIZE = 3,
            FOUND_NUM_1 = 4,
            FOUND_NUM_2 = 6,
            FOUND_NUM_3 = 7,
            INVALID_NUMBER = 99,
        };
        map<int, int> pos;
        int startNumber = INVALID_NUMBER;
        int endNumber = INVALID_NUMBER;

        for (int i = 0;i < input.size();i++) {
            if (input.at(i) == FOUND_NUM_1 || input.at(i) == FOUND_NUM_2 || input.at(i) == FOUND_NUM_3) {
                if (input.at(i) == FOUND_NUM_1) {
                    pos[FOUND_NUM_1] = i;
                }
                if (input.at(i) == FOUND_NUM_2) {
                    pos[FOUND_NUM_2] = i;
                }
                if (input.at(i) == FOUND_NUM_3) {
                    pos[FOUND_NUM_3] = i;
                }
                if (pos.size() >= VALID_POS_SIZE) {
                    break;
                }
            }
        }
        if (pos.size() != VALID_POS_SIZE) {
            cout << "[" << __FILE__ << ":" << __LINE__ << "] invalid pos.size[" << pos.size() << "]\n";
            condition_7++;
            return false;
        }

        if (pos.at(FOUND_NUM_1) == pos.at(FOUND_NUM_2)) {
            cout << "[" << __FILE__ << ":" << __LINE__ << "] same pos value pos.at(FOUND_NUM_1) / pos.at(FOUND_NUM_2)[" << pos.at(FOUND_NUM_1) << "/" << pos.at(FOUND_NUM_2) << "]\n";
            condition_7++;
            return false;
        }
        else if (pos.at(FOUND_NUM_1) == pos.at(FOUND_NUM_3)) {
            cout << "[" << __FILE__ << ":" << __LINE__ << "] same pos value pos.at(FOUND_NUM_1) / pos.at(FOUND_NUM_3)[" << pos.at(FOUND_NUM_1) << "/" << pos.at(FOUND_NUM_3) << "]\n";
            condition_7++;
            return false;
        }
        else if (pos.at(FOUND_NUM_2) == pos.at(FOUND_NUM_3)) {
            cout << "[" << __FILE__ << ":" << __LINE__ << "] same pos value pos.at(FOUND_NUM_2) / pos.at(FOUND_NUM_3)[" << pos.at(FOUND_NUM_2) << "/" << pos.at(FOUND_NUM_3) << "]\n";
            condition_7++;
            return false;
        }

        if (pos.at(FOUND_NUM_1) < pos.at(FOUND_NUM_2)) {
            startNumber = pos.at(FOUND_NUM_1);
            endNumber = pos.at(FOUND_NUM_2);
        }
        else {
            startNumber = pos.at(FOUND_NUM_2);
            endNumber = pos.at(FOUND_NUM_1);
        }
        if (!(startNumber < pos.at(FOUND_NUM_3) && pos.at(FOUND_NUM_3) < endNumber)) {
            condition_7++;
            return false;
        }
        return true;
    }

    bool checkAll(vector<int> &input)
    {
        bool result = true;
        bool tempResult = true;
        tempResult = checkCondition_1(input);
        if(tempResult == false) {
            result = false;
#if defined(TEST_CASE_ALL_CHECK)
            return result;
#endif  /* TEST_CASE_ALL_CHECK */
        }
        tempResult = checkCondition_2(input);
        if(tempResult == false) {
            result = false;
#if defined(TEST_CASE_ALL_CHECK)
            return result;
#endif  /* TEST_CASE_ALL_CHECK */
        }
        tempResult = checkCondition_3(input);
        if(tempResult == false) {
            result = false;
#if defined(TEST_CASE_ALL_CHECK)
            return result;
#endif  /* TEST_CASE_ALL_CHECK */
        }
        tempResult = checkCondition_4(input);
        if(tempResult == false) {
            result = false;
#if defined(TEST_CASE_ALL_CHECK)
            return result;
#endif  /* TEST_CASE_ALL_CHECK */
        }
        tempResult = checkCondition_5(input);
        if(tempResult == false) {
            result = false;
#if defined(TEST_CASE_ALL_CHECK)
            return result;
#endif  /* TEST_CASE_ALL_CHECK */
        }
        tempResult = checkCondition_6(input);
        if(tempResult == false) {
            result = false;
#if defined(TEST_CASE_ALL_CHECK)
            return result;
#endif  /* TEST_CASE_ALL_CHECK */
        }
        tempResult = checkCondition_7(input);
        if(tempResult == false) {
            result = false;
#if defined(TEST_CASE_ALL_CHECK)
            return result;
#endif  /* TEST_CASE_ALL_CHECK */
        }
        return result;
    }

    void showCurrentState(vector<int> &input)
    {
        // cout << "[" << __FILE__ << ":" << __LINE__ << "] Enter " << __func__ << "\n";
        for (vector<int>::iterator it = input.begin();it != input.end();it++) {
            cout << " " << *it;
        }
        cout << "\n";
        // cout << "\n[" << __FILE__ << ":" << __LINE__ << "] Finish " << __func__ << "\n";
    }

private:
    int tryCount;
    int validCount;
    int condition_1;
    int condition_2;
    int condition_3;
    int condition_4;
    int condition_5;
    int condition_6;
    int condition_7;

    vector<int> inputData;
};

int main(int argc, char** argv)
{
    CTest ctest;

    ctest.runReal();

    return 0;
}