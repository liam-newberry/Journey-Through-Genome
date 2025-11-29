// File created by: Liam Newberry & Lyle Stone

#include "Advisor.h"

using namespace std;

Advisor::Advisor() {}

Advisor::Advisor(string n, string d) : name(n), description(d) {}

vector<Advisor> makeAdvisors() {
    vector<Advisor> advisors = {
        Advisor("Dr. Aliquot", "A master of the “wet lab”, assisting in avoiding contamination"),
        Advisor("Dr. Assembler", "An expert who helps improve efficiency and streamlines pipelines"),
        Advisor("Dr. Pop-Gen", "A genetics specialist with insight for identifying rare genetic variants"),
        Advisor("Dr. Bio-Script", "The genius behind the data analysis, helps debug code"),
        Advisor("Dr. Loci", "Your biggest supporter assisting you in learning the equipment")
    };

    return advisors;
}