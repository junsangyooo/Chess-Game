#ifndef _EMPTY_H_
#define _EMPTY_H_
#include "pieces.h"

class Empty : public Piece {
    char piece;
    bool firstMove = true;
    bool isChecked = false;
public:
    Empty(char piece);
    ~Empty();
public:
    char getPiece() const override {return piece;}
    std::string getColour() const override{return "";}
    bool getFirstMove() const override {return firstMove;}
    void setFirstMove(bool value) override {firstMove = value;}
    bool getIsChecked() const override {return isChecked;}
    void setIsChecked(bool value) override {isChecked = value;}
};

#endif