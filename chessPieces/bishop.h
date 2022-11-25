#ifndef _BISHOP_H_
#define _BISHOP_H_
#include "pieces.h"

class Bishop : public Piece {
public:
    bool validMove(Position org_posn, Position new_posn) const override;
    ~Bishop();
};

#endif