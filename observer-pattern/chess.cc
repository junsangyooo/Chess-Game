#include "chess.h"

Chess::Chess(std::shared_ptr<Board> bd): board{bd} {}

void exception() {
    throw std::out_of_range {"Invalid Move!"};
}

std::string Chess::isCheck(std::shared_ptr<Board> bd) {

}

std::string Chess::isStaleMate() {
    
}

void Chess::enPassant(std::shared_ptr<Move> movement) {
    std::shared_ptr<Move> preMove = moves.back();
    Position org_posn = movement->getOrg();
    Position new_posn = movement->getNew();
    char piece = board->charAt(org_posn);
    bool rightPosn = false;
    if (piece == 'p') {
        if (40 > org_posn || org_posn > 47) {exception();}
        if (board->charAt(Position(new_posn - 10)) != 'P') {exception();}
    } else if (30 > org_posn || org_posn > 37) {exception();}
    else if (board->charAt(Position(new_posn + 10)) != 'p') {exception();}
    return;
}

void Chess::castling(std::shared_ptr<Move> movement) {
    Position org_posn = movement->getOrg();
    Position new_posn = movement->getNew();
    bool firstMove;
    if (!board->getFirstMove(org_posn)) {exception();}
    if (isCheck(board) != "") {exception();}
    if (new_posn + 2 == org_posn) {
        firstMove = board->getFirstMove(Position(new_posn + 1));
    } else {
        firstMove = board->getFirstMove(Position(new_posn - 2));
    }
    if (!firstMove) {exception();}
    for(int i = org_posn + 1; i <= new_posn; i++) {
        if (board->colourAt(Position(i)) != "") {exception();}
        auto new_board = std::make_shared<Board>(board);
        new_board->move(org_posn, Position(i));
        if (isCheck(new_board) != "") {exception();}
    }
    for(int i = org_posn - 1; i >= new_posn; i--) {
        if (board->colourAt(Position(i)) != "") {exception();}
        auto new_board = std::make_shared<Board>(board);
        new_board->move(org_posn, Position(i));
        if (isCheck(new_board) != "") {exception();}
    }
    if (new_posn < org_posn && board->colourAt(Position(new_posn - 1)) != "") {
        exception();
    }
    return;
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
        return;
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
    char piece = board->charAt(new_posn);
    bool firstMove = board->getFirstMove(org_posn);
    if (colour == "White") {
        if (org_posn - 11 == new_posn || new_posn == org_posn - 9) {
            return;
        } else if (org_posn - 10 == new_posn){
            if (piece != ' ' && piece != '-') {exception();}
        } else if (firstMove && new_posn == org_posn - 20) {
            if (piece != ' ' && piece != '-') {exception();}
        } else {exception();}
    } else {
        if (org_posn + 9 == new_posn || new_posn == org_posn + 11) {
            return;
        } else if (org_posn + 10 == new_posn) {
            if (piece != ' ' && piece != '-') {exception();}
        } else if (firstMove && new_posn == org_posn + 20) {
            if (piece != ' ' && piece != '-') {exception();}
        } else {exception();}
    }
    return;
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
    if (piece == 'p' || piece == 'P') {
        if (org_posn - 11 == new_posn || new_posn == org_posn - 9 || 
        org_posn + 9 == new_posn || new_posn == org_posn + 11) {
            if (board->colourAt(new_posn) == "") {
                try{enPassant(movement);} 
                catch (const std::out_of_range& e) {throw e;}
            }
        }
        Position captured;
        if (piece == 'p') {
            captured = Position(new_posn - 10);
        } else {
            captured = Position(new_posn + 10);
        }
        movement->setCaptured(board->getPiece(captured));
        board->enPassant(org_posn, new_posn);
    } else if (piece == 'k' || piece == 'K') {
        if (new_posn + 2 == org_posn || new_posn - 2 == org_posn) {
            try {castling(movement);}
            catch(const std::out_of_range& e) {throw e;}
        }
        movement->setCaptured(board->getPiece(new_posn));
        board->castling(org_posn, new_posn);
    } else {
        board->move(org_posn, new_posn);
        movement->setCaptured(board->getPiece(new_posn));
    }
    moves.emplace_back(movement);
    std::string check = isCheck(board);
    if (check == "") {
        check = isStaleMate();
    }
    notify(check);
}

char Chess::getPiece(Position posn) const {
    return board->charAt(posn);
}