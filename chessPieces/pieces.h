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

class Piece {
protected:
    enum Position;
public:
    virtual bool validMove(Position org_posn, Position new_posn) const = 0;
    virtual ~Piece() = 0;
};

#endif