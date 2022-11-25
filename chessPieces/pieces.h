#ifndef _PIECES_H_
#define _PIECES_H_
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <utility>
#include <stdexcept>
#include <vector>

class Piece {
public:
    virtual bool validMove() const = 0;
    virtual ~Piece();
};

#endif