#ifndef OVERVIEW_H
#define OVERVIEW_H

#include <string>

#include "Character.h"
#include "Advisor.h"

using namespace std;

struct Player {
    string name;
    string plain_name;
    string color;
    Character character;
    string path;
    Advisor advisor;
};

#endif