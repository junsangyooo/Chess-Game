#ifndef _MOVE_H_
#define _MOVE_H_
#include "position.h"

enum Position;

class Move {
    Position org_posn, new_posn;
public:
    Move(Position org_posn, Position new_posn);
    ~Move();
public:
    Position getOrg();
    Position getNew();
};


#endif