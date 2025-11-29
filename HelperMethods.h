#ifndef HELPERMETHODS_H
#define HELPERMETHODS_H

#include <string>
#include <vector>

using namespace std;

class HelperMethods {
public:
    static bool isValidIntChoice(string s, int low, int high);
    static void invalidInput();
    static void clearTerminal();
    static void printHeading(string heading);
    static void clearPrintHeading(string heading);
    static int randomInt(int min, int max);
    static int randomInt(int max);
    static void sortScores(vector<vector<string>>& scores);
    static vector<vector<string>> getScores();
    static void writeScores(vector<vector<string>> scores);

private:
    static int getMaxScoreIndex(vector<vector<string>>& scores, int start);
    static bool seedRandom();

    static bool seeded_random;
};

#endif