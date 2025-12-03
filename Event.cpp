// File created by: Liam Newberry & Lyle Stone

#include "Event.h"

// initializes Event data from a string
void Event::initializeData(string data) {
    string sections[4];
    splitData(sections, data);

    description = sections[0];

    path = "0" == sections[1] ? "Training Fellowship" : "Direct Lab Assignment";
    
    vector<Advisor> advisors = makeAdvisors();
    if (sections[2] != "0") {
        for (int i = 0; i < sections[2].size(); i++) {
            advisor_vector.push_back(advisors[stoi(sections[2].substr(i,1)) - 1]);
        }
    }

    discoveryPoints = stoi(sections[3]);
}

// splits the data string into its component sections
void Event::splitData(string sections[4], string data) {
    int last = -1;
    int count = 0;
    int i = 0;

    while (count < 3) {
        if (data[i] == '|') {
            sections[count] = data.substr(last + 1, i - last - 1);
            last = i;
            count++;
        }
        i++;
    }

    sections[3] = data.substr(i);
}