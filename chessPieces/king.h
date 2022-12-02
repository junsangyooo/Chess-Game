#ifndef _KING_H_
#define _KING_H_
#include "pieces.h"

class King : public Piece {
    char piece;
    bool firstMove = true;
    bool isChecked = false;
    bool castling = false;
public:
    King(char piece);
    ~King();
public:
    char getPiece() const override {return piece;}
    bool getFirstMove() const override {return firstMove;}
    void setFirstMove(bool value) override {firstMove = value;}
    bool getIsChecked() const override {return isChecked;}
    void setIsChecked(bool value) override {isChecked = value;}
    bool getCastling() const override {return castling;}
    void setCastling(bool value) override {castling = value;}
};

#endif