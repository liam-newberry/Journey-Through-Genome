// Source file calling the header file
#include "Board.h"
#include "HelperMethods.h"
// Recall we use this preprocessor directive for rand() and srand()
#include <cstdlib>
// Similarly, we use this one for time() (The seed for random)
#include <ctime>
#include <iostream>
#include <string>

// Each of the following defines a macro
// Essentially nicenames to use instead of the corresponding escape sequence ('\') 
#define ORANGE "\033[48;2;230;115;0m"
#define GREY "\033[48;2;128;128;128m"
#define GREEN "\033[48;2;34;139;34m"
#define BLUE "\033[48;2;10;10;230m"
#define PINK "\033[48;2;255;105;180m"
#define BROWN "\033[48;2;139;69;19m"
#define RED "\033[48;2;230;10;10m"
#define PURPLE "\033[48;2;128;0;128m"
#define RESET "\033[0m"

using namespace std;

// =========================== Constructor ===========================
Board::Board(Player& p1, Player& p2) : player1(p1), player2(p2) {
    // Creates two players
    _player_count = _MAX_PLAYERS;

    // Initialize player's position
    for (int i = 0; i < _player_count; i++) {
        _player_position[i] = 0;
    }

    // Fill both lanes
    initializeBoard();
}

// =========================== Private Member Functions ===========================
/** 
void initializeTiles(int player_index) {
    Tile tile;
    int green_count = 0;
    // Recall 52 from header file
    int total_tiles = _BOARD_SIZE;

    for (int i = 0; i < total_tiles; i++) {
        // Set the last tile as Orange for the finish line
        if (i == total_tiles - 1) {
            tile.color = 'O';
        } 
        // Set the first tile as Grey for the starting line
        else if (i == 0) {
            tile.color = 'Y';
        } 
        // Hard-coded target of 30 green tiles
        // Probablisitic method to spread out the green tiles randomly
        else if (green_count < 30 && (rand() % (total_tiles - i) < 30 - green_count)) {
            tile.color = 'G';
            green_count++;
        }
        // Randomly assign one of the other colors: Blue, Pink, Brown, Red, Purple
        else {
            int color_choice = rand() % 5;
            switch (color_choice) {
                case 0:
                    tile.color = 'B'; // Blue
                    break;
                case 1:
                    tile.color = 'P'; // Pink
                    break;
                case 2:
                    tile.color = 'T'; // Brown
                    break;
                case 3:
                    tile.color = 'R'; // Red
                    break;
                case 4:
                    tile.color = 'U'; // Purple
                    break;
            }
        }

        // Assign the tile to the board for the specified lane/player 1 or 2
        // Recall i refers to tile 0 to 51
        _tiles[player_index][i] = tile;
    }
} */
void Board::initializeTiles(int player_index) {
    Tile tile;
    Player& player = player_index == 0 ? player1 : player2;
    
    int total_tiles = _BOARD_SIZE;

    tile.color = 'Y';
    _tiles[player_index][0] = tile;
    tile.color = 'O';
    _tiles[player_index][total_tiles - 1] = tile;

    int greens, blues, pinks, browns, reds, purples;
    if (player.path ==        "Training Fellowship") {
        greens =    30;
        blues =     6;
        pinks =     5;
        browns =    3;
        reds =      2;
        purples =   4;
    } else if (player.path == "Direct Lab Assignment") {
        greens =    30;
        blues =     4;
        pinks =     3;
        browns =    4;
        reds =      6;
        purples =   3;
    }

    int rand_num;
    for (int i = 1; i < total_tiles - 1; i++) {
        rand_num = HelperMethods::randomInt(1, greens + blues + pinks + browns + reds + purples);

        if (rand_num <= greens) {
            tile.color = 'G';
            greens--;
        } else if (rand_num <= greens + blues) {
            tile.color = 'B';
            blues--;
        } else if (rand_num <= greens + blues + pinks) {
            tile.color = 'P';
            pinks--;
        } else if (rand_num <= greens + blues + pinks + browns) {
            tile.color = 'T';
            browns--;
        } else if (rand_num <= greens + blues + pinks + browns + reds) {
            tile.color = 'R';
            reds--;
        } else {
            tile.color = 'U';
            purples--;
        }

        _tiles[player_index][i] = tile;
    }
}

bool Board::isPlayerOnTile(int player_index, int pos) {
    if (_player_position[player_index] == pos) {
        return true;
    }
    return false;
}

void Board::displayTile(int player_index, int pos) {
    string color = "";
    int player = isPlayerOnTile(player_index, pos);

    // Using the defined nicenames above
    switch(_tiles[player_index][pos].color) {
        case 'O': color = ORANGE; break;
        case 'Y': color = GREY; break;
        case 'G': color = GREEN; break;
        case 'B': color = BLUE; break;
        case 'P': color = PINK; break;
        case 'T': color = BROWN; break;
        case 'R': color = RED; break;
        case 'U': color = PURPLE; break;
    }

    // Template for displaying a tile: <line filler space> <color start> |<player symbol or blank space>| <reset color> <line filler space> <endl>
    if (player == true) {
        cout << color << "|" << (player_index + 1) << "|" << RESET;
    }
    else {
        cout << color << "| |" << RESET;
    }
}

// =========================== Public Member Functions ===========================

void Board::initializeBoard() {
    initializeTiles(0);
    initializeTiles(1);
}

void Board::displayTrack(int player_index) {
    for (int i = 0; i < _BOARD_SIZE; i++) {
        displayTile(player_index, i);
    }
    cout << endl;
}

void Board::displayBoard() {
    // visually clear terminal
    HelperMethods::clearTerminal();

    cout << player1.name << endl;
    displayTrack(0);
    cout << player2.name << endl;
    displayTrack(1);
    cout << endl << endl;
}

bool Board::movePlayer(int player_index) {
    // Increment player position by 1
    _player_position[player_index]++;

    // Return if player reached last tile
    return _player_position[player_index] == _BOARD_SIZE - 1;
}

bool Board::movePlayer(int player_index, int squares) {
    bool reachedEnd;

    for (int i = 0; i < squares; i++) {
        reachedEnd = movePlayer(player_index);
    }

    return reachedEnd;
}

int Board::getPlayerPosition(int player_index) const {
    if (player_index >= 0 && player_index <= _player_count) {
        return _player_position[player_index];
    }
    return -1;
}