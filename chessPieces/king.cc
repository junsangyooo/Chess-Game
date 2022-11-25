#include "king.h"

bool King::validMove(Position org_posn, Position new_posn) const {
    if (org_posn == new_posn) return false;
    if (new_posn + 1 == org_posn || new_posn - 1 == org_posn) {
        return true;
    } else if (org_posn - 11 <= new_posn && new_posn <= org_posn - 9) {
        return true;
    } else if (org_posn + 9 <= new_posn && new_posn <= org_posn + 11) {
        return true;
    } else {
        return false;
    }
}
King::~King() {}