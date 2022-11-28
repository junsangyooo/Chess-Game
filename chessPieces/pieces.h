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
#include "position.h"

enum Position;

class Piece {
public:
    virtual ~Piece() = 0;
public:
    virtual bool validMove(Position org_posn, Position new_posn) const = 0;
    virtual char getPiece() const = 0;
    virtual std::string getColour() const = 0;
};

#endif