#include "chess.h"

Chess::Chess(std::shared_ptr<Board> bd, std::shared_ptr<ScoreBoard> sb): board{bd}, score{sb} {}

void exception() {
    throw std::out_of_range {"Invalid Move!"};
}

void Chess::undo() {
    
}

bool Chess::enPassant(std::shared_ptr<Move> movement) {
    std::shared_ptr<Move> preMove = moves.back();
    Position org_posn = movement->getOrg();
    Position new_posn = movement->getNew();
    char piece = board->charAt(org_posn);
    Position pre_org_posn = preMove->getOrg();
    Position pre_new_posn = preMove->getNew();
    if (piece == 'p') {
        Position captured = Position(new_posn - 10);
        if (40 > org_posn || org_posn > 47) {return false;}
        else if (board->charAt(captured) != 'P') {return false;}
        else if (pre_new_posn != new_posn - 10 && pre_org_posn != new_posn + 10) {return false;}
        /*movement->setCaptured(board->getPiece(captured));
        board->move(org_posn, new_posn);
        if (blackInCheck() != "") {
            board->move(new_posn, org_posn);
            board->setPiece(captured, movement->getCaptured());
            movement->setCaptured(nullptr);
            return false;
        }*/
    } else {
        Position captured = Position(new_posn + 10);
        if (30 > org_posn || org_posn > 37) {return false;}
        else if (board->charAt(captured) != 'p') {return false;}
        else if (pre_new_posn != new_posn + 10) {return false;}
        else if (pre_org_posn != new_posn - 10) {return false;}
        /*movement->setCaptured(board->getPiece(captured));
        board->move(org_posn, new_posn);
        if (whiteInCheck() != "") {
            board->move(new_posn, org_posn);
            board->setPiece(captured, movement->getCaptured());
            movement->setCaptured(nullptr);
            return false;
        }*/
    }
    return true;
}

bool Chess::castling(std::shared_ptr<Move> movement) {
    Position org_posn = movement->getOrg();
    Position new_posn = movement->getNew();
    bool firstMove;
    if (!board->getFirstMove(org_posn)) {return false;}
    if (whiteTurn && whiteInCheck(whiteTurn) != "") {return false;}
    else if (!whiteTurn && blackInCheck(whiteTurn) != "") {return false;}
    if (new_posn == org_posn + 2) {
        firstMove = board->getFirstMove(Position(new_posn + 1));
    } else {
        if (board->colourAt(Position(new_posn - 1)) != "") {return false;}
        firstMove = board->getFirstMove(Position(new_posn - 2));
    }
    if (!firstMove) {return false;}
    //Check whether the path for castling right side is checked
    for(int i = org_posn + 1; i <= new_posn; i++) {
        if (board->colourAt(Position(i)) != "") {return false;}
        board->move(org_posn, Position(i));
        if (whiteTurn) {
            board->setWhiteKing(Position(i));
            if (whiteInCheck(whiteTurn) != "") {
                board->move(Position(i), org_posn);
                return false;
            }
        } else {
            board->setBlackKing(Position(i));
            if (blackInCheck(whiteTurn) != "") {
                board->move(Position(i), org_posn);
                return false;
            }
        }
    }
    //Check whether the path for castling left side is checked
    for(int i = org_posn - 1; i >= new_posn; i--) {
        if (board->colourAt(Position(i)) != "") {return false;}
        board->move(org_posn, Position(i));
        if (whiteTurn) {
            board->setWhiteKing(Position(i));
            if (whiteInCheck(whiteTurn) != "") {
                board->move(Position(i), org_posn);
                return false;
            }
        } else {
            board->setBlackKing(Position(i));
            if (blackInCheck(whiteTurn) != "") {
                board->move(Position(i), org_posn);
                return false;
            }
        }
    }
    return true;
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
    } else if (new_posn + 2 == org_posn || new_posn - 2 == org_posn) {
        return castling(movement);
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
    char piece = board->charAt(org_posn);
    char captured = board->charAt(new_posn);
    bool firstMove = board->getFirstMove(org_posn);
    if ('A' <= piece && piece <= 'Z') {
        if (org_posn - 11 == new_posn || new_posn == org_posn - 9) {
            if ('a' <= captured && captured <= 'z') {
                return true;
            } else if (captured == ' ' || captured == '-') {
                return enPassant(movement);
            }
        } else if (org_posn - 10 == new_posn){
            if (captured != ' ' && captured != '-') {return false;}
        } else if (firstMove && new_posn == org_posn - 20) {
            if (captured != ' ' && captured != '-') {return false;}
        } else {return false;}
    } else if ('a' <= piece && piece <= 'z') {
        if (org_posn + 9 == new_posn || new_posn == org_posn + 11) {
            if ('A' <= captured && captured <= 'Z') {
                return true;
            } else if (captured == ' ' || captured == '-') {
                return enPassant(movement);
            }
        } else if (org_posn + 10 == new_posn) {
            if (captured != ' ' && captured != '-') {return false;}
        } else if (firstMove && new_posn == org_posn + 20) {
            if (captured != ' ' && captured != '-') {return false;}
        } else {return false;}
    } else {
        return false;
    }
}


