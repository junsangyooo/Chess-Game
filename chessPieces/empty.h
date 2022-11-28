#ifndef _EMPTY_H_
#define _EMPTY_H_
#include "pieces.h"

class Empty : public Piece {
    char piece;
    bool firstMove = true;
public:
    Empty(char piece);
    ~Empty();
public:
    char getPiece() const override {return piece;}
    std::string getColour() const override{return "";}
    bool getFirstMove() const override {return firstMove;}
    void setFirstMove(bool value) override {firstMove = value;}
};

#endif