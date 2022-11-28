#include "chess.h"

Chess::Chess(std::shared_ptr<Board> bd): board{bd} {}

void exception() {
    throw std::out_of_range {"Invalid Move!"};
}

void Chess::castling(std::shared_ptr<Move> movement) {

}

void Chess::validBishop(std::shared_ptr<Move> movement) {
    Position org_posn = movement->getOrg();
    Position new_posn = movement->getNew();
    int diff = abs(org_posn - new_posn);
    int posn = org_posn;
    int tmp;
    if (diff% 9 == 0) {tmp = 9;}
    else if (diff % 11 == 0) {tmp = 11;}
    else {exception();}

    for (int i = org_posn - tmp; i > new_posn; i -= tmp) {
        char piece = board->charAt(Position(i));
        if (piece != ' ' && piece != '-') {exception();}
    }
    for (int i = org_posn + tmp; i < new_posn; i += tmp) {
        char piece = board->charAt(Position(i));
        if (piece != ' ' && piece != '-') {exception();}
    }
    return;
}
void Chess::validKing(std::shared_ptr<Move> movement) {
    Position org_posn = movement->getOrg();
    Position new_posn = movement->getNew();
    if (new_posn + 1 == org_posn || new_posn - 1 == org_posn) {
        return;
    } else if (org_posn - 11 <= new_posn && new_posn <= org_posn - 9) {
        return;
    } else if (org_posn + 9 <= new_posn && new_posn <= org_posn + 11) {
        return;
    } else if (new_posn + 2 == org_posn || new_posn - 2 == org_posn) {
        try {castling(movement);}
        catch(const std::out_of_range& e) {throw e;}
    } else {exception();}
    return;
}
void Chess::validQueen(std::shared_ptr<Move> movement) {
    Position org_posn = movement->getOrg();
    Position new_posn = movement->getNew();
    int diff = abs(org_posn - new_posn);
    int org_row = org_posn / 10;
    org_row *= 10;
    int tmp;
    if (diff% 9 == 0) {tmp = 9;}
    else if (diff % 10 == 0) {tmp = 10;}
    else if (diff % 11 == 0) {tmp = 11;}
    else if (org_row <= new_posn && new_posn <= org_row+ 7) {tmp = 1;}
    else {exception();}

    for (int i = org_posn - tmp; i > new_posn; i -= tmp) {
        char piece = board->charAt(Position(i));
        if (piece != ' ' && piece != '-') {exception();}
    }
    for (int i = org_posn + tmp; i < new_posn; i += tmp) {
        char piece = board->charAt(Position(i));
        if (piece != ' ' && piece != '-') {exception();}
    }
    return;
}
void Chess::validRook(std::shared_ptr<Move> movement) {
    Position org_posn = movement->getOrg();
    Position new_posn = movement->getNew();
    int diff = abs(org_posn - new_posn);
    int org_row = org_posn / 10;
    org_row *= 10;
    int tmp;
    if (diff % 10 == 0) {tmp = 10;}
    else if (org_row <= new_posn && new_posn <= org_row+ 7) {tmp = 1;}
    else {exception();}
    for (int i = org_posn - tmp; i > new_posn; i -= tmp) {
        char piece = board->charAt(Position(i));
        if (piece != ' ' && piece != '-') {exception();}
    }
    for (int i = org_posn + tmp; i < new_posn; i += tmp) {
        char piece = board->charAt(Position(i));
        if (piece != ' ' && piece != '-') {exception();}
    }
    return;
}
void Chess::validKnight(std::shared_ptr<Move> movement) {
    Position org_posn = movement->getOrg();
    Position new_posn = movement->getNew();
    if (new_posn == org_posn - 21 || new_posn == org_posn - 19) {
        return;
    } else if (new_posn == org_posn - 12 || new_posn == org_posn - 8) {
        return;
    } else if (new_posn == org_posn + 8 || new_posn == org_posn + 12) {
        return;
    } else if (new_posn == org_posn + 19 || new_posn == org_posn + 21) {
        return;
    } else {
        exception();
    }
    return;
}
void Chess::validPawn(std::shared_ptr<Move> movement) {
    Position org_posn = movement->getOrg();
    Position new_posn = movement->getNew();
    std::string colour = board->colourAt(org_posn);
    
}

void Chess::validMove(std::shared_ptr<Move> movement) {
    Position org_posn = movement->getOrg();
    Position new_posn = movement->getNew();
    if (org_posn == new_posn) {
        throw std::out_of_range {"Move a piece!!"};
    }
    std::string colour = board->colourAt(org_posn);
    std::string colour_new = board->colourAt(new_posn);
    if (whiteTurn) {
        if (colour == "Black") {
            throw std::out_of_range {"Move a white piece!"};
        }
        if (colour_new == "White") {exception();}
    } else {
        if (colour == "White") {
            throw std::out_of_range {"Move a black piece!"};
        }
        if (colour_new == "Black") {exception();}
    }
    char piece = board->charAt(org_posn);
    if (piece == ' ' || piece == '-') {exception();}
    else if (piece == 'k' || piece == 'K') {validKing(movement);}
    else if (piece == 'q' || piece == 'Q') {validQueen(movement);}
    else if (piece == 'b' || piece == 'B') {validBishop(movement);}
    else if (piece == 'n' || piece == 'N') {validKnight(movement);}
    else if (piece == 'r' || piece == 'R') {validRook(movement);}
    else {validPawn(movement);}
    return;
}

void Chess::movePiece(std::shared_ptr<Move> movement) {
    Position org_posn = movement->getOrg();
    Position new_posn = movement->getNew();
    try {
        validMove(movement);
    }
    catch(const std::out_of_range& e) {throw e;}
    char piece = board->charAt(org_posn);
}

char Chess::getPiece(Position posn) const {
    return board->charAt(posn);
}