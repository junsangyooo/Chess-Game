#ifndef _BISHOP_H_
#define _BISHOP_H_
#include "pieces.h"

class Bishop : public Piece {
    char piece;
public:
    Bishop(char piece);
    ~Bishop();
public:
    char getPiece() const override {return piece;}
};

#endif