// File created by: Liam Newberry & Lyle Stone

#include "GameLoop.h"
#include "HelperMethods.h"
#include "EscapeColors.h"
#include "Event.h"
#include "DNA.h"

#include <iostream>
#include <ctime>
#include <vector>

using namespace std;

GameLoop::GameLoop(Player& p1, Player& p2, Board& b) : player1(p1), player2(p2), board(b) {
    turn = 0;
    events = HelperMethods::getEvents();
    riddles = HelperMethods::getRiddles();
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
        cout <<         "Display the advisor’s description"
             << endl << "Display the advisor's bonuses"
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
        case 1: reviewAdvisorDescription(); break;
        case 2: reviewAdvisorBonuses(); break;
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

void GameLoop::reviewAdvisorDescription() { 
    Player& player = getCurrentPlayer();

    cout << EscapeColors::colorString(player.advisor.name, EscapeColors::MAGENTA)
         << ": " << player.advisor.description << endl << endl;
}

void GameLoop::reviewAdvisorBonuses() {
    Player& player = getCurrentPlayer();

    cout << EscapeColors::colorString(player.advisor.name, EscapeColors::MAGENTA)
         << " bonuses: " << endl 
         << "   Negative recovery: " << (1 - player.advisor.negative_recovery) * 100 << "%" << endl
         << "   Positive bonuses:  " << (player.advisor.positive_bonus - 1) * 100    << "%" << endl 
         << endl;
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

    switch (board.getCurrentTileColor(turn)) {
        case 'G': rolledGreen(); break;
        case 'B': rolledBlue(); break;
        case 'P': rolledPink(); break;
        case 'T': rolledBrown(); break;
        case 'R': rolledRed(); break;
        case 'U': rolledPurple(); break;
        case 'O': rolledOrange(); break;
    }

    changeTurn();
}

void GameLoop::rolledGreen() {
    if (HelperMethods::randomInt(1)) { // 50% chance
        Player& player = getCurrentPlayer();
        int rand_ind;
        Event event;

        while (event.path != player.path) {
            rand_ind = HelperMethods::randomInt(events.size() - 1);
            event = events[rand_ind];
        }

        events[rand_ind] = events[events.size() - 1];
        events.pop_back();

        cout << event.description << endl << endl;

        if (HelperMethods::inAdvisorVector(player.advisor, event.advisor_vector)) {
            if (player.advisor.remaining_uses > 0) {
                string input;

                while (true) {
                    cout << "Your advisor has " 
                         << EscapeColors::colorString(player.advisor.remaining_uses, EscapeColors::CYAN)
                         << " uses left" << endl;
                    cout << "Would you like to use "
                         << EscapeColors::colorString(player.advisor.name + "'s", EscapeColors::MAGENTA)
                         << " abilities, y/n? ";
                    cin >> input;

                    if (input == "y" || input == "n") {
                        cout << endl;
                        break;
                    } else {
                        HelperMethods::invalidInput();
                    }
                }

                if (input == "y") {
                    event.discoveryPoints > 0 ? event.discoveryPoints *= player.advisor.positive_bonus :
                                                event.discoveryPoints *= player.advisor.negative_recovery;
                    player.advisor.remaining_uses--;
                } 

            } else {
                cout << EscapeColors::colorString(player.advisor.name, EscapeColors::MAGENTA)
                     << " is out of ability uses" << endl << endl;
            }
        } 

        if (event.discoveryPoints < 0) {
            cout << "You lost "
                 << EscapeColors::colorString(-1 * event.discoveryPoints, EscapeColors::RED)
                 << " points" << endl << endl;
        } else {
            cout << "You gained "
                 << EscapeColors::colorString(event.discoveryPoints, EscapeColors::GREEN)
                 << " points" << endl << endl;
        }

        player.character.changeDiscoveryPoints(event.discoveryPoints);

    } else {
        cout << EscapeColors::colorString("No event", EscapeColors::RED) << endl << endl;
    }
}

void GameLoop::rolledBlue() {
    int strand_length = HelperMethods::randomInt(8,12);

    string strand1 = "";

    for (int i = 0; i < strand_length; i++) {
        switch (HelperMethods::randomInt(1,4)) {
            case 1: strand1 += "A"; break;
            case 2: strand1 += "C"; break;
            case 3: strand1 += "G"; break;
            case 4: strand1 += "T"; break;
        }
    }

    string strand2 = strand1;

    for (int i = 0; i < strand_length; i++) {
        if (HelperMethods::randomInt(1,3) == 1) {
            switch (HelperMethods::randomInt(1,4)) {
                case 1: strand2[i] = 'A'; break;
                case 2: strand2[i] = 'C'; break;
                case 3: strand2[i] = 'G'; break;
                case 4: strand2[i] = 'T'; break;
            }
        }
    }
    cout << "Strand A: ";
    for (int i = 0; i < strand_length; i++) {
        HelperMethods::printNeucleotide(strand1[i]);
        cout << " ";
    }
    cout << endl << "Strand B: ";
    for (int i = 0; i < strand_length; i++) {
        HelperMethods::printNeucleotide(strand2[i]);
        cout << " ";
    }
    cout << endl << endl;

    string input;

    while (true) {
        cout << "What percent (round to whole number) of the strands match (ex. 50 if half match)? ";
        cin >> input;

        if (HelperMethods::isValidIntChoice(input, 0, 100)) {
            cout << endl;
            break;
        } else {
            HelperMethods::invalidInput();
        }
    }

    if (stoi(input) == int(DNA::strandSimilarity(strand1, strand2) * 100)) {
        cout << EscapeColors::colorString("Correct! +2000 Discovery Points", EscapeColors::GREEN)
             << endl << endl;
        getCurrentPlayer().character.changeDiscoveryPoints(2000); 
    } else {
        cout << "The answer is "
             << EscapeColors::colorString(int(DNA::strandSimilarity(strand1, strand2) * 100), EscapeColors::YELLOW)
             << endl << endl;

        cout << EscapeColors::colorString("Incorrect! -1000 Discovery Points", EscapeColors::RED)
             << endl << endl;
        getCurrentPlayer().character.changeDiscoveryPoints(-1000);
    }
}

void GameLoop::rolledPink() {

}

void GameLoop::rolledBrown() {

}

void GameLoop::rolledRed() {

}

void GameLoop::rolledPurple() {
    int rand_ind = HelperMethods::randomInt(riddles.size() - 1);
    vector<string> riddle = riddles[rand_ind];

    riddles[rand_ind] = riddles[riddles.size() - 1];
    riddles.pop_back();

    string input;

    cout << riddle[0] << endl;
    cin >> input;
    
    if (HelperMethods::stringCompare(input, riddle[1])) {
        cout << endl
             << EscapeColors::colorString("Correct! +500 Discovery Points", EscapeColors::GREEN)
             << endl << endl;
        getCurrentPlayer().character.changeDiscoveryPoints(500);
    } else {
        cout << endl << "The answer is " 
             << EscapeColors::colorString(riddle[1], EscapeColors::YELLOW)
             << endl;

        cout << endl
             << EscapeColors::colorString("Incorrect! -100 Discovery Points", EscapeColors::RED)
             << endl << endl;
        getCurrentPlayer().character.changeDiscoveryPoints(-100);
    }
}

void GameLoop::rolledOrange() {
    Player& player = getCurrentPlayer();

    cout << player.name << " has reached the finish line!" << endl << endl;
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