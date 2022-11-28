#include "controller.h"

void Controller::move(std::string org_posn, std::string new_posn) {
    chess->movePiece(org_posn, new_posn);
}
void Controller::computerMove() {}