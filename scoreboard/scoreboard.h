#ifndef _SCOREBOARD_H_
#define _SCOREBOARD_H_
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

class ScoreBoard {
    int white;
    int black;
    friend std::ostream &operator<<(std::ostream &out, const ScoreBoard &sb);
public:
    ScoreBoard(int white, int black);
    ~ScoreBoard();
public:
    int getWhite();
    int getBlack();
    void addToWhite(int value);
    void addToBlack(int value);
};

std::ostream& operator<<(std::ostream &out, const ScoreBoard& sb);


#endif