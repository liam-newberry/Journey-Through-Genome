// File created by: Liam Newberry & Lyle Stone

#ifndef BOARD_H
#define BOARD_H

#include "Tile.h"
#include "Player.h"

class Board {
    private:
        // Static in this context: Belongs to the class, not each object
        static const int _BOARD_SIZE = 52;
        static const int _MAX_PLAYERS = 2;

        Player player1;
        Player player2;

        // Composition!
        Tile _tiles[2][_BOARD_SIZE];

        int _player_count;
        int _player_position[_MAX_PLAYERS];

        void initializeTiles(int player_index);
        bool isPlayerOnTile(int player_index, int pos);
        void displayTile(int player_index, int pos);

    public:
        // Default Constructor
        Board();
        Board(Player p1, Player p2);

        void initializeBoard();
        void displayTrack(int player_index);
        void displayBoard();
        bool movePlayer(int player_index);
        bool movePlayer(int player_index, int squares);
        // Recall we can use const for getter functions
        int getPlayerPosition(int player_index) const;
        char getCurrentTileColor(int player_index) const;
};

#endif