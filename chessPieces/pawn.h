#ifndef _PAWN_H_
#define _PAWN_H_
#include "pieces.h"

class Pawn : public Piece {
    char piece;
    bool en_passant = false;
    const int value = 1;
public:
    Pawn(char piece);
    ~Pawn();
public:
    char getPiece() const override {return piece;}
    bool getEnPassant() const override {return en_passant;}
    void setEnPassant(bool value) override {en_passant = value;}
    int getValue() const override {return value;}
};

#endif