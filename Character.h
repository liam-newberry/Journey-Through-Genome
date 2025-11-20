#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>

using namespace std;

class Character {
public:
    Character();
    Character(string characterName, int stats[5]);
    void set_stats(string characterName, int stats[5]);
    string getName() const;
    int getExperience() const;
    int getAccuracy() const;
    int getEfficiency() const;
    int getInsight() const;
    int getDiscoveryPoints() const;
    void print() const;

private:
    string name;
    int experience, accuracy, efficiency, insight, discoveryPoints;
};

vector<Character> make_characters();

void printHeaders();

#endif