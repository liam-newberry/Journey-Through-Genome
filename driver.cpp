#include <iostream>
#include <vector>

#include "Board.h"
#include "Tile.h"
#include "Character.h"
#include "Player.h"

using namespace std;

// check if character input is number between 1 and 5
bool isValidCharacterChoice(string s) {
    try {
        int x = stoi(s); // convert the string to int
        return x >= 1 && x <= 5; // return input is in range of options
    } catch (const invalid_argument) { // if non number input to stoi
        return false;
    }
}

// get players' choice of character
void getCharacterChoice(Player& player) {
    vector<Character> characters = make_characters();

    string input;
    int intInput;

    cout << "\n\n\n";

    while (true) { // this is used to make the input safe if the input is invalid
        printHeaders();
        for (int i = 0; i < characters.size(); i++) {
            characters[i].print();
            cout << endl;
        }

        cout << endl << player.name << ", pick your character 1-5: ";
        cin >> input;

        if (isValidCharacterChoice(input)) {
            player.character = characters[stoi(input) - 1];
            break;
        } else {
            cout << "\033[31mInvalid input\033[0m" << endl << endl; // This makes the error code red
        }
    }
}

// set player names and characters
void intialize_players(Player& player1, Player& player2) {
    cout << "Player 1 name: ";
    cin >> player1.name;

    cout << "Player 2 name: ";
    cin >> player2.name;   

    getCharacterChoice(player1);
    getCharacterChoice(player2);
}

// main driver function
int main() {
    Player player1, player2;
    intialize_players(player1, player2);

    // Board b;
    // b.displayBoard();

    // while (!b.movePlayer(0)) {}
    // while (!b.movePlayer(1)) {}

    // b.displayBoard();

    return 0;
}