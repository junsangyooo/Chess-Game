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
    virtual ~Piece();
public:
    virtual char getPiece() const = 0;
    virtual bool getFirstMove() const {return false;}
    virtual void setFirstMove(bool value) {}
    virtual bool getEnPassant() const {return false;}
    virtual void setEnPassant(bool value) {}
    virtual bool getPromoted() const {return false;}
    virtual void setPromoted(bool value) {}
    virtual void setWhenPromoted(int value) {}
    virtual int getWhenPromoted() {return -1;}
    virtual void setWhenFirstMove(int value) {}
    virtual int getWhenFirstMove() {return -1;}
    virtual int getValue() const {return 0;}
};

#endif