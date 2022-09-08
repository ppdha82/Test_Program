#include <iostream>
#include <cstdlib>

using namespace std;
enum {
    KING = 1,
    QUEEN = 1,
    ROOK = 2,
    BISHOP = 2,
    KNIGHT = 2,
    PAWN = 8,
};

int main(void)
{
    int king = 0;
    int queen = 0;
    int rook = 0;
    int bishop = 0;
    int knight = 0;
    int pawn = 0;

    cin >> king >> queen >> rook >> bishop >> knight >> pawn;

    if(king < 0 || king > 10 || queen < 0 || queen > 10 || rook < 0 || rook > 10 || bishop < 0 || bishop > 10 || knight < 0 || knight > 10 || pawn < 0 || pawn > 10) {
        cout << "Invalid value: king(" << king << ")" << "queen(" << queen << ")" << "rook(" << rook << ")" << "bishop(" << bishop << ")" << "knight(" << knight << ")" << "pawn(" << pawn << ")" << endl;
        return -1;
    }

	cout << KING - king << " " << QUEEN - queen << " " << ROOK - rook << " " << BISHOP - bishop << " " << KNIGHT - knight << " " << PAWN - pawn << endl;

	return 0;
}
