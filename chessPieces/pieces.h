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
    virtual char getPiece() const = 0;
    virtual bool getFirstMove() const {}
    virtual void setFirstMove(bool value) {}
    virtual bool getIsChecked() const{} 
    virtual void setIsChecked(bool value) {}
    virtual bool getEnPassant() const {}
    virtual void setEnPassant(bool value) {}
    virtual bool getCastling() const {}
    virtual void setCastling(bool value) {}
};

#endif