bool Chess::validMove(std::shared_ptr<Move> movement, bool whiteTurn) {
    Position org_posn = movement->getOrg();
    Position new_posn = movement->getNew();

     // Check whether the move does not change anything.
    if (org_posn == new_posn) {
        return false;
    }

    // Check whether the piece would be captured has the same side piece.
    char piece = board->charAt(org_posn);
    char new_piece = board->charAt(new_posn);
    if (piece == ' ' || piece == '-') {return false;}   //Check Empty piece
    if (whiteTurn) {
        if ('a' <= piece && piece <= 'z') {
            return false;
        }
        if (new_piece >= 'A' && 'Z' >= new_piece) {return false;}
    } else {
        if (piece >= 'A' && 'Z' >= piece) {
            return false;
        }
        if ('a' <= new_piece && new_piece <= 'z') {return false;}
    }

    if (piece == 'k' || piece == 'K') {    //Check King move
        if (!validKing(movement)) {return false;}
        /*if (!validKing(movement) && new_posn + 2 == org_posn || new_posn - 2 == org_posn) {
            if(!castling(movement, whiteTurn)) {return false;}
                board->setCastling(org_posn, true);
                if (new_posn > org_posn) {
                    board->setCastling(Position(new_posn + 1), true);
                    //movement->setCaptured(board->getPiece(Position(new_posn + 1)));
                }
                else {
                    board->setCastling(Position(new_posn - 2), true);
                    //movement->setCaptured(board->getPiece(Position(new_posn - 2)));
                }
                return true;
            } else {
                return false;
        }*/
    } else if (piece == 'q' || piece == 'Q') {    //Check Queen move
        if (!validQueen(movement)) {return false;}
    }
    else if (piece == 'b' || piece == 'B') {    //Check Bishop move
        if (!validBishop(movement)) {return false;}
    }
    else if (piece == 'n' || piece == 'N') {    //Check Knight move
        if (!validKnight(movement)) {return false;}
    }
    else if (piece == 'r' || piece == 'R') {    //Check Rook move
        if (!validRook(movement)) {return false;}
    }
    else if (piece == 'p' || piece == 'P') { //Check Pawn move
        if (!validPawn(movement)) {return false;}
        /*if (org_posn > new_posn) {
            board->setEnPassant(Position(new_posn + 10), true);
            movement->setCaptured(board->getPiece(Position(new_posn + 10)));
        }
        else {
            board->setEnPassant(Position(new_posn -10), true);
            movement->setCaptured(board->getPiece(Position(new_posn - 10)));
        }*/
    } else {
        return false;
    }
}

std::string Chess::stalemateTest() {

}

std::string Chess::blackInCheck() {
    Position blackKing = board->getBlackKing();
    bool inCheck = false;
    int whites = 0;
    int blacks = 0;
    int kingIndex = 0;
    std::vector<std::shared_ptr<Position>> blackPieces;
    std::vector<std::shared_ptr<Position>> whitePieces;
    std::vector<std::shared_ptr<Position>> checkingPiece;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Position posn = Position(i*10 + j);
            char piece = board->charAt(posn);
            auto tmp_move_black = std::make_shared<Move>(posn, blackKing);
            if (piece == ' ' || piece == '-') {continue;}
            else if (piece == 'K') {
                whitePieces.emplace_back(posn);
                whites++;
                if (validKing(tmp_move_black)) {
                    inCheck = true;
                    checkingPiece.emplace_back(posn);
                }
            } else if (piece == 'B') {
                whitePieces.emplace_back(posn);
                whites++;
                if (validBishop(tmp_move_black)) {
                    inCheck = true;
                    checkingPiece.emplace_back(posn);
                }
            } else if (piece == 'Q') {
                whitePieces.emplace_back(posn);
                whites++;
                if (validQueen(tmp_move_black)) {
                    inCheck = true;
                    checkingPiece.emplace_back(posn);
                }
            } else if (piece == 'R') {
                whitePieces.emplace_back(posn);
                whites++;
                if (validRook(tmp_move_black)) {
                    inCheck = true;
                    checkingPiece.emplace_back(posn);
                }
            } else if (piece == 'N') {
                whitePieces.emplace_back(posn);
                whites++;
                if (validKnight(tmp_move_black)) {
                    inCheck = true;
                    checkingPiece.emplace_back(posn);
                }
            } else if (piece == 'P') {
                whitePieces.emplace_back(posn);
                whites++;
                if (validPawn(tmp_move_black)) {
                    inCheck = true;
                    checkingPiece.emplace_back(posn);
                }
            } else if (piece == 'k'){
                kingIndex = blackPieces.size();
                blackPieces.emplace_back(posn);
                blacks++;
            } else {
                blackPieces.emplace_back(posn);
                blacks++;
            }
        }
    }
    if (!whiteTurn && inCheck) {return "Black is in check.";}
    else if (inCheck) {board->setIsChecked(blackKing, true);}
    int check = checkingPiece.size();
    
}

