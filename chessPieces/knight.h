#ifndef _KNIGHT_H_
#define _KNIGHT_H_
#include "pieces.h"

class Knight : public Piece {
    char piece;
    std::string colour;
    bool firstMove = true;
public:
    Knight(char piece, std::string colour);
    ~Knight();
public:
    char getPiece() const override {return piece;}
    std::string getColour() const override{return colour;}
    bool getFirstMove() const override {return firstMove;}
    void setFirstMove(bool value) override {firstMove = value;}
};

#endif