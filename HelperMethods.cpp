#include "HelperMethods.h"
#include "EscapeColors.h"

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

// check if an input is number between low and high
bool HelperMethods::isValidIntChoice(string s, int low, int high) {
    try {
        int x = stoi(s); // convert the string to int
        return x >= low && x <= high; // return input is in range of options
    } catch (const invalid_argument) { // if non number input to stoi
        return false;
    }
}

//
void HelperMethods::invalidInput() { 
    cout << endl
         << EscapeColors::colorString("Invalid input", EscapeColors::RED) 
         << endl << endl; // This makes the error code red
}

// clear the terminal; unix - "clear", windows - "cls"
void HelperMethods::clearTerminal() {
    user_os == "unix" ? system("clear") : system("cls");
}

// displays a decorated heading
void HelperMethods::printHeading(string heading) {
    const int LENGTH = 120;

    string decoration = string(LENGTH, '='); // makes a new string with '=' char 30 times
    decoration = EscapeColors::colorString(decoration, EscapeColors::CYAN);

    int leftPaddingSize = int((LENGTH - heading.size()) / 2);
    string leftPadding = string(leftPaddingSize, ' ');

    cout << endl << decoration << endl << leftPadding
         << EscapeColors::colorString(heading, EscapeColors::MAGENTA)
         << endl << decoration << endl << endl;
}

// displays a heading and clears screen
void HelperMethods::clearPrintHeading(string heading) {
    clearTerminal();
    printHeading(heading);
}

// returns random int [min,max]
int HelperMethods::randomInt(int min, int max) {
    return min + rand() % (max - min + 1);
}

// returns random int [0,max]
int HelperMethods::randomInt(int max) {
    return randomInt(0, max);
}

// sorts a 2D vector of scores
void HelperMethods::sortScores(vector<vector<string>>& scores) {
    if (scores.size() <= 1) {
        return;
    }
 
    int highest;
    vector<string> temp(2);

    for (int i = 0; i < scores.size() - 1; i++) {
        highest = getMaxScoreIndex(scores, i);
        temp = scores[i];
        scores[i] = scores[highest];
        scores[highest] = temp;
    }
}

vector<vector<string>> HelperMethods::getScores() {
    vector<vector<string>> scores;
    ifstream input("scores.txt");
    if (!input) {
        return scores;
    }

    string name, score;
    vector<string> pair(2);

    while (input >> name >> score) {
        pair[0] = name;
        pair[1] = score;
        scores.push_back(pair);
    }

    return scores;
}

void HelperMethods::writeScores(vector<vector<string>> scores) {
    ofstream output("scores.txt");

    for (int i = 0; i < scores.size(); i++) {
        output << scores[i][0] << " " << scores[i][1] << endl;
    }
}

// finds the max index of a subsection of scores; helper for sorting
int HelperMethods::getMaxScoreIndex(vector<vector<string>>& scores, int start) {
    int highest_ind = start;

    for (int i = start + 1; i < scores.size(); i++) {
        if (stoi(scores[i][1]) > stoi(scores[highest_ind][1])) {
            highest_ind = i;
        }
    }

    return highest_ind;
}

string HelperMethods::getOS() {
    string os;

    #ifdef _WIN32 
        os = "windows";
    #else
        os = "unix";
    #endif

    return os;
}

// basically a constructor for seeded_random to seed random
bool HelperMethods::seedRandom() {
    srand(time(0));
    return true;
}

string HelperMethods::user_os = getOS(); // gets user OS for clear command
bool HelperMethods::seeded_random = seedRandom(); // seeds random automatically