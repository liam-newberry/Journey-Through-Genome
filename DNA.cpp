// File created by: Liam Newberry & Lyle Stone

#include "DNA.h"

#include <iostream>

using namespace std;

double DNA::strandSimilarity(string strand1, string strand2) {
    if (strand1.size() != strand2.size()) {
        string smaller = strand1.size() < strand2.size() ? strand1 : strand2;
        string bigger = strand1.size() > strand2.size() ? strand1 : strand2;
        strand1 = bigger;
        strand2 = smaller;

        strand1 = strand1.substr(bestStrandMatch(bigger,smaller), smaller.size());
    }

    int count = 0;
    for (int i = 0; i < strand1.size(); i++) {
        if (strand1[i] == strand2[i]) {
            count++;
        }
    }

    return (count * 1.0) / strand1.size();
}

void DNA::transcribeDNAtoRNA(string strand) {
    for (int i = 0; i < strand.size(); i++) {
        if (strand[i] == 'T') {
            strand[i] = 'U';
        }
    }

    cout << strand << endl;
}

int DNA::bestStrandMatch(string input_strand, string target_strand) {
    double best = strandSimilarity(input_strand.substr(0, target_strand.size()), target_strand);;
    int best_index = 0;

    double similarity;
    for (int i = 1; i < input_strand.size() - target_strand.size(); i++) {
        similarity = strandSimilarity(input_strand.substr(i, target_strand.size()), target_strand);
        if (similarity > best) {
            best = similarity;
            best_index = i;
        }
    }

    return best_index;
}

void DNA::identifyMutations(string input_strand, string target_strand) {

}