#ifndef _ROOK_H_
#define _ROOK_H_
#include "pieces.h"

class Rook : public Piece {
    char piece;
    std::string colour;
    bool firstMove = true;
public:
    Rook(char piece, std::string colour);
    ~Rook();
public:
    char getPiece() const override {return piece;}
    std::string getColour() const override{return colour;}
    bool getFirstMove() {return firstMove;}
    void setFirstMove(bool value) override {firstMove = value;}
};

#endif