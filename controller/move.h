#ifndef _MOVE_H_
#define _MOVE_H_
#include "position.h"
#include "pieces.h"

enum Position;

class Move {
    Position org_posn, new_posn;
    std::shared_ptr<Piece> captured;
public:
    Move(Position org_posn, Position new_posn);
    ~Move();
public:
    Position getOrg();
    Position getNew();
    void setCaptured(std::shared_ptr<Piece> piece);
};


#endif