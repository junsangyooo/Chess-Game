#ifndef _EMPTY_H_
#define _EMPTY_H_
#include "pieces.h"

class Empty : public Piece {
    char piece;
public:
    Empty(char piece);
    ~Empty();
public:
    bool validMove(Position org_posn, Position new_posn) const override;
    char getPiece() const override {return piece;}
    std::string getColour() const override{return "";}
};

#endif