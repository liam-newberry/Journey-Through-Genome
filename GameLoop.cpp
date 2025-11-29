// File created by: Liam Newberry & Lyle Stone

#include "GameLoop.h"
#include "HelperMethods.h"
#include "EscapeColors.h"

#include <iostream>
#include <ctime>

using namespace std;

GameLoop::GameLoop(Player& p1, Player& p2, Board& b) : player1(p1), player2(p2), board(b) {
    turn = 0;
}

void GameLoop::runLoop() {
    while (board.getPlayerPosition(0) < 51 || board.getPlayerPosition(1) < 51) {
        evaluateMenuChoice(getMenuChoice());
    }
}

int GameLoop::getMenuChoice() {
    Player& player = getCurrentPlayer();

    int numChoices = player.advisor.name == "" ? 4 : 5;

    string input;

    while (true) { 
        cout <<         "Check Player Progress: Review Discover Points or Review Trait stats"
             << endl << "Review Character: Check your character name and experience"
             << endl << "Check Position: Display board to view current position"
             << endl << "Move Forward: Access this option to spin the virtual spinner";
        if (numChoices == 5) {
            cout << endl 
                 << "Review your Advisor: Display the advisor’s abilities or Use the abilities for the challenge";
        }

        cout << endl << endl 
             << player.name << ", what is your choice 1-" << numChoices << "? ";
        cin >> input;

        if (HelperMethods::isValidIntChoice(input, 1, numChoices)) {
            cout << endl;
            return stoi(input);
        } else {
            HelperMethods::invalidInput();
        }
    }
}

int GameLoop::getPlayerProgressChoice() {
    Player& player = getCurrentPlayer();

    string input;

    while (true) { 
        cout <<         "Review Discover Points"
             << endl << "Review Trait stats";

        cout << endl << endl << player.name << ", what is your choice 1-2? ";
        cin >> input;

        if (HelperMethods::isValidIntChoice(input, 1, 2)) {
            cout << endl;
            return stoi(input);
        } else {
            HelperMethods::invalidInput();
        }
    }
}

int GameLoop::getReviewAdvisorChoice() {
    Player& player = getCurrentPlayer();

    string input;

    while (true) { 
        cout <<         "Display the advisor’s abilities"
             << endl << "Use the abilities for the challenge"
             << endl << endl;

        cout << player.name << ", what is your choice 1-2? ";
        cin >> input;

        if (HelperMethods::isValidIntChoice(input, 1, 2)) {
            cout << endl;
            return stoi(input);
        } else {
            HelperMethods::invalidInput();
        }
    }
}

void GameLoop::evaluateMenuChoice(int choice) {
    switch(choice) {
        case 1: evaluatePlayerProgressChoice(getPlayerProgressChoice()); break;
        case 2: reviewCharacter(); break;
        case 3: reviewPosition(); break;
        case 4: moveForward(); break;
        case 5: evaluateReviewAdvisorChoice(getReviewAdvisorChoice()); break;
    }
}

void GameLoop::evaluatePlayerProgressChoice(int choice) {
    switch(choice) {
        case 1: reviewDiscoverPoints(); break;
        case 2: reviewTraitStats(); break;
    }
}

void GameLoop::evaluateReviewAdvisorChoice(int choice) {
    switch(choice) {
        case 1: reviewAdvisorAbilities(); break;
        case 2: useAdvisorAbilities(); break;
    }
}

void GameLoop::reviewDiscoverPoints() {
    Player& player = getCurrentPlayer();

    cout << "Discovery Points: "
         << EscapeColors::colorString(player.character.getDiscoveryPoints(), EscapeColors::YELLOW)
         << endl << endl;
}

void GameLoop::reviewTraitStats() {
    Player& player = getCurrentPlayer();

    cout <<         "Experience: " 
         << EscapeColors::colorString(player.character.getExperience(), EscapeColors::YELLOW)
         << endl << "Accuracy:   " 
         << EscapeColors::colorString(player.character.getAccuracy(), EscapeColors::YELLOW)
         << endl << "Efficiency: " 
         << EscapeColors::colorString(player.character.getEfficiency(), EscapeColors::YELLOW)
         << endl << "Insight:    " 
         << EscapeColors::colorString(player.character.getInsight(), EscapeColors::YELLOW)
         << endl << endl;
}

void GameLoop::reviewCharacter() {
    Player& player = getCurrentPlayer();
    
    cout << EscapeColors::colorString(player.character.getName(), EscapeColors::CYAN)
         << " has " 
         << EscapeColors::colorString(player.character.getExperience(), EscapeColors::YELLOW)
         << " experience" << endl << endl;
}

void GameLoop::reviewPosition() {
    Player& player = getCurrentPlayer();

    cout << player.name << " is at tile " 
         << EscapeColors::colorString(board.getPlayerPosition(turn), EscapeColors::BLUE)
         << "." << endl << endl;
}

void GameLoop::reviewAdvisorAbilities() { 
    Player& player = getCurrentPlayer();

    cout << EscapeColors::colorString(player.advisor.name, EscapeColors::MAGENTA)
         << ": " << player.advisor.description << endl << endl;
}

void GameLoop::useAdvisorAbilities() {

}

void GameLoop::moveForward() {
    Player& player = getCurrentPlayer();

    srand(time(0));

    int roll = (rand() % 6) + 1;
    int forward = roll;

    if (forward + board.getPlayerPosition(turn) > 51) {
        forward =  51 - board.getPlayerPosition(turn);
    }

    HelperMethods::clearTerminal();

    board.movePlayer(turn, forward);

    board.displayBoard();

    cout << player.name << " rolled a " 
         << EscapeColors::colorString(roll, EscapeColors::RED)
         << "!" << endl << endl;

    changeTurn();
}

int GameLoop::getTurn() const {
    return turn;
}

Player& GameLoop::getCurrentPlayer() {
    return turn == 0 ? player1 : player2;
}

void GameLoop::changeTurn() {
    if (board.getPlayerPosition(0) == 51) {
        turn = 1;
        return;
    } else if (board.getPlayerPosition(1) == 51) {
        turn = 0;
        return;
    }

    turn++;
    turn = turn % 2;
}