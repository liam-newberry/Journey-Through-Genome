// File created by: Liam Newberry & Lyle Stone

#ifndef ESCAPECOLORS_H
#define ESCAPECOLORS_H

#include <string>

using namespace std;

struct EscapeColors {
private:
    static void split(string color, string items[2]);

public:
    static string colorString(string s, string color);
    static string colorString(int s, string color);
    static string colorString(string s, int color_index);
    static string colorString(int s, int color_index);

    static const string BLACK;
    static const string RED;
    static const string GREEN;
    static const string YELLOW;
    static const string BLUE;
    static const string MAGENTA;
    static const string CYAN;
    static const string WHITE;

    static const string COLORS[8];
};

#endif