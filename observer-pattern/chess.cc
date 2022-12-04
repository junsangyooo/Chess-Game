#include "chess.h"

Chess::Chess(std::shared_ptr<Board> bd, std::shared_ptr<ScoreBoard> sb): board{bd}, score{sb} {}

void Chess::undo() {
    if (moves.size() == 0) {
        throw std::out_of_range {"Cannot undo when the game starts"};
        return;
    }
    std::shared_ptr<Move> move = moves.back();
    moves.pop_back();
    Position pre_org_posn = move->getOrg();
    Position pre_new_posn = move->getNew();
    auto captured = move->getCaptured();
    int when = moves.size();
    board->undo(move, when);
    char piece = board->charAt(pre_new_posn);
    int org_changed_posn = (pre_org_posn / 10) * 10 + pre_org_posn % 10;
    int new_changed_posn = (pre_new_posn / 10) * 10 + pre_new_posn % 10;
    if (piece== 'q' || piece == 'Q' || piece == 'n' || piece == 'N' || piece == 'r' || piece == 'R' || piece == 'b' || piece == 'B') {
        if (board->getPromoted(pre_new_posn)) {
            int whenPromoted = board->getWhenPromoted(pre_new_posn);
            if (whenPromoted == when) {
                board->undoPromoted(move);
            }
            else {
                board->undo(move, when);
            }
            drawBoard(move->getChecked(), org_changed_posn, new_changed_posn);
        }
    } else if (piece == 'k' || piece == 'K') {
        int diff = abs(pre_new_posn - pre_org_posn);
        if (diff == 2) {
            board->undoCastling(move, when);
            drawBoard(move->getChecked(), org_changed_posn, new_changed_posn, move->getCell1(), move->getCell2());
        } else {
            board->undo(move, when);
            drawBoard(move->getChecked(), org_changed_posn, new_changed_posn);
        }
    } else if (piece == 'p' || piece == 'P') {
        if (captured->getPiece() == 'p' || captured->getPiece() == 'P') {
            if (captured->getEnPassant()) {
                board->undoEnPassant(move, when);
                drawBoard(move->getChecked(), org_changed_posn, new_changed_posn, move->getCell1(), move->getCell2());
            } else {
                board->undo(move, when);
                drawBoard(move->getChecked(), org_changed_posn, new_changed_posn);
            }
        } else {
            board->undo(move, when);
            drawBoard(move->getChecked(), org_changed_posn, new_changed_posn);
        }
    }
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
    } else {
        Position captured = Position(new_posn + 10);
        if (30 > org_posn || org_posn > 37) {return false;}
        else if (board->charAt(captured) != 'p') {return false;}
        else if (pre_new_posn != new_posn + 10) {return false;}
        else if (pre_org_posn != new_posn - 10) {return false;}
    }
    return true;
}

bool Chess::castling(std::shared_ptr<Move> movement) {
    Position org_posn = movement->getOrg();
    Position new_posn = movement->getNew();
    char piece = board->charAt(org_posn);
    int when = moves.size();
    if (!board->getFirstMove(org_posn)) {return false;}
    if (new_posn + 2 == org_posn) {
        if (!board->getFirstMove(Position(new_posn - 2))) {return false;}
        if (board->charAt(Position(new_posn - 1)) != ' ' && board->charAt(Position(new_posn - 1)) != '-') {return false;}
        for(int i = org_posn - 1; i >= new_posn; i--) {
            char tmp_piece = board->charAt(Position(i));
            if (tmp_piece != ' ' && tmp_piece != '-') {return false;}
            auto tmp_move = std::make_shared<Move>(org_posn, Position(i));
            board->move(tmp_move, when);
            moves.emplace_back(tmp_move);
            if ((piece == 'k' && blackInCheck() != "") || (piece == 'K' && whiteInCheck() != "")) {
                undo();
                return false;
            } else {
                undo();
                continue;
            }
        }
    } else {
        if (!board->getFirstMove(Position(new_posn + 1))) {return false;}
        for(int i = org_posn + 1; i <= new_posn; i++) {
            char tmp_piece = board->charAt(Position(i));
            if (tmp_piece != ' ' && tmp_piece != '-') {return false;}
            auto tmp_move = std::make_shared<Move>(org_posn, Position(i));
            board->move(tmp_move, when);
            moves.emplace_back(tmp_move);
            if ((piece == 'k' && blackInCheck() != "") || (piece == 'K' && whiteInCheck() != "")) {
                undo();
                return false;
            } else {
                undo();
                continue;
            }
        }
    }
    return true;
}


bool Chess::validBishop(std::shared_ptr<Move> movement) {
    Position org_posn = movement->getOrg();
    Position new_posn = movement->getNew();
    int diff = abs(org_posn - new_posn);
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

bool Chess::validMove(std::shared_ptr<Move> movement, bool whiteTurn, char promote) {
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
    } else {
        return false;
    }

    board->move(movement, moves.size(), promote);
    moves.emplace_back(movement);
    if (whiteTurn && whiteInCheck() != "") {
        undo();
        return false;
    } else if (!whiteTurn && blackInCheck() != "") {
        undo();
        return false;
    }
    undo();
    return true;
}

std::string Chess::stalemateTest(bool whiteTurn) {
    std::vector<Position> pieces;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Position posn = Position(i*10 + j);
            char piece = board->charAt(posn);
            if (whiteTurn && 'A' <= piece && piece <= 'Z') {
                pieces.emplace_back(posn);
            } else if (!whiteTurn && 'a' <= piece && piece <= 'z') {
                pieces.emplace_back(posn);
            }
        }
    }
    int length = pieces.size();
    for (int index = 0; index < length; ++index) {
        Position org_posn = pieces.at(index);
        for(int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                int posn_index = i*10- + j;
                Position new_posn = Position(posn_index);
                char c  = board->charAt(new_posn);
                if (whiteTurn && 'A' <= c && c <= 'Z') {
                    continue;
                } else if (!whiteTurn && 'a' <= c && c <= 'z') {
                    continue;
                } else {
                    auto move = std::make_shared<Move>(org_posn, new_posn);
                    if (validMove(move, whiteTurn)) {
                        return "";
                    }
                }
            }
        }
    }
    return "Stalemate!";
}

std::string Chess::checkmateTest(bool whiteTurn) {
    std::string stalemate = stalemateTest(whiteTurn);
    if (stalemate != "" && whiteTurn) {
        return "Checkmate! Black wins!";
    } else if (stalemate != "") {
        return "Checkmate! White wins!";
    } else {return "";}
}

std::string Chess::blackInCheck() {
    Position blackKing = board->getBlackKing();
    bool inCheck = false;
    std::vector<std::shared_ptr<Position>> whitePieces;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Position posn = Position(i*10 + j);
            char piece = board->charAt(posn);
            if (piece == ' ' || piece == '-') {continue;}
            else if ('A' <= piece && piece <= 'Z') {
                auto tmp_move = std::make_shared<Move>(posn, blackKing);
                if (validMove(tmp_move, true)) {
                    inCheck = true;
                    break;
                }
            } else { continue;}
        }
        if (inCheck) {break;}
    }
    if (inCheck) {
        board->setIsChecked(blackKing, true);
        return "Black is in check.";
    }
    else {return "";}
}

std::string Chess::whiteInCheck() {
    Position whiteKing = board->getWhiteKing();
    bool inCheck = false;
    std::vector<std::shared_ptr<Position>> blackPieces;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Position posn = Position(i*10 + j);
            char piece = board->charAt(posn);
            if (piece == ' ' || piece == '-') {continue;}
            else if ('a' <= piece && piece <= 'z') {
                auto tmp_move = std::make_shared<Move>(posn, whiteKing);
                if (validMove(tmp_move, false)) {
                    inCheck = true;
                    break;
                }
            } else { continue;}
        }
        if (inCheck) {break;}
    }
    if (inCheck) {
        board->setIsChecked(whiteKing, true);
        return "White is in check.";
    } else {
        return "";
    }
}

//Controller calls movePiece function with the movement of next turn.  
bool Chess::movePiece(std::shared_ptr<Move> movement, bool whiteTurn, char promote) {
    Position org_posn = movement->getOrg();
    Position new_posn = movement->getNew();
    int when = moves.size();
    bool valid = validMove(movement, whiteTurn);
    if (!valid) {
        throw std::out_of_range {"Invalid move!"};
    } else {
        board->move(movement, when);
    }

    //Now, we check whether the movement put the king under check
    std::string status;
    if (whiteTurn){
        status = blackInCheck();
    } else {
        status = whiteInCheck();
    }

    if (status != "") {
        std::string checkmate = checkmateTest(!whiteTurn);
        if (checkmate != "") {
            status = checkmate;
        }
    } else {
        status = stalemateTest(!whiteTurn);
    }

    movement->setChecked(status);
    moves.emplace_back(movement);

    int org_changed_posn = (org_posn / 10) * 10 + org_posn % 10;
    int new_changed_posn = (new_posn / 10) * 10 + new_posn % 10;
    //Notify to the observers to display the board.
    if (status == "Checkmate! White wins!"){
        score->addToWhite(1);
        drawBoard(status, org_changed_posn, new_changed_posn, movement->getCell1(), movement->getCell2());
        return false;
    } else if (status == "Checkmate! Black wins!") {
        score->addToBlack(1);
        drawBoard(status, org_changed_posn, new_changed_posn, movement->getCell1(), movement->getCell2());
        return false;
    } else if (status == "Stalemate!") {
        score->addToWhite(0.5);
        score->addToBlack(0.5);
        drawBoard(status, org_changed_posn, new_changed_posn, movement->getCell1(), movement->getCell2());
        return false;
    } else {
        drawBoard(status, org_changed_posn, new_changed_posn, movement->getCell1(), movement->getCell2());
        return true;
    }
}

// Observers call getPiece function to get the piece which is on the Position
char Chess::getPiece(Position posn) const {
    return board->charAt(posn);
}

Chess::~Chess() {
    int length = moves.size();
    for(int i = 0; i < length; ++i) {
        moves.erase(moves.begin());
    }
}

std::string Chess::checkTest() {
    std::string white = whiteInCheck();
    std::string black = blackInCheck();
    if (white == "") {return black;}
    else if (black == "") {return white;}
    else {return "";}
}