std::string Chess::whiteInCheck() {
    Position whiteKing = board->getWhiteKing();
    bool inCheck = false;
    std::vector<std::shared_ptr<Position>> blackPieces;
    std::vector<std::shared_ptr<Position>> whitePieces;
    int blacks = 0;
    int whites = 0;
    //Now check whether the King is under check
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Position posn = Position(i*10 + j);
            char piece = board->charAt(posn);
            auto tmp_move_white = std::make_shared<Move>(posn, whiteKing);
            if (piece ==' ' || piece == '-'){continue;}
            else if (piece == 'k') {
                blackPieces.emplace_back(posn);
                blacks++;
                if (validKing(tmp_move_white)) {inCheck = true;}
            } else if (piece == 'b') {
                blackPieces.emplace_back(posn);
                blacks++;
                if (validBishop(tmp_move_white)) {inCheck = true;}
            } else if (piece == 'q') {
                blackPieces.emplace_back(posn);
                blacks++;
                if (validQueen(tmp_move_white)) {inCheck = true;}
            } else if (piece == 'r') {
                blackPieces.emplace_back(posn);
                blacks++;
                if (validRook(tmp_move_white)) {inCheck = true;}
            } else if (piece == 'n') {
                blackPieces.emplace_back(posn);
                blacks++;
                if (validKnight(tmp_move_white)) {inCheck = true;}
            } else if (piece == 'p') {
                blackPieces.emplace_back(posn);
                blacks++;
                if (validPawn(tmp_move_white)) {inCheck = true;}
            } else {
                whites++;
                whitePieces.emplace_back(posn);
            }
        }
    }
    if (whiteTurn && inCheck) {return "White is in check.";}
    else if (inCheck) {board->setIsChecked(whiteKing, true);}
}

void Chess::undo() {

}

//Controller calls movePiece function with the movement of next turn.
bool Chess::movePiece(std::shared_ptr<Move> movement, bool whiteTurn) {
    Position org_posn = movement->getOrg();
    Position new_posn = movement->getNew();
    char piece = board->charAt(org_posn);

    if (!validMove(movement, whiteTurn)) {
        throw std::out_of_range {"Invalid move!"};
    }

    moves.emplace_back(movement);   //store the movement for undoing
    board->setFirstMove(org_posn, false);   //Set the fistMove moving piece to false
    board->move(org_posn, new_posn);    //move!
    if (piece == 'k') {
        board->setBlackKing(new_posn);  // Update the position of King piece
    } else if (piece == 'K') {
        board->setWhiteKing(new_posn);  // Update the position of King piece
    }

    //Now, we check whether the movement put the king under check
    std::string status;
    if (whiteTurn){
        status = whiteInCheck(whiteTurn);
        if (status != "") {  //If thie move makes their king under check, undo
            undo();
            throw std::out_of_range {"Make King under check."};
        }
        else {status = blackInCheck(whiteTurn);}
    } else {
        status = blackInCheck(whiteTurn);
        if (status != "") {  //If thie move makes their king under check, undo
            undo();
            throw std::out_of_range {"Make King under check."};
        }
        else {status = whiteInCheck(whiteTurn);}
    }

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

Chess::~Chess() {
    score = nullptr;
    for(int i = 0; i < moves.size(); ++i) {
        moves.erase(moves.begin());
    }
    board = nullptr;
}