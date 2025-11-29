// File created by: Liam Newberry & Lyle Stone

#ifndef ADVISOR_H
#define ADVISOR_H

#include <vector>

using namespace std;

struct Advisor {
    string name;
    string description;
    Advisor();
    Advisor(string n, string d);
};

vector<Advisor> makeAdvisors();

#endif