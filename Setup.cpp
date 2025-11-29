#include <iostream>
#include <iomanip>
#include <vector>

#include "Setup.h"
#include "Player.h"
#include "EscapeColors.h"
#include "HelperMethods.h"

using namespace std;

// setup player traits
void Setup::intialize_players(Player& player1, Player& player2) {
    HelperMethods::clearPrintHeading("Names");
    getPlayerNames(player1, player2);

    HelperMethods::clearPrintHeading("Colors");
    getPlayerColor(player1, "");
    getPlayerColor(player2, player1.color);
 
    HelperMethods::clearPrintHeading("Characters");
    getCharacterChoice(player1);
    getCharacterChoice(player2);

    HelperMethods::clearPrintHeading("Paths");
    getPathChoice(player1);
    getPathChoice(player2);

    if (player1.path == "Training Fellowship" || player2.path == "Training Fellowship") {
        HelperMethods::clearPrintHeading("Advisors");
    }
    evaluatePathChoice(player1);
    evaluatePathChoice(player2);
}

// get players' names
void Setup::getPlayerNames(Player& player1, Player& player2) {
    cout << "Player 1 name: ";
    cin >> player1.name;
    player1.name = player1.name.substr(0,20); // max name length 20
    player1.plain_name = player1.name;

    cout << endl << "Player 2 name: ";
    cin >> player2.name;
    player2.name = player2.name.substr(0,20); // max name length 20
    player2.plain_name = player2.name;
}

// get the player's color; used every time they're name is displayed
void Setup::getPlayerColor(Player& player, string taken) {
    string input;

    while (true) { // this is used to make the input safe if the input is invalid
        cout << player.name << ", what color would you like? Enter 1-8" << endl;

        for (int i = 0; i < 7; i++) {
            cout << EscapeColors::colorString(i + 1, EscapeColors::COLORS[i]) << ", ";
        }
        cout << EscapeColors::colorString(8, EscapeColors::COLORS[7]) << endl << endl;
        cin >> input;

        if (HelperMethods::isValidIntChoice(input, 1, 8)) {
            player.color = EscapeColors::COLORS[stoi(input) - 1];
            if (player.color == taken) {
                cout << EscapeColors::colorString("Color already taken", EscapeColors::RED) 
                 << endl << endl; // This makes the error code red
            } else {
                player.name = EscapeColors::colorString(player.name, player.color);
                cout << endl;
                break;
            }
        } else {
            HelperMethods::invalidInput();
        }
    }
}

// get players' choice of character
void Setup::getCharacterChoice(Player& player) {
    vector<Character> characters = makeCharacters();

    string input;
    int intInput;

    while (true) { // this is used to make the input safe if the input is invalid
        printHeaders();
        for (int i = 0; i < characters.size(); i++) {
            characters[i].print();
            cout << endl;
        }

        cout << endl << player.name << ", pick your character 1-5: ";
        cin >> input;

        if (HelperMethods::isValidIntChoice(input, 1, 5)) {
            player.character = characters[stoi(input) - 1];
            cout << endl;
            break;
        } else {
            HelperMethods::invalidInput();
        }
    }
}

// get the path choice for a player
void Setup::getPathChoice(Player& player) {
    string input;

    while (true) { // this is used to make the input safe if the input is invalid
        cout << "Would you like to do a " 
             << EscapeColors::colorString("Training Fellowship", EscapeColors::GREEN) << " or "
             << EscapeColors::colorString("Direct Lab Assignment", EscapeColors::GREEN) << "?" << endl;
        cout << "A " << EscapeColors::colorString("Training Fellowship", EscapeColors::GREEN)
             << " is a slower path but skills are developed earlier." << endl;
        cout << "A "
             << EscapeColors::colorString("Direct Lab Assignment", EscapeColors::GREEN)
             << " is a faster but riskier path." << endl;

        cout << endl << player.name << ", pick your path 1 or 2: ";
        cin >> input;

        if (HelperMethods::isValidIntChoice(input, 1, 2)) {
            player.path = input == "1" ? "Training Fellowship" : "Direct Lab Assignment";
            cout << endl;
            break;
        } else {
            HelperMethods::invalidInput();
        }
    }
}

// get the advisor choice if needed for a player
void Setup::getAdvisorChoice(Player& player) {
    vector<Advisor> advisors = makeAdvisors();

    string input;
    int intInput;

    while (true) { // this is used to make the input safe if the input is invalid
        for (int i = 0; i < advisors.size(); i++) {
            cout << left << setw(25) << EscapeColors::colorString(advisors[i].name, EscapeColors::MAGENTA) + ": "
                 << advisors[i].description << endl;
        }

        cout << endl << player.name << ", pick your advisor 1-5: ";
        cin >> input;

        if (HelperMethods::isValidIntChoice(input, 1, 5)) {
            player.advisor = advisors[stoi(input) - 1];
            cout << endl;
            break;
        } else {
            HelperMethods::invalidInput();
        }
    }
}

// change trait values based on the path chosen
void Setup::evaluatePathChoice(Player& player) {
    if (player.path == "Training Fellowship") {
        player.character.changeDiscoveryPoints(-5000);
        player.character.changeAccuracy(500);
        player.character.changeEfficiency(500);
        player.character.changeInsight(1000);

        getAdvisorChoice(player);
    } else if (player.path == "Direct Lab Assignment") {
        player.character.changeDiscoveryPoints(5000);
        player.character.changeAccuracy(200);
        player.character.changeEfficiency(200);
        player.character.changeInsight(200);
    }
}