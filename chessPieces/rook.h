#ifndef _ROOK_H_
#define _ROOK_H_
#include "pieces.h"

class Rook : public Piece {
    char piece;
    std::string colour;
public:
    Rook(char piece, std::string colour);
    ~Rook();
public:
    bool validMove(Position org_posn, Position new_posn) const override;
    char getPiece() const override {return piece;}
    std::string getColour() const override{return colour;}
};

#endif