#include "rook.h"

bool Rook::validMove(Position org_posn, Position new_posn) const {
    if (org_posn == new_posn) return false;
    int diff = abs(org_posn - new_posn);
    int org_row = org_posn / 10;
    org_row *= 10;
    if (diff % 10 == 0) {
        return true;
    } else if (org_row <= new_posn && new_posn <= org_row + 7) {
        return true;
    } else {
        return false;
    }
}
Rook::~Rook() {}