#ifndef ENDGAME_H
#define ENDGAME_H

#include "Player.h"

class EndGame {
public:
    static bool runLoop(Player& player1, Player& player2);

private:
    static void configureDiscoveryPoints(Player& player);
    static void updateScores(Player& player1, Player& player2);
    static void printWinnerHeading(Player& player1, Player& player2);
    static int getNextChoice();
    static void displayScores();
};

#endif