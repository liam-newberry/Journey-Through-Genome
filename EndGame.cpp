// File created by: Liam Newberry & Lyle Stone

#include "EndGame.h"
#include "HelperMethods.h"
#include "EscapeColors.h"

#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

bool EndGame::runLoop(Player& player1, Player& player2) {
    configureDiscoveryPoints(player1);
    configureDiscoveryPoints(player2);

    updateScores(player1, player2);

    printWinnerHeading(player1, player2);

    while (true) {
        switch(getNextChoice()) {
            case 1: return true; break;
            case 2: displayScores(); break;
            case 3: return false; break;
        }
    }
}

void EndGame::configureDiscoveryPoints(Player& player) {
    int total = 0;
    total += player.character.getAccuracy();
    total += player.character.getEfficiency();
    total += player.character.getExperience();
    total += player.character.getInsight();

    total -= total % 100;
    total *= 10;

    player.character.changeDiscoveryPoints(total);
}

void EndGame::updateScores(Player& player1, Player& player2) {
    vector<vector<string>> scores = HelperMethods::getScores();

    scores.push_back({player1.plain_name, to_string(player1.character.getDiscoveryPoints())});
    scores.push_back({player2.plain_name, to_string(player2.character.getDiscoveryPoints())});

    HelperMethods::sortScores(scores);

    while (scores.size() > 10) {
        scores.pop_back();
    }

    HelperMethods::writeScores(scores);
}

void EndGame::printWinnerHeading(Player& player1, Player& player2) {
    if (player1.character.getDiscoveryPoints() == player2.character.getDiscoveryPoints()) {
        HelperMethods::clearPrintHeading("It's a Tie!");
    } else {
        Player& winner = player1.character.getDiscoveryPoints() > player2.character.getDiscoveryPoints() ?
            player1 : player2;
        HelperMethods::clearPrintHeading(winner.name + EscapeColors::colorString(" Wins!", EscapeColors::MAGENTA));
    }

    cout << player1.name << " had " 
         << EscapeColors::colorString(player1.character.getDiscoveryPoints(), EscapeColors::YELLOW)
         << " discovery points" << endl;
    cout << player2.name << " had " 
         << EscapeColors::colorString(player2.character.getDiscoveryPoints(), EscapeColors::YELLOW)
         << " discovery points" << endl << endl;
}

int EndGame::getNextChoice() {
    cout << "Congrats on finishing! What's your next move?" << endl << endl;

    string input;

    while (true) { // this is used to make the input safe if the input is invalid
        cout <<         "Play again"
             << endl << "View scores"
             << endl << "End Game";

        cout << endl << endl << "Pick your choice 1-3: ";
        cin >> input;

        if (HelperMethods::isValidIntChoice(input, 1, 3)) {
            cout << endl;
            return stoi(input);
        } else {
            HelperMethods::invalidInput();
        }
    }
}

void EndGame::displayScores() {
    cout << "Top Scores of All Time" << endl << endl;

    vector<vector<string>> scores = HelperMethods::getScores();

    cout << "    " << left << setw(21) << "Name" << "Score" << endl;

    for (int i = 0; i < scores.size(); i++) {
        switch(i) {
            case 0: 
                cout << EscapeColors::colorString("1.  ", EscapeColors::YELLOW); 
                cout << setw(30)
                     << EscapeColors::colorString(scores[i][0], EscapeColors::YELLOW)
                     << EscapeColors::colorString(scores[i][1], EscapeColors::YELLOW)
                     << endl; 
                break;
            case 1: 
                cout << EscapeColors::colorString("2.  ", EscapeColors::CYAN);
                cout << setw(30)
                     << EscapeColors::colorString(scores[i][0], EscapeColors::CYAN)
                     << EscapeColors::colorString(scores[i][1], EscapeColors::CYAN)
                     << endl; 
                break;
            case 2: 
                cout << EscapeColors::colorString("3.  ", EscapeColors::RED);
                cout << setw(30)
                     << EscapeColors::colorString(scores[i][0], EscapeColors::RED)
                     << EscapeColors::colorString(scores[i][1], EscapeColors::RED)
                     << endl; 
                break;
            case 9:
                cout << EscapeColors::colorString("10. ", EscapeColors::BLACK); // 1 space not 2
                cout << setw(30)
                     << EscapeColors::colorString(scores[i][0], EscapeColors::BLACK)
                     << EscapeColors::colorString(scores[i][1], EscapeColors::BLACK)
                     << endl; 
                break;
            default:
                cout << EscapeColors::colorString(to_string(i + 1) + ".  ", EscapeColors::BLACK);
                cout << setw(30)
                     << EscapeColors::colorString(scores[i][0], EscapeColors::BLACK)
                     << EscapeColors::colorString(scores[i][1], EscapeColors::BLACK)
                     << endl;
                break;
        }
    }   

    cout << endl;
}