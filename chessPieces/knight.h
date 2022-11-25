#ifndef _KNIGHT_H_
#define _KNIGHT_H_
#include "pieces.h"

class Knight : public Piece {
public:
    bool validMove(Position org_posn, Position new_posn) const override;
    ~Knight();
};

#endif