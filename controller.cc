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
    std::string check = chess->whiteInCheck();
    if (check == "") {
        check = chess->blackInCheck();
    }
    if (check == "") {
        return false;
    } else {
        return true;
    }
}

void Controller::display(int posn) {
    chess->drawBoard("", posn);
}

void Controller::undo() {
    try{chess->undo(true);}
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

void Controller::resign(bool whiteTurn) {
    chess = nullptr;
}

bool Controller::computerMove(bool whiteTurn) {
    if (whiteTurn) {
        return computerWhite->makeMove();
    }
    else {
        return computerBlack->makeMove();
    }
}
