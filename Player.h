// File created by: Liam Newberry & Lyle Stone

#ifndef OVERVIEW_H
#define OVERVIEW_H

#include <string>

#include "Character.h"
#include "Advisor.h"

using namespace std;

// struct to hold all player-related data
struct Player {
    string name;
    string plain_name;
    string color;
    Character character;
    string path;
    Advisor advisor;
};

#endif