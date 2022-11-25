#include "knight.h"

bool Knight::validMove(Position org_posn, Position new_posn) const {
    if (org_posn == new_posn) return false;
    if (new_posn == org_posn - 21 || new_posn == org_posn - 19) {
        return true;
    } else if (new_posn == org_posn - 12 || new_posn == org_posn - 8) {
        return true;
    } else if (new_posn == org_posn + 8 || new_posn == org_posn + 12) {
        return true;
    } else if (new_posn == org_posn + 19 || new_posn == org_posn + 21) {
        return true;
    } else {
        return false;
    }
}
Knight::~Knight() {}