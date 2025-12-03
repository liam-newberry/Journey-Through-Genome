// File created by: Liam Newberry & Lyle Stone

#ifndef SETUP_H
#define SETUP_H

#include <string>
#include <vector>

#include "Player.h"

using namespace std;

class Setup {
public:
    static vector<Player> intialize_players();

private:
    static vector<Player> getPlayerNames(Player player1, Player player2);
    static Player getPlayerColor(Player player, string taken);
    static Player getCharacterChoice(Player player);
    static Player getPathChoice(Player player);
    static Player getAdvisorChoice(Player player);
    static Player evaluatePathChoice(Player player);
};

#endif