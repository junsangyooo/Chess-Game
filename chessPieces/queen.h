#ifndef _QUEEN_H_
#define _QUEEN_H_
#include "pieces.h"

class Queen : public Piece {
    char piece;
    std::string colour;
public:
    Queen(char piece, std::string colour);
    ~Queen();
public:
    bool validMove(Position org_posn, Position new_posn) const override;
    char getPiece() const override {return piece;}
    std::string getColour() const override{return colour;}
};

#endif