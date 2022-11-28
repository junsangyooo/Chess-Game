#ifndef _KING_H_
#define _KING_H_
#include "pieces.h"

class King : public Piece {
    char piece;
    std::string colour;
public:
    King(char piece, std::string colour);
    ~King();
public:
    bool validMove(Position org_posn, Position new_posn) const override;
    char getPiece() const override {return piece;}
    std::string getColour() const override{return colour;}
};

#endif