// File created by: Liam Newberry & Lyle Stone

#ifndef SETUP_H
#define SETUP_H

#include <string>

#include "Player.h"

using namespace std;

class Setup {
public:
    static void intialize_players(Player& player1, Player& player2);

private:
    static void getPlayerNames(Player& player1, Player& player2);
    static bool isValidIntChoice(string s, int low, int high);
    static void getPlayerColor(Player& player, string taken);
    static void getCharacterChoice(Player& player);
    static void getPathChoice(Player& player);
    static void getAdvisorChoice(Player& player);
    static void evaluatePathChoice(Player& player);
};

#endif