#ifndef _KING_H_
#define _KING_H_
#include "pieces.h"

class King : public Piece {
public:
    bool validMove(Position org_posn, Position new_posn) const override;
    ~King();
};

#endif