#include "controller.h"

Controller::Controller(std::shared_ptr<Chess> cs): chess{cs} {}

void Controller::move(std::string org_posn, std::string new_posn) {
    auto movement = std::make_shared<Move>(org_posn, new_posn);
    chess->movePiece(movement);
}
void Controller::computerMove() {}