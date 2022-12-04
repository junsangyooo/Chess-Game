#ifndef _PAWN_H_
#define _PAWN_H_
#include "pieces.h"

class Pawn : public Piece {
    char piece;
    bool firstMove = true;
    bool en_passant = false;
    int whenFirstMove = -1;
public:
    Pawn(char piece);
    ~Pawn();
public:
    char getPiece() const override {return piece;}
    bool getFirstMove() const override {return firstMove;}
    void setFirstMove(bool value) override {firstMove = value;}
    bool getEnPassant() const override {return en_passant;}
    void setEnPassant(bool value) override {en_passant = value;}
    void setWhenFirstMove(int value) override {whenFirstMove = value;}
    int getWhenFirstMove() {return whenFirstMove;}
};

#endif