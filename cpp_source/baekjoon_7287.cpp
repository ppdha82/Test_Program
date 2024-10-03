#include <iostream>
#include <cstdlib>
#include <climits>
#include <sys/socket.h>
#include <resolv.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

int main(void)
{
    const string MY_ID("ppdha82");
    const int SOLVED_PROBLEM = 78;

    cin.tie(NULL);
    ios::sync_with_stdio(false);

    cout << SOLVED_PROBLEM << "\n" << MY_ID;
#if defined(__DEBUG_ON__)
    cout << "\n";
#endif  /* __DEBUG_ON__ */

    return 0;
}