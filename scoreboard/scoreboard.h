#ifndef _SCOREBOARD_H_
#define _SCOREBOARD_H_
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

class ScoreBoard {
    float white;
    float black;
    friend std::ostream &operator<<(std::ostream &out, const ScoreBoard &sb);
public:
    ScoreBoard(float white, float black);
    ~ScoreBoard();
public:
    int getWhite();
    int getBlack();
    void addToWhite(float value);
    void addToBlack(float value);
};

std::ostream& operator<<(std::ostream &out, const ScoreBoard& sb);


#endif