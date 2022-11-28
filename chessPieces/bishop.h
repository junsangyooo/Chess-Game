#ifndef _BISHOP_H_
#define _BISHOP_H_
#include "pieces.h"

class Bishop : public Piece {
    char piece;
    std::string colour;
    bool firstMove = true;
    bool isChecked = false;
public:
    Bishop(char piece, std::string colour);
    ~Bishop();
public:
    char getPiece() const override {return piece;}
    std::string getColour() const override{return colour;}
    bool getFirstMove() const override {return firstMove;}
    void setFirstMove(bool value) override {firstMove = value;}
    bool getIsChecked() const override {return isChecked;}
    void setIsChecked(bool value) override {isChecked = value;}
};

#endif