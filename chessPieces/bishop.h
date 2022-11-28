#ifndef _BISHOP_H_
#define _BISHOP_H_
#include "pieces.h"

class Bishop : public Piece {
    char piece;
    std::string colour;
    bool firstMove = true;
public:
    Bishop(char piece, std::string colour);
    ~Bishop();
public:
    char getPiece() const override {return piece;}
    std::string getColour() const override{return colour;}
    bool getFirstMove() const override {return firstMove;}
    void setFirstMove(bool value) override {firstMove = value;}
};

#endif