#ifndef _EMPTY_H_
#define _EMPTY_H_
#include "pieces.h"

class Empty : public Piece {
    char piece;
public:
    Empty(char piece);
    ~Empty();
public:
    char getPiece() const override {return piece;}
};

#endif