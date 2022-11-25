#ifndef _BOARD_H_
#define _BOARD_H_
#include <string>

class Board {
    char bd[8][8];

public:
    Board();
    ~Board();
    char charAt(std::string posn);
    void setBd();
};

#endif