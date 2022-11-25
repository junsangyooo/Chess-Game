#include "pawn.h"

Pawn::Pawn(bool isMoved, std::string colour): firstMove{!isMoved}, colour{colour} {}

bool Pawn::validMove(Position org_posn, Position new_posn) const {
    if (org_posn == new_posn) return false;
    if (colour == "white") {
        if (org_posn - 11 <= new_posn && new_posn <= org_posn - 9){
            return true;
        } else if (firstMove && new_posn == org_posn - 20){
            return true;
        } else {
            return false;
        }
    } else {
        if (org_posn + 9 <= new_posn && new_posn <= org_posn + 11) {
            return true;
        } else if (firstMove && new_posn == org_posn + 20) {
            return true;
        } else {return false;}
    }
}
Pawn::~Pawn() {}