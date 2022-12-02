#ifndef _KNIGHT_H_
#define _KNIGHT_H_
#include "pieces.h"

class Knight : public Piece {
    char piece;
public:
    Knight(char piece);
    ~Knight();
public:
    char getPiece() const override {return piece;}
};

#endif