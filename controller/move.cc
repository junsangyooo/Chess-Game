#include "move.h"

Move::Move(Position org_posn, Position new_posn): org_posn{org_posn}, new_posn{new_posn} {}
Move::~Move() {}

Position Move::getOrg() {return org_posn;}
Position Move::getNew() {return new_posn;}