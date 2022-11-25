#include "queen.h"

bool Queen::validMove(Position org_posn, Position new_posn) const {
    if (org_posn == new_posn) return false;
    int diff = abs(org_posn - new_posn);
    int org_row = org_posn / 10;
    if (diff % 9 == 0 || diff % 11 == 0){
        return true;
    } else if (diff % 10 == 0) {
        return true;
    } else if (org_row * 10 <= new_posn && new_posn <= org_row* 10 + 7) {
        return true;
    } else {
        return false;
    }
}
Queen::~Queen() {}