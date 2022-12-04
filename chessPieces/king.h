#ifndef _KING_H_
#define _KING_H_
#include "pieces.h"

class King : public Piece {
    char piece;
    bool firstMove = true;
    int whenFirstMove = -1;
public:
    King(char piece);
    ~King();
public:
    char getPiece() const override {return piece;}
    bool getFirstMove() const override {return firstMove;}
    void setFirstMove(bool value) override {firstMove = value;}
    void setWhenFirstMove(int value) override {whenFirstMove = value;}
    int getWhenFirstMove() {return whenFirstMove;}
};

#endif