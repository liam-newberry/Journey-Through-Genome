#ifndef DNA_H
#define DNA_H

#include <string>

using namespace std;

class DNA {
public:
    static double strandSimilarity(string strand1, string strand2);
    static void transcribeDNAtoRNA(string strand);

private:
    static int bestStrandMatch(string input_strand, string target_strand);
    static void identifyMutations(string input_strand, string target_strand);
};

#endif