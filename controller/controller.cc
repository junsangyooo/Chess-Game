#include "controller.h"

Controller::Controller(std::shared_ptr<Chess> cs): chess{cs} {}

Controller::~Controller() {
    chess = nullptr;
}

bool Controller::move(Position org_posn, Position new_posn, bool whiteTurn) {
    auto movement = std::make_shared<Move>(org_posn, new_posn);
    bool gameEnd;
    try {gameEnd = chess->movePiece(movement, whiteTurn);}
    catch (std::out_of_range &e) {throw e;}
    return gameEnd;
}

bool Controller::check() {
    std::string check = chess->checkTest();
    if (check == "") {
        return false;
    } else {
        return true;
    }
}

void Controller::display(int posn = -1) {
    chess->drawBoard(posn);
}

void Controller::undo() {
    try{chess->undo();}
    catch(std::out_of_range &e) {
        throw e;
    }
}

bool Controller::pawnPromote(Position org_posn, Position new_posn, bool whiteTurn, char piece) {
    auto movement = std::make_shared<Move>(org_posn, new_posn);
    bool gameEnd;
    try {gameEnd = chess->movePiece(movement, whiteTurn, piece);}
    catch (std::out_of_range &e) {throw e;}
    return gameEnd;
}