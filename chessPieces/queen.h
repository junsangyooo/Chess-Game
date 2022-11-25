#ifndef _QUEEN_H_
#define _QUEEN_H_
#include "pieces.h"

class Queen : public Piece {
public:
    bool validMove(Position org_posn, Position new_posn) const override;
    ~Queen();
};

#endif