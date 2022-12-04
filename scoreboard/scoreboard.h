#ifndef _SCOREBOARD_H_
#define _SCOREBOARD_H_
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <utility>
#include <stdexcept>
#include <vector>
#include <memory>

class ScoreBoard {
    float white;
    float black;
    friend std::ostream &operator<<(std::ostream &out, const ScoreBoard &sb);
public:
    ScoreBoard(float white, float black);
    ~ScoreBoard();
public:
    float getWhite();
    float getBlack();
    void addToWhite(float value);
    void addToBlack(float value);
};

std::ostream& operator<<(std::ostream &out, const ScoreBoard& sb);


#endif