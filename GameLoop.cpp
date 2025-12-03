// File created by: Liam Newberry & Lyle Stone

#include "GameLoop.h"
#include "HelperMethods.h"
#include "EscapeColors.h"
#include "Event.h"
#include "DNA.h"

#include <iostream>
#include <vector>

using namespace std;

// constructor to initialize players and board and read text files
GameLoop::GameLoop(Player p1, Player p2, Board b) : player1(p1), player2(p2), board(b) {
    turn = 0;
    events = HelperMethods::getEvents();
    riddles = HelperMethods::getRiddles();
}

// main game loop that continues until a player reaches the end of the board
vector<Player> GameLoop::runLoop() {
    while (board.getPlayerPosition(0) < 51 || board.getPlayerPosition(1) < 51) {
        evaluateMenuChoice(getMenuChoice());
    }

    return {player1, player2};
}

// get the main menu choice from the user
int GameLoop::getMenuChoice() {
    Player player = getCurrentPlayer();

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

// get the player progress menu choice from the user
int GameLoop::getPlayerProgressChoice() {
    Player player = getCurrentPlayer();

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

// get the review advisor menu choice from the user
int GameLoop::getReviewAdvisorChoice() {
    Player player = getCurrentPlayer();

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

// evaluate the main menu choice
void GameLoop::evaluateMenuChoice(int choice) {
    switch(choice) {
        case 1: evaluatePlayerProgressChoice(getPlayerProgressChoice()); break;
        case 2: reviewCharacter(); break;
        case 3: reviewPosition(); break;
        case 4: moveForward(); break;
        case 5: evaluateReviewAdvisorChoice(getReviewAdvisorChoice()); break;
    }
}

// evaluate the player progress menu choice
void GameLoop::evaluatePlayerProgressChoice(int choice) {
    switch(choice) {
        case 1: reviewDiscoverPoints(); break;
        case 2: reviewTraitStats(); break;
    }
}

// evaluate the review advisor menu choice
void GameLoop::evaluateReviewAdvisorChoice(int choice) {
    switch(choice) {
        case 1: reviewAdvisorDescription(); break;
        case 2: reviewAdvisorBonuses(); break;
    }
}

// review the current player's discovery points
void GameLoop::reviewDiscoverPoints() {
    Player player = getCurrentPlayer();

    cout << "Discovery Points: "
         << EscapeColors::colorString(player.character.getDiscoveryPoints(), EscapeColors::YELLOW)
         << endl << endl;
}

// review the current player's trait stats
void GameLoop::reviewTraitStats() {
    Player player = getCurrentPlayer();

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

// review the current player's character and experience
void GameLoop::reviewCharacter() {
    Player player = getCurrentPlayer();
    
    cout << EscapeColors::colorString(player.character.getName(), EscapeColors::CYAN)
         << " has " 
         << EscapeColors::colorString(player.character.getExperience(), EscapeColors::YELLOW)
         << " experience" << endl << endl;
}

// review the current player's position on the board
void GameLoop::reviewPosition() {
    Player player = getCurrentPlayer();

    cout << player.name << " is at tile " 
         << EscapeColors::colorString(board.getPlayerPosition(turn) + 1, EscapeColors::BLUE)
         << "." << endl << endl;
}

// review the current player's advisor description
void GameLoop::reviewAdvisorDescription() { 
    Player player = getCurrentPlayer();

    cout << EscapeColors::colorString(player.advisor.name, EscapeColors::MAGENTA)
         << ": " << player.advisor.description << endl << endl;
}

// review the current player's advisor bonuses
void GameLoop::reviewAdvisorBonuses() {
    Player player = getCurrentPlayer();

    cout << EscapeColors::colorString(player.advisor.name, EscapeColors::MAGENTA)
         << " bonuses: " << endl 
         << "   Negative recovery: " << (1 - player.advisor.negative_recovery) * 100 << "%" << endl
         << "   Positive bonuses:  " << (player.advisor.positive_bonus - 1) * 100    << "%" << endl 
         << endl;
}

// roll a die 1-6 and call a function based on the tile color landed on
void GameLoop::moveForward() {
    Player player = getCurrentPlayer();

    int roll = HelperMethods::randomInt(1,6);
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

// 50% chance to trigger an event for discovery points
void GameLoop::rolledGreen() {
    if (HelperMethods::randomInt(1)) { // 50% chance
        Player player = getCurrentPlayer();
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

// DNA strand similarity challenge (same length strands)
void GameLoop::rolledBlue() {
    string strand1 = DNA::makeInputStrand();
    string strand2 = DNA::makeTargetStrand(strand1, false);
    
    cout << "Strand A: ";
    DNA::printStrand(strand1);
    cout << endl;

    cout << "Strand B: ";
    DNA::printStrand(strand2);
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

    if (stoi(input) == HelperMethods::makeWholePercent(DNA::strandSimilarity(strand1, strand2))) {
        cout << EscapeColors::colorString("Correct! +2000 Discovery Points", EscapeColors::GREEN)
             << endl << endl;
        getCurrentPlayer().character.changeDiscoveryPoints(2000); 
    } else {
        cout << "The answer is "
             << EscapeColors::colorString(HelperMethods::makeWholePercent(DNA::strandSimilarity(strand1, strand2)), 
                                                                          EscapeColors::YELLOW)
             << endl << endl;

        cout << EscapeColors::colorString("Incorrect! -1000 Discovery Points", EscapeColors::RED)
             << endl << endl;
        getCurrentPlayer().character.changeDiscoveryPoints(-1000);
    }
}

// DNA strand similarity challenge (different length strands)
void GameLoop::rolledPink() {
    string strand1 = DNA::makeInputStrand();
    string strand2 = DNA::makeTargetStrand(strand1, true);

    cout << "Strand A: ";
    DNA::printStrand(strand1);
    cout << endl;

    cout << "Strand B: ";
    DNA::printStrand(strand2);
    cout << endl << endl;

    string input;

    while (true) {
        cout << "What percent (round to whole number) of the strands match in the best fit (ex. 50 if half match)? ";
        cin >> input;

        if (HelperMethods::isValidIntChoice(input, 0, 100)) {
            cout << endl;
            break;
        } else {
            HelperMethods::invalidInput();
        }
    } 

    if (stoi(input) == HelperMethods::makeWholePercent(DNA::strandSimilarity(strand1, strand2))) {
        cout << EscapeColors::colorString("Correct! +5000 Discovery Points", EscapeColors::GREEN)
             << endl << endl;
        getCurrentPlayer().character.changeDiscoveryPoints(5000); 
    } else {
        cout << "The answer is "
             << EscapeColors::colorString(HelperMethods::makeWholePercent(DNA::strandSimilarity(strand1, strand2)), 
                                                                          EscapeColors::YELLOW)
             << endl << endl;

        cout << EscapeColors::colorString("Incorrect! -2500 Discovery Points", EscapeColors::RED)
             << endl << endl;
        getCurrentPlayer().character.changeDiscoveryPoints(-2500);
    }
}

// DNA to RNA transcription challenge
void GameLoop::rolledBrown() {
    cout << "Please transcribe the following DNA sequence into RNA by replacing every ";
    DNA::printNeucleotide('T');
    cout << " with a ";
    DNA::printNeucleotide('U');
    cout << endl 
         << EscapeColors::colorString("DO NOT", EscapeColors::RED)
         << " use spaces!" << endl << endl;

    string strand1 = DNA::makeInputStrand();

    cout << "DNA sequence: ";
    DNA::printStrand(strand1);
    cout << endl;
       
    cout << "RNA sequence: "; 
    string input;
    cin >> input;
    cout << endl;

    if (DNA::transcribeDNAtoRNA(strand1) == input) {
        cout << EscapeColors::colorString("Correct! +2000 Discovery Points", EscapeColors::GREEN)
             << endl << endl;
        getCurrentPlayer().character.changeDiscoveryPoints(2000); 
    } else {
        cout << "The answer is ";
        DNA::printStrand(DNA::transcribeDNAtoRNA(strand1));
        cout << endl << endl;

        cout << EscapeColors::colorString("Incorrect! -1000 Discovery Points", EscapeColors::RED)
             << endl << endl;
        getCurrentPlayer().character.changeDiscoveryPoints(-1000);
    }
}

// DNA mutation identification challenge
void GameLoop::rolledRed() {
    cout << "Identify the following mutations in the following sequence" << endl
         << "Use " 
         << EscapeColors::colorString("i", EscapeColors::BLUE) << " for insertion, "
         << EscapeColors::colorString("s", EscapeColors::YELLOW) << " for substitution, and "
         << EscapeColors::colorString("d", EscapeColors::RED) 
         << " for deletion to represent the mutations in order" << endl

         << "An " << EscapeColors::colorString("insertion", EscapeColors::BLUE)
         << " is when there is a "
         << EscapeColors::colorString("deletion", EscapeColors::RED)
         << " to the left or right of a mismatch" << endl

         << "A " << EscapeColors::colorString("substitution", EscapeColors::YELLOW)
         << " is a mismatch that is not a " 
         << EscapeColors::colorString("deletion", EscapeColors::RED) << endl

         << "A " << EscapeColors::colorString("deletion", EscapeColors::RED) 
         << " is when there is a missing neucleotide" << endl

         << "Example: dsssi" << endl << endl;
    
    string strand1 = DNA::makeInputStrand();
    string strand2 = strand1;
    while (DNA::strandSimilarity(strand1, strand2) == 1) {
        strand2 = DNA::makeTargetStrand(strand1, true);
    }

    cout << "          ";
    for (int i = 0; i < strand1.size(); i++) {
        cout << i + 1 << (i < 9 ? "  " : " ");
    }

    cout << endl << "Strand A: ";
    DNA::printStrand(strand1, "  ");

    int spacing = DNA::bestStrandMatch(strand1, strand2);

    cout << endl << "Strand B: ";
    for (int i = 0; i < spacing; i++) {
        cout << "   ";
    }
    DNA::printStrand(strand2, "  ");
 
    string input;
    cout << endl << endl << "What is the correct sequence of mutations?" << endl;
    cin >> input;
    cout << endl;

    if (DNA::identifyMutations(strand1, strand2, false) == input) {
        cout << EscapeColors::colorString("Correct! +5000 Discovery Points", EscapeColors::GREEN)
             << endl << endl;
        getCurrentPlayer().character.changeDiscoveryPoints(5000); 
    } else {
        cout << "The answer is: " << endl << endl;
        DNA::identifyMutations(strand1, strand2, true);

        cout << EscapeColors::colorString("Incorrect! -2500 Discovery Points", EscapeColors::RED)
             << endl << endl;
        getCurrentPlayer().character.changeDiscoveryPoints(-2500);
    }
}

// riddle challenge
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

// finish line reached
void GameLoop::rolledOrange() {
    Player player = getCurrentPlayer();

    cout << player.name << " has reached the finish line!" << endl << endl;
}

// get the current turn (0 or 1)
int GameLoop::getTurn() const {
    return turn;
}

// get the current player based on the turn
Player GameLoop::getCurrentPlayer() {
    return turn == 0 ? player1 : player2;
}

// change the turn to the next player if applicable
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