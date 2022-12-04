#include "move.h"

Move::Move(Position org_posn, Position new_posn): org_posn{org_posn}, new_posn{new_posn}, captured{nullptr} {}
Move::~Move() {
    captured = nullptr;
}

void Move::setCaptured(std::shared_ptr<Piece> piece) {
    captured = piece;
}

void Move::setPromoted(std::shared_ptr<Piece> piece) {
    promoted = piece;
}