// File created by: Liam Newberry & Lyle Stone

#include "Advisor.h"

using namespace std;

Advisor::Advisor() {
    remaining_uses = 3;
}

Advisor::Advisor(string n, string d, double neg, double pos)
                 : name(n), description(d), negative_recovery(neg), positive_bonus(pos) {
    remaining_uses = 3;
}

vector<Advisor> makeAdvisors() {
    vector<Advisor> advisors = {
        Advisor("Dr. Aliquot", "A master of the “wet lab”, assisting in avoiding contamination", 
                0.7,  1.1),
        Advisor("Dr. Assembler", "An expert who helps improve efficiency and streamlines pipelines",
                0.75, 1.15),
        Advisor("Dr. Pop-Gen", "A genetics specialist with insight for identifying rare genetic variants",
                0.8,  1.2),
        Advisor("Dr. Bio-Script", "The genius behind the data analysis, helps debug code",
                0.6,  1.25),
        Advisor("Dr. Loci", "Your biggest supporter assisting you in learning the equipment",
                0.7,  1.15)
    };

    return advisors;
}