// File created by: Liam Newberry & Lyle Stone

#include "Board.h"
#include "Player.h"
#include "Setup.h"
#include "GameLoop.h"
#include "HelperMethods.h"
#include "EndGame.h"

#include <iostream>

using namespace std;

// main driver function
int main() {
    bool new_game = true;

    while (new_game) {
        HelperMethods::clearTerminal();

        vector<Player> players = Setup::intialize_players();

        HelperMethods::clearPrintHeading("Game Begin");

        Board board(players[0], players[1]);
        GameLoop loop(players[0], players[1], board);

        players = loop.runLoop();

        new_game = EndGame::runLoop(players[0], players[1]);
    }

    HelperMethods::clearPrintHeading("Thank you for playing!");

    cout << "Game written by: Liam Newberry & Lyle Stone" << endl
         << "This work is released into the public domain, 2025." <<endl;

    return 0;
}