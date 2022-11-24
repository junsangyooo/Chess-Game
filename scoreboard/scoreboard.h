#ifndef _SCOREBOARD_H_
#define _SCOREBOARD_H_
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

class ScoreBoard {
    int white;
    int blank;

public:
    ScoreBoard(int white, int black);
    ~ScoreBoard();
    std::ostream &operator<<(std::ostream & out);
};


#endif