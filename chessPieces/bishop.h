#ifndef _BISHOP_H_
#define _BISHOP_H_
#include "pieces.h"

class Bishop : public Piece {
    char piece;
    std::string colour;
public:
    Bishop(char piece, std::string colour);
    ~Bishop();
public:
    bool validMove(Position org_posn, Position new_posn) const override;
    char getPiece() const override {return piece;}
    std::string getColour() const override{return colour;}
};

#endif