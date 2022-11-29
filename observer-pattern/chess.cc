#include "chess.h"

Chess::Chess(std::shared_ptr<Board> bd, std::shared_ptr<ScoreBoard> sb): board{bd}, score{sb} {}

void exception() {
    throw std::out_of_range {"Invalid Move!"};
}

std::string Chess::isStaleMate() {

}


bool Chess::validBishop(std::shared_ptr<Move> movement) {
    Position org_posn = movement->getOrg();
    Position new_posn = movement->getNew();
    int diff = abs(org_posn - new_posn);
    int posn = org_posn;
    int tmp;
    if (diff% 9 == 0) {tmp = 9;}
    else if (diff % 11 == 0) {tmp = 11;}
    else {return false;}

    for (int i = org_posn - tmp; i > new_posn; i -= tmp) {
        char piece = board->charAt(Position(i));
        if (piece != ' ' && piece != '-') {return false;}
    }
    for (int i = org_posn + tmp; i < new_posn; i += tmp) {
        char piece = board->charAt(Position(i));
        if (piece != ' ' && piece != '-') {return false;}
    }

    return true;
}
bool Chess::validKing(std::shared_ptr<Move> movement) {
    Position org_posn = movement->getOrg();
    Position new_posn = movement->getNew();
    if (new_posn + 1 == org_posn || new_posn - 1 == org_posn) {
        return true;
    } else if (org_posn - 11 <= new_posn && new_posn <= org_posn - 9) {
        return true;
    } else if (org_posn + 9 <= new_posn && new_posn <= org_posn + 11) {
        return true;
    } else {return false;}
}
bool Chess::validQueen(std::shared_ptr<Move> movement) {
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
    else {return false;}

    for (int i = org_posn - tmp; i > new_posn; i -= tmp) {
        char piece = board->charAt(Position(i));
        if (piece != ' ' && piece != '-') {return false;}
    }
    for (int i = org_posn + tmp; i < new_posn; i += tmp) {
        char piece = board->charAt(Position(i));
        if (piece != ' ' && piece != '-') {return false;}
    }
    return true;
}
bool Chess::validRook(std::shared_ptr<Move> movement) {
    Position org_posn = movement->getOrg();
    Position new_posn = movement->getNew();
    int diff = abs(org_posn - new_posn);
    int org_row = org_posn / 10;
    org_row *= 10;
    int tmp;
    if (diff % 10 == 0) {tmp = 10;}
    else if (org_row <= new_posn && new_posn <= org_row+ 7) {tmp = 1;}
    else {return false;}
    for (int i = org_posn - tmp; i > new_posn; i -= tmp) {
        char piece = board->charAt(Position(i));
        if (piece != ' ' && piece != '-') {return false;}
    }
    for (int i = org_posn + tmp; i < new_posn; i += tmp) {
        char piece = board->charAt(Position(i));
        if (piece != ' ' && piece != '-') {return false;}
    }
    return true;
}
bool Chess::validKnight(std::shared_ptr<Move> movement) {
    Position org_posn = movement->getOrg();
    Position new_posn = movement->getNew();
    if (new_posn == org_posn - 21 || new_posn == org_posn - 19) {
        return true;
    } else if (new_posn == org_posn - 12 || new_posn == org_posn - 8) {
        return true;
    } else if (new_posn == org_posn + 8 || new_posn == org_posn + 12) {
        return true;
    } else if (new_posn == org_posn + 19 || new_posn == org_posn + 21) {
        return true;
    } else {
        return false;
    }
}
bool Chess::validPawn(std::shared_ptr<Move> movement) {
    Position org_posn = movement->getOrg();
    Position new_posn = movement->getNew();
    std::string colour = board->colourAt(org_posn);
    char piece = board->charAt(new_posn);
    bool firstMove = board->getFirstMove(org_posn);
    if (colour == "White") {
        if (org_posn - 11 == new_posn || new_posn == org_posn - 9) {
            return;
        } else if (org_posn - 10 == new_posn){
            if (piece != ' ' && piece != '-') {return false;}
        } else if (firstMove && new_posn == org_posn - 20) {
            if (piece != ' ' && piece != '-') {return false;}
        } else {return false;}
    } else {
        if (org_posn + 9 == new_posn || new_posn == org_posn + 11) {
            return;
        } else if (org_posn + 10 == new_posn) {
            if (piece != ' ' && piece != '-') {return false;}
        } else if (firstMove && new_posn == org_posn + 20) {
            if (piece != ' ' && piece != '-') {return false;}
        } else {return false;}
    }
    return true;
}

std::string Chess::isCheck() {
    Position whiteKing = board->getWhiteKing();
    Position blackKing = board->getBlackKing();
    bool whiteInCheck = false;
    bool blackInCheck = false;
    //Now check whether the King is under check
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Position posn = Position(i*10 + j);
            char piece = board->charAt(posn);
            if (piece ==' ' || piece == '-'){continue;}
            auto tmp_move_white = std::make_shared<Move>(posn, whiteKing);
            auto tmp_move_black = std::make_shared<Move>(posn, blackKing);
            if (piece == 'k') {
                if (validKing(tmp_move_white)) {whiteInCheck = true;}
            } else if (piece == 'b') {
                if (validBishop(tmp_move_white)) {whiteInCheck = true;}
            } else if (piece == 'q') {
                if (validQueen(tmp_move_white)) {whiteInCheck = true;}
            } else if (piece == 'r') {
                if (validRook(tmp_move_white)) {whiteInCheck = true;}
            } else if (piece == 'n') {
                if (validKnight(tmp_move_white)) {whiteInCheck = true;}
            } else if (piece == 'p') {
                if (validPawn(tmp_move_white)) {whiteInCheck = true;}
            } else if (piece == 'K') {
                if (validKing(tmp_move_black)) {blackInCheck = true;}
            } else if (piece == 'B') {
                if (validBishop(tmp_move_black)) {blackInCheck = true;}
            } else if (piece == 'Q') {
                if (validQueen(tmp_move_black)) {blackInCheck = true;}
            } else if (piece == 'R') {
                if (validRook(tmp_move_black)) {blackInCheck = true;}
            } else if (piece == 'N') {
                if (validKnight(tmp_move_black)) {blackInCheck = true;}
            } else if (piece == 'P') {
                if (validPawn(tmp_move_black)) {blackInCheck = true;}
            }
        }
    }
    if (whiteTurn && whiteInCheck) {return "White is in check.";}
    else if (!whiteTurn && blackInCheck) {return "Black is in check.";}
    else if (whiteInCheck) {    //Check a checkmate for white King
        board->setIsChecked(whiteKing, true);
    } else if (blackInCheck) {  //Check a checkmate for black King
        board->setIsChecked(blackKing, true);
    }
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

//Controller calls movePiece function with the movement of next turn.
bool Chess::movePiece(std::shared_ptr<Move> movement) {
    Position org_posn = movement->getOrg();
    Position new_posn = movement->getNew();

     // Check whether the move does not change anything.
    if (org_posn == new_posn) {
        throw std::out_of_range {"Move a piece!!"};
    }

    // Check whether the piece would be captured has the same colour of the moving piece.
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

    // Check valid movement based on each moving piece type.
    char piece = board->charAt(org_posn);
    bool specialCase = false;
    // If the moving piece is Empty, throw an exception.
    if (piece == ' ' || piece == '-') {exception();}
    else if (piece == 'k' || piece == 'K') {    //Check King move
        if (!validKing(movement)) {
            if (new_posn + 2 == org_posn || new_posn - 2 == org_posn) {
                try {castling(movement);}
                catch(const std::out_of_range& e) {throw e;}
                specialCase = true;
                movement->setCaptured(board->getPiece(new_posn));   // If castling is valid
                board->castling(org_posn, new_posn);
            } else {
                exception();
            }
        }
    }
    else if (piece == 'q' || piece == 'Q') {    //Check Queen move
        if (!validQueen(movement)) {exception();}
    }
    else if (piece == 'b' || piece == 'B') {    //Check Bishop move
        if (!validBishop(movement)) {exception();}
    }
    else if (piece == 'n' || piece == 'N') {    //Check Knight move
        if (!validKnight(movement)) {exception();}
    }
    else if (piece == 'r' || piece == 'R') {    //Check Rook move
        if (!validRook(movement)) {exception();}    
    }
    else if (!validPawn(movement)) { //Check Pawn move
        if (org_posn - 11 == new_posn || new_posn == org_posn - 9 || org_posn + 9 == new_posn || new_posn == org_posn + 11) {
            if (board->colourAt(new_posn) == "") { //Check whether there is no piece on new_posn.
                try{enPassant(movement);}   // Check whether the enPassant is valid.
                catch (const std::out_of_range& e) {throw e;}
                specialCase = true;
                Position captured;
                if (piece == 'p') {
                    captured = Position(new_posn - 10);
                } else {
                    captured = Position(new_posn + 10);
                }
                movement->setCaptured(board->getPiece(captured));
                board->enPassant(org_posn, new_posn);
            }
        }
    }

    if (piece == 'k') {
        board->setBlackKing(new_posn);  // Change the position of King piece
    } else if (piece == 'K') {
        board->setWhiteKing(new_posn);  // Change the position of King piece
    }

    //If the movement is not En Passant or Castling, move in general
    if (!specialCase) { 
        movement->setCaptured(board->getPiece(new_posn)); // Store captured piece into the movement
        board->move(org_posn, new_posn);    // Change the board
    }

    //Now, we check whether the movement put the king under check
    //If so, undo
    std::string status = isCheck();
    if (whiteTurn) {
        if (status == "White is in check.") {
            if (piece == 'k') {
                board->setBlackKing(org_posn);  // Change the position of King piece
            } else if (piece == 'K') {
                board->setWhiteKing(org_posn);  // Change the position of King piece
            }
            board->move(new_posn, org_posn);
            board->setPiece(new_posn, movement->getCaptured());
            movement->setCaptured(nullptr);
            exception();
        }
    } else if (status == "Black is in check.") {
        if (piece == 'k') {
            board->setBlackKing(org_posn);  // Change the position of King piece
        } else if (piece == 'K') {
            board->setWhiteKing(org_posn);  // Change the position of King piece
        }
        board->move(new_posn, org_posn);
        board->setPiece(new_posn, movement->getCaptured());
        movement->setCaptured(nullptr);
        exception();
    }

    //Now we know the movement is valid
    //Store the movement in the vector, moves.
    moves.emplace_back(movement);
    //Change the turn
    whiteTurn = !whiteTurn;

    //If it is not check, check stalemate
    if (status == "") {
        status = isStaleMate();
    }

    //Notify to the observers to display the board.
    if (status == "Checkmate! White wins!"){
        score->addToWhite(1);
        notify(status);
        return false;
    } else if (status == "Checkmate! Black wins!") {
        score->addToBlack(1);
        notify(status);
        return false;
    } else if (status == "Stalemate!") {
        score->addToWhite(0.5);
        score->addToBlack(0.5);
        notify(status);
        return false;
    } else {
        notify(status);
        return true;
    }
}

// Observers call getPiece function to get the piece which is on the Position
char Chess::getPiece(Position posn) const {
    return board->charAt(posn);
}