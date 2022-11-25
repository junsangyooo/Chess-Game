#ifndef _PAWN_H_
#define _PAWN_H_
#include "pieces.h"

class Pawn : public Piece {
    bool firstMove;
    std::string colour;
public:
    Pawn(bool isMoved, std::string colour);
    bool validMove(Position org_posn, Position new_posn) const override;
    ~Pawn();
};

#endif