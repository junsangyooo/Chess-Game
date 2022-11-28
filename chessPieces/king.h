#ifndef _KING_H_
#define _KING_H_
#include "pieces.h"

class King : public Piece {
    char piece;
    std::string colour;
    bool firstMove = true;
public:
    King(char piece, std::string colour);
    ~King();
public:
    char getPiece() const override {return piece;}
    std::string getColour() const override{return colour;}
    bool getFirstMove() const override {return firstMove;}
    void setFirstMove(bool value) override {firstMove = value;}
};

#endif