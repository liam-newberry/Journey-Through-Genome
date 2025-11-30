// File created by: Liam Newberry & Lyle Stone

#ifndef ADVISOR_H
#define ADVISOR_H

#include <vector>

using namespace std;

struct Advisor {
    string name;
    string description;
    double negative_recovery;
    double positive_bonus;
    int remaining_uses;
    Advisor();
    Advisor(string n, string d, double neg, double pos);
};

vector<Advisor> makeAdvisors();

#endif