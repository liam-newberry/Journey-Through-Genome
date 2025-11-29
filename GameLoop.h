// File created by: Liam Newberry & Lyle Stone

#ifndef GAMELOOP_H
#define GAMELOOP_H

#include "Player.h"
#include "Board.h"

class GameLoop {
public:
    GameLoop(Player& p1, Player& p2, Board& b);
    void runLoop();

private:
    int getMenuChoice();
    int getPlayerProgressChoice();
    int getReviewAdvisorChoice();

    void evaluateMenuChoice(int choice);
    void evaluatePlayerProgressChoice(int choice);
    void evaluateReviewAdvisorChoice(int choice);

    void reviewDiscoverPoints();
    void reviewTraitStats();
    void reviewCharacter();
    void reviewPosition();
    void reviewAdvisorAbilities();
    void useAdvisorAbilities();
    void moveForward();

    int getTurn() const;
    Player& getCurrentPlayer();
    void changeTurn();

    Player& player1, player2;
    Board& board;
    int turn;
};

#endif