// File created by: Liam Newberry & Lyle Stone

#include "Board.h"
#include "Player.h"
#include "Setup.h"
#include "GameLoop.h"
#include "HelperMethods.h"
#include "EndGame.h"

using namespace std;

// main driver function
int main() {
    bool new_game = true;

    while (new_game) {
        HelperMethods::clearTerminal();

        Player player1, player2;
        Setup::intialize_players(player1, player2);

        HelperMethods::clearPrintHeading("Game Begin");

        Board board(player1, player2);
        GameLoop loop(player1, player2, board);

        loop.runLoop();

        new_game = EndGame::runLoop(player1, player2);
    }

    HelperMethods::clearPrintHeading("Thank you for playing!");

    return 0;
}