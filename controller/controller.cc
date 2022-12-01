#include "controller.h"

Controller::Controller(std::shared_ptr<Chess> cs): chess{cs} {}

bool Controller::move(std::string org_posn, std::string new_posn, bool whiteTurn) {
    auto movement = std::make_shared<Move>(org_posn, new_posn);
    bool gameEnd;
    try {gameEnd = chess->movePiece(movement, whiteTurn);}
    catch (std::out_of_range &e) {throw e;}
    return gameEnd;
}
void Controller::computerMove() {}