#include "bishop.h"

bool Bishop::validMove(Position org_posn, Position new_posn) const {
    if (org_posn == new_posn) return false;
    int diff = abs(org_posn - new_posn);
    if (diff % 9 == 0 || diff % 11 == 0) return true;
    return false;
}
Bishop::~Bishop() {}