#ifndef _ROOK_H_
#define _ROOK_H_
#include "pieces.h"

class Rook : public Piece {
    char piece;
    bool firstMove = true;
    bool castling = false;
public:
    Rook(char piece);
    ~Rook();
public:
    char getPiece() const override {return piece;}
    bool getFirstMove() {return firstMove;}
    void setFirstMove(bool value) override {firstMove = value;}
    bool getCastling() const override {return castling;}
    void setCastling(bool value) override {castling = value;}
};

#endif