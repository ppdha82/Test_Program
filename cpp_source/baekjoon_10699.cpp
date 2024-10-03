#include <iostream>
#include <cstdlib>
#include <climits>
#include <ctime>

using namespace std;

int main(void)
{
    enum {
        YEAR_BASE = 1900,
    };
    time_t timer;
    struct tm *t;
#if 0
    time_t timer_problem;
    char* str;
    string answer;
    const char* STR_UTC = " UTC";

    time(&timer_problem);
    str = ctime(&timer_problem);


    answer = str;
    cout << answer.insert(answer.rfind(" "), STR_UTC) << "\n";
#endif
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    timer = time(NULL);
    t = localtime(&timer);

    cout << t->tm_year + YEAR_BASE << "-";
    cout.width(2);
    cout.fill('0');
    cout << t->tm_mon + 1 << "-";
    cout << t->tm_mday;
#if 0
    // Wed Mar 21 05:07:38 UTC 2018
#if defined(__DEBUG_ON__)
    cout << "[" << __FILE__ << ":" << __LINE__ << "]" << "YYYY-MM-DD hh:mm:ss weekday\n";
#endif  /* __DEBUG_ON__ */
    cout << t->tm_year + YEAR_BASE << "-";
    cout.width(2);
    cout.fill('0');
    cout << t->tm_mon << "-";
    cout << t->tm_mday + 1 << " ";
    cout << t->tm_hour << ":";
    cout << t->tm_min << ":";
    cout << t->tm_sec << " ";
    switch(t->tm_wday) {
        case 0:
            cout << "SUN" << "\n";
        break;
        case 1:
            cout << "MON" << "\n";
        break;
        case 2:
            cout << "TUE" << "\n";
        break;
        case 3:
            cout << "WED" << "\n";
        break;
        case 4:
            cout << "THU" << "\n";
        break;
        case 5:
            cout << "FRI" << "\n";
        break;
        case 6:
            cout << "SAT" << "\n";
        break;
    }
#endif
    return 0;
}