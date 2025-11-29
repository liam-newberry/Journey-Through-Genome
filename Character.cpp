// File created by: Liam Newberry & Lyle Stone

#include "Character.h"
#include "EscapeColors.h"

#include <iostream>
#include <iomanip>

Character::Character() {}

Character::Character(string characterName, int stats[5]) : name(characterName) {
    experience =        stats[0];
    accuracy =          stats[1];
    efficiency =        stats[2];
    insight =           stats[3];
    discoveryPoints =   stats[4];
}

void Character::set_stats(string characterName, int stats[5]) {
    name =              characterName;
    experience =        stats[0];
    accuracy =          stats[1];
    efficiency =        stats[2];
    insight =           stats[3];
    discoveryPoints =   stats[4];
}

string Character::getName() const {
    return name;
}

int Character::getExperience() const {
    return experience;
}

int Character::getAccuracy() const {
    return accuracy;
}

int Character::getEfficiency() const {
    return efficiency;
}

int Character::getInsight() const {
    return insight;
}

int Character::getDiscoveryPoints() const {
    return discoveryPoints;
}

void Character::changeExperience(int amount) {
    experience += amount;
}

void Character::changeAccuracy(int amount) {
    accuracy += amount;
}

void Character::changeEfficiency(int amount) {
    efficiency += amount;
}

void Character::changeInsight(int amount) {
    insight += amount;
}

void Character::changeDiscoveryPoints(int amount) {
    discoveryPoints += amount;
}

void Character::print() const {
    // print all the stats to the left and aling them with printHeaders
    // the alignment is from the headers +9 due to the EscapeColors
    cout << left; 
    cout << setw(24) << EscapeColors::colorString(name, EscapeColors::CYAN);
    cout << setw(21) << EscapeColors::colorString(experience, EscapeColors::YELLOW);
    cout << setw(21) << EscapeColors::colorString(accuracy, EscapeColors::YELLOW);
    cout << setw(21) << EscapeColors::colorString(efficiency, EscapeColors::YELLOW);
    cout << setw(21) << EscapeColors::colorString(insight, EscapeColors::YELLOW);
    cout << setw(21) << EscapeColors::colorString(discoveryPoints, EscapeColors::YELLOW);
}

vector<Character> makeCharacters() {
    // stats for each character
    int leoStats[5]      = {5,  500,  500, 1000, 20000};
    int helixStats[5]    = {8,  900,  600, 600,  20000};
    int pantheraStats[5] = {12, 900,  700, 500,  20000};
    int adenineStats[5]  = {7,  600,  500, 900,  20000};
    int kmerStats[5]     = {18, 1000, 500, 500,  20000};

    // make vector with each character
    vector<Character> characters = {
        Character("Dr. Leo",     leoStats),
        Character("Dr. Helix",   helixStats),
        Character("Dr. Panthera",pantheraStats),
        Character("Dr. Adenine", adenineStats),
        Character("Dr. K-mer",   kmerStats)
    };

    return characters;
}

void printHeaders() {
    // print all the headers of stats to the left and space them out
    cout << left;
    cout << setw(15) << "Name";
    cout << setw(12) << "Experience";
    cout << setw(12) << "Accuracy";
    cout << setw(12) << "Efficiency";
    cout << setw(12) << "Insight";
    cout << setw(12) << "Discovery Points";
    cout << endl;
}