#ifndef _ROOK_H_
#define _ROOK_H_
#include "pieces.h"

class Rook : public Piece {
public:
    bool validMove(Position org_posn, Position new_posn) const override;
    ~Rook();
};

#endif