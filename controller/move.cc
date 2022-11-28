#include "move.h"

Move::Move(Position org_posn, Position new_posn): org_posn{org_posn}, new_posn{new_posn}, captured{nullptr} {}
Move::~Move() {}

Position Move::getOrg() {return org_posn;}
Position Move::getNew() {return new_posn;}

void Move::setCaptured(std::shared_ptr<Piece> piece) {
    captured = piece;
}