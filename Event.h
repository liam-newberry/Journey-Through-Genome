// File created by: Liam Newberry & Lyle Stone

#ifndef EVENT_H
#define EVENT_H

#include "Advisor.h"

#include <string>
#include <vector>

using namespace std;

struct Event {
    // Public member variables
    string description;
    string path;
    vector<Advisor> advisor_vector;
    int discoveryPoints;

    void initializeData(string data);

private:
    void splitData(string sections[4], string data);
};

#endif