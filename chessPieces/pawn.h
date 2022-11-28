#ifndef _PAWN_H_
#define _PAWN_H_
#include "pieces.h"

class Pawn : public Piece {
    char piece;
    std::string colour;
public:
    Pawn(char piece, std::string colour);
    ~Pawn();
public:
    bool validMove(Position org_posn, Position new_posn) const override;
    char getPiece() const override {return piece;}
    std::string getColour() const override{return colour;}
};

#endif