#include "pawn.h"

Pawn::Pawn(char piece, std::string colour): piece{piece}, colour{colour} {}

bool Pawn::validMove(Position org_posn, Position new_posn) const {
    if (org_posn == new_posn) return false;
    bool firstMove = false;
    if (colour == "White") {
        if (60 <= org_posn && org_posn <= 67) {
            firstMove = true;
        }
        if (org_posn - 11 <= new_posn && new_posn <= org_posn - 9){
            return true;
        } else if (firstMove && new_posn == org_posn - 20){
            return true;
        } else {
            return false;
        }
    } else {
        if (10 <= org_posn && org_posn <= 17) {
            firstMove = true;
        }
        if (org_posn + 9 <= new_posn && new_posn <= org_posn + 11) {
            return true;
        } else if (firstMove && new_posn == org_posn + 20) {
            return true;
        } else {return false;}
    }
}
Pawn::~Pawn() {}