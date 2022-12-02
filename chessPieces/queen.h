#ifndef _QUEEN_H_
#define _QUEEN_H_
#include "pieces.h"

class Queen : public Piece {
    char piece;
public:
    Queen(char piece);
    ~Queen();
public:
    char getPiece() const override {return piece;}
};

#endif