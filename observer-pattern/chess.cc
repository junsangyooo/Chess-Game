#include "chess.h"

Chess::Chess(std::shared_ptr<Board> bd): board{bd} {}

void exception() {
    throw std::out_of_range {"Invalid Move!"};
}

std::string Chess::isCheck() {
    bool check = false;
    std::string colour = "White";
    Position whiteKing;
    Position blackKing;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (bd->charAt(Position(i*10 + j)) == 'K'){
                whiteKing = Position(i*10 + j);
            } else if (bd->charAt(Position(i*10 + j)) == 'k'){
                blackKing = Position(i*10 + j);
            }
        }
    }
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Position posn = Position(i*10 + j);
            char piece = bd->charAt(posn);
            if (piece == 'p') {
                if (posn )
            }
        }
    }

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
        try {validKing(movement);}      // Check general valid move
        catch (std::out_of_range &e) {throw e;}
        if (new_posn + 2 == org_posn || new_posn - 2 == org_posn) { // Check Castling
            try {castling(movement);}
            catch(const std::out_of_range& e) {throw e;}
            specialCase = true;
            movement->setCaptured(board->getPiece(new_posn));   // If castling is valid
            board->castling(org_posn, new_posn);
        }
    }
    else if (piece == 'q' || piece == 'Q') {    //Check Queen move
        try{validQueen(movement);}  //Check general valid move of Queen piece.
        catch (std::out_of_range &e) {throw e;} //If the move is invalid, throw and exception.
    }
    else if (piece == 'b' || piece == 'B') {    //Check Bishop move
        try{validBishop(movement);}  //Check general valid move of Bishop piece.
        catch (std::out_of_range &e) {throw e;} //If the move is invalid, throw and exception.
    }
    else if (piece == 'n' || piece == 'N') {    //Check Knight move
        try{validKnight(movement);}  //Check general valid move of Knight piece.
        catch (std::out_of_range &e) {throw e;} //If the move is invalid, throw and exception.
    }
    else if (piece == 'r' || piece == 'R') {    //Check Rook move
        try{validRook(movement);}  //Check general valid move of Rook piece.
        catch (std::out_of_range &e) {throw e;} //If the move is invalid, throw and exception.
    }
    else {  //Check Pawn move
        try{validPawn(movement);}  //Check general valid move of Pawn piece.
        catch (std::out_of_range &e) {throw e;}
        //Check En Passant
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

    //If the movement is not En Passant or Castling, move in general
    if (!specialCase) { 
        if (piece == 'k') {
            board->setBlackKing(new_posn);  // Change the position of King piece
        } else if (piece == 'K') {
            board->setWhiteKing(new_posn);  // Change the position of King piece
        }
        movement->setCaptured(board->getPiece(new_posn)); // Store captured piece into the movement
        board->move(org_posn, new_posn);    // Change the board
    }

    //Now, we check whether the movement put the king under check
    //If so, undo
    std::string status = isCheck();
    if (whiteTurn) {
        if (status == "White is in check." || status == "Checkmate! Black wins!") {
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
    } else if (status == "Black is in check." || status == "Checkmate! White wins!") {
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