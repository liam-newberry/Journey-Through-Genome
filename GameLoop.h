// File created by: Liam Newberry & Lyle Stone

#ifndef GAMELOOP_H
#define GAMELOOP_H

#include "Player.h"
#include "Board.h"
#include "Event.h"

#include <vector>

class GameLoop {
public:
    GameLoop(Player p1, Player p2, Board b);
    vector<Player> runLoop();

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
    void reviewAdvisorDescription();
    void reviewAdvisorBonuses();
    void moveForward();

    void rolledGreen();
    void rolledBlue();
    void rolledPink();
    void rolledBrown();
    void rolledRed();
    void rolledPurple();
    void rolledOrange();

    int getTurn() const;
    Player getCurrentPlayer();
    void changeTurn();
    // Member variables
    Player player1, player2;
    Board board;
    int turn;
    // Events and Riddles from text files
    vector<Event> events;
    vector<vector<string>> riddles;
};

#endif