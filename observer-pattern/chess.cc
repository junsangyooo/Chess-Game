#include "chess.h"

Chess::Chess(std::shared_ptr<Board> bd, std::shared_ptr<ScoreBoard> sb): board{bd}, score{sb} {}

void Chess::undo() {
    if (moves.size() == 0) {
        throw std::out_of_range {"Cannot undo when the game starts"};
        return;
    }
    std::shared_ptr<Move> move = moves.back();
    moves.pop_back();
    int when = moves.size();
    Position pre_org_posn = move->getOrg();
    Position pre_new_posn = move->getNew();
    auto captured = move->getCaptured();
    char piece = board->charAt(pre_new_posn);
    if (piece== 'q' || piece == 'Q' || piece == 'n' || piece == 'N' || piece == 'r' || piece == 'R' || piece == 'b' || piece == 'B') {
        if (board->getPromoted(pre_new_posn) && board->getWhenPromoted(pre_new_posn) == when) {
            board->undoPromoted(move);
            board->setPromoted(pre_org_posn, false);
            board->setWhenPromoted(pre_org_posn, -1);
        } else if ((piece == 'r' || piece == 'R') && board->getWhenFirstMove(pre_new_posn) == when) {
            board->undo(move);
            board->setFirstMove(pre_org_posn, true);
            board->setWhenFirstMove(pre_org_posn, -1);
        }
    } else if (captured->getEnPassant()) {
        board->undoEnPassant(move);
        board->setEnPassant(Position((pre_org_posn * 10) / 10 + (pre_new_posn % 10)), false);
    } else if (piece == 'p' || piece == 'P') {
        board->undo(move);
    } else if (piece == 'k' || piece == 'K') {
        if (pre_new_posn + 2 == pre_org_posn) {
            board->undoCastling(move);
            board->setFirstMove(pre_org_posn, true);
            board->setWhenFirstMove(pre_org_posn, -1);
            board->setFirstMove(Position(pre_new_posn - 2), true);
            board->setWhenFirstMove(Position(pre_new_posn - 2), -1);
        } else if (pre_new_posn - 2 == pre_org_posn) {
            board->undoCastling(move);
            board->setFirstMove(pre_org_posn, true);
            board->setWhenFirstMove(pre_org_posn, -1);
            board->setFirstMove(Position(pre_new_posn + 1), true);
            board->setWhenFirstMove(Position(pre_new_posn + 1), -1);
        } else if (board->getWhenFirstMove(pre_new_posn) == when) {
            board->undo(move);
            board->setFirstMove(pre_org_posn, true);
            board->setWhenFirstMove(pre_org_posn, -1);
        } else {
            board->undo(move);
        }
    }
}

bool Chess::enPassant(std::shared_ptr<Move> movement, bool whiteTurn) {
    std::shared_ptr<Move> preMove = moves.back();
    Position pre_org_posn = preMove->getOrg();
    Position pre_new_posn = preMove->getNew();
    Position org_posn = movement->getOrg();
    Position new_posn = movement->getNew();
    if (Position(40  - (whiteTurn * 10)) > org_posn || org_posn < Position(47 - (whiteTurn * 10))) {
        return false;
    } else if (pre_new_posn == Position((org_posn / 10) + (new_posn % 10))) {
        if (pre_org_posn == Position(pre_new_posn - (whiteTurn * 20) + (!whiteTurn * 20))) {
            return true;
        } else {
            return false;
        }
    } 
    return false;
}

bool Chess::castling(std::shared_ptr<Move> movement, bool whiteTurn) {
    Position org_posn = movement->getOrg();
    Position new_posn = movement->getNew();
    if (!board->getFirstMove(org_posn)) {return false;}
    if (whiteTurn && whiteInCheck() != "") {return false;}
    if (!whiteTurn && blackInCheck() != "") {return false;}
    int index;
    if (new_posn + 2 == org_posn) {
        if (!board->getFirstMove(Position(new_posn - 2))) {return false;}
        if (board->charAt(Position(new_posn - 1)) != ' ' && board->charAt(Position(new_posn - 1)) != '-') {return false;}
        index = -1;
    } else {
        if (!board->getFirstMove(Position(new_posn + 1))) {return false;}
        index = 1;
    }
    int i = org_posn + index;
    bool valid = true;
    while(i != new_posn) {
        char tmp_piece = board->charAt(Position(i));
        if (tmp_piece != ' ' && tmp_piece != '-') {return false;}
        auto tmp_move = std::make_shared<Move>(org_posn, Position(i));
        board->move(tmp_move);
        if ((whiteTurn && whiteInCheck() != "") || (!whiteTurn && blackInCheck() != "")) {
            valid = false;
        }
        tmp_move = std::make_shared<Move>(Position(i), org_posn);
        board->move(tmp_move);
        if (!valid) {return false;}
        i += index;
    }
    return valid;
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

bool Chess::validKing(std::shared_ptr<Move> movement, bool whiteTurn) {
    Position org_posn = movement->getOrg();
    Position new_posn = movement->getNew();
    if (new_posn + 1 == org_posn || new_posn - 1 == org_posn) {
        return true;
    } else if (org_posn - 11 <= new_posn && new_posn <= org_posn - 9) {
        return true;
    } else if (org_posn + 9 <= new_posn && new_posn <= org_posn + 11) {
        return true;
    } else if (new_posn + 2 == org_posn || new_posn - 2 == org_posn) {
        return castling(movement, whiteTurn);
    }
    return false;
}

bool Chess::validQueen(std::shared_ptr<Move> movement) {
    Position org_posn = movement->getOrg();
    Position new_posn = movement->getNew();
    int diff = abs(org_posn - new_posn);
    int org_row = (org_posn / 10) * 10;
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
    int org_row = (org_posn / 10) * 10;
    int tmp;
    if (diff % 10 == 0) {tmp = 10;}
    else if (org_row <= new_posn && new_posn <= org_row + 7) {tmp = 1;}
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
    if (new_posn == Position(org_posn - 21) || new_posn == Position(org_posn - 19)) {
        return true;
    } else if (new_posn == Position(org_posn - 12) || new_posn == Position(org_posn - 8)) {
        return true;
    } else if (new_posn == Position(org_posn + 8) || new_posn == Position(org_posn + 12)) {
        return true;
    } else if (new_posn == Position(org_posn + 19) || new_posn == Position(org_posn + 21)) {
        return true;
    }
    return false;
}

bool Chess::validPawn(std::shared_ptr<Move> movement, bool whiteTurn, char promote) {
    Position org_posn = movement->getOrg();
    Position new_posn = movement->getNew();
    char captured = board->charAt(new_posn);
    bool firstMove = board->getFirstMove(org_posn);
    if (Position(org_posn  - (whiteTurn * 11) + (!whiteTurn * 11)) == new_posn || Position(org_posn  - (whiteTurn * 9) + (!whiteTurn * 9)) == new_posn) {
        if (captured == ' ' || captured == '-') {
            return enPassant(movement, whiteTurn);
        } else if (promote != '.') {
            if (Position(70 - (whiteTurn * 70)) <= new_posn && new_posn <= Position(77 - (whiteTurn*70))) {
                return true;
            } else {return false;}
        } else {return true;}
    } else if (Position(org_posn - (whiteTurn*10) + (!whiteTurn*10)) == new_posn) {
        if (promote != '.' && Position(70 - (whiteTurn * 70)) <= new_posn && new_posn <= Position(77 - (whiteTurn*70))) {
            return true;
        } else if (promote != '.') {return false;}
        else {return true;}
    } else if (firstMove && Position(org_posn - (whiteTurn*20) + (!whiteTurn*20)) == new_posn) {
        char between = board->charAt(Position(org_posn - (whiteTurn*10) + (!whiteTurn*10)));
        if (between == ' ' || between == '-') {
            return true;
        } else {
            return false;
        }
    }
    return false;
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
        if ('A' <= new_piece && new_piece <= 'Z') {
            return false;
        }
    } else {
        if ('A' <= piece && piece <= 'Z') {
            return false;
        }
        if ('a' <= new_piece && new_piece <= 'z') {
            return false;
        }
    }

    if (piece == 'k' || piece == 'K') {    //Check King move
        if (!validKing(movement, whiteTurn)) {return false;}
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
        if (!validPawn(movement, whiteTurn, promote)) {return false;}
    } else {
        return false;
    }
    bool valid = true;
    auto tmp_move = std::make_shared<Move>(new_posn, org_posn);
    board->move(movement);
    if ((whiteTurn && whiteInCheck() != "") || (!whiteTurn && blackInCheck() != "")) {
        board->move(tmp_move);
        valid = false;
    }
    board->move(tmp_move);
    return valid;
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
        Position org_posn = pieces[index];
        for(int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                int posn_index = i*10 + j;
                Position new_posn = Position(posn_index);
                char c  = board->charAt(new_posn);
                if (whiteTurn && 'A' <= c && c <= 'Z') {
                    continue;
                } else if (!whiteTurn && 'a' <= c && c <= 'z') {
                    continue;
                } else {
                    auto move = std::make_shared<Move>(org_posn, new_posn);
                    std::cout << "before valid test" << std::endl;
                    if (validMove(move, whiteTurn)) {
                        std::cout << "after valid test and returning empty" << std::endl;
                        return "";
                    }
                }
            }
        }

    }
    std::cout << "after valid test returning stalemate" << std::endl;
    return "Stalemate!";
}

std::string Chess::checkmateTest(bool whiteTurn) {
    std::string stalemate = stalemateTest(whiteTurn);
    if (stalemate != "" && whiteTurn) {
        return "Checkmate! Black wins!";
    } else if (stalemate != "") {
        return "Checkmate! White wins!";
    }
    return "";
}

std::string Chess::blackInCheck() {
    Position blackKing;
    bool kingFound = false;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Position posn = Position(i*10 + j);
            char piece = board->charAt(posn);
            if (piece == 'k') {
                blackKing = posn;
                kingFound = true;
                break;
            } else { continue;}
        }
        if (kingFound) {break;}
    }
    bool inCheck = false;
    std::vector<std::shared_ptr<Position>> whitePieces;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Position posn = Position(i*10 + j);
            char piece = board->charAt(posn);
            if ('A' <= piece && piece <= 'Z') {
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
        return "Black is in check.";
    }
    return "";
}

std::string Chess::whiteInCheck() {
    Position whiteKing;
    bool kingFound = false;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Position posn = Position(i*10 + j);
            char piece = board->charAt(posn);
            if (piece == 'K') {
                whiteKing = posn;
                kingFound = true;
                break;
            } else { continue;}
        }
        if (kingFound) {break;}
    }
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
        return "White is in check.";
    }
    return "";
}

//Controller calls movePiece function with the movement of next turn.  
bool Chess::movePiece(std::shared_ptr<Move> movement, bool whiteTurn, char promote) {
    Position org_posn = movement->getOrg();
    Position new_posn = movement->getNew();
    int when = moves.size();
    char piece = board->charAt(org_posn);
    char captured = board->charAt(new_posn);
    
    // Check valid move and move
    bool valid = validMove(movement, whiteTurn, promote);
    if (!valid) {
        throw std::out_of_range {"Invalid move!"};
    } else if ((piece == 'k' || piece == 'K') && (new_posn + 2 == org_posn || new_posn - 2 == org_posn)) {
        board->castling(movement);
        board->setFirstMove(new_posn, false);
        board->setWhenFirstMove(new_posn, when);
        if (new_posn + 2 == org_posn) {
            board->setWhenFirstMove(Position(new_posn + 1), when);
            board->setFirstMove(Position(new_posn + 1), false);
            movement->setCell1(((new_posn + 1) / 10) * 10 + ((new_posn + 1) % 10));
            movement->setCell2(((new_posn - 2) / 10) * 10 + ((new_posn - 2) % 10));
        } else {
            board->setWhenFirstMove(Position(new_posn - 1), when);
            board->setFirstMove(Position(new_posn - 1), false);
            movement->setCell1(((new_posn - 1) / 10) * 10 + ((new_posn - 1) % 10));
            movement->setCell2(((new_posn + 1) / 10) * 10 + ((new_posn + 1) % 10));
        }
    } else if (piece == 'k' || piece == 'K' || piece == 'r' || piece == 'R') {
        movement->setCaptured(board->getPiece(new_posn));
        board->move(movement);
        if (board->getFirstMove(new_posn)) {
            board->setFirstMove(new_posn, false);
            board->setWhenFirstMove(new_posn, when);
        }
    } else if (piece == 'p' || piece == 'P') {
        if (Position(org_posn  - (whiteTurn * 11) + (!whiteTurn * 11)) == new_posn || Position(org_posn  - (whiteTurn * 9) + (!whiteTurn * 9)) == new_posn) {
            if (captured == ' ' || captured == '-') {
                board->setEnPassant(Position((org_posn / 10) + (new_posn % 10)), true);
                movement->setCaptured(board->getPiece(Position((org_posn / 10) + (new_posn % 10))));
                movement->setCell1(((org_posn / 10)*10) + (new_posn % 10));
                board->enPassant(movement);
            } else if (promote != '.') {
                movement->setPromoted(board->getPiece(org_posn));
                movement->setCaptured(board->getPiece(new_posn));
                board->move(movement, promote);
                board->setPromoted(new_posn, true);
                board->setWhenPromoted(new_posn, when);
            } else if (board->getFirstMove(org_posn)) {
                board->setFirstMove(org_posn, false);
                board->setWhenFirstMove(org_posn, when);
                movement->setCaptured(board->getPiece(new_posn));
                board->move(movement);
            } else {
                movement->setCaptured(board->getPiece(new_posn));
                board->move(movement);
            }
        } else if (promote != '.') {
            movement->setPromoted(board->getPiece(org_posn));
            board->move(movement, promote);
            board->setPromoted(new_posn, true);
            board->setWhenPromoted(new_posn, when);
        } else if (board->getFirstMove(org_posn)) {
            board->setFirstMove(org_posn, false);
            board->setWhenFirstMove(org_posn, when);
            board->move(movement);
        } else {
            board->move(movement);
        }
    } else if (captured == ' ' || captured == '-') {
        board->move(movement);
    } else {
        movement->setCaptured(board->getPiece(new_posn));
        board->move(movement);
    }

    //Now, we check it's check, checkmate or stalemate
    std::string status;
    if (whiteTurn){
        status = blackInCheck();
    } else {
        status = whiteInCheck();
    }
    std::cout << status << std::endl;
    if (status != "") {
        std::string checkmate = checkmateTest(!whiteTurn);
        if (checkmate != "") {
            status = checkmate;
        }
    } else {
        std::cout << "1" << std::endl;
        status = stalemateTest(!whiteTurn);
        std::cout << "2" << std::endl;
    }

    movement->setChecked(status);
    std::cout << "4" << std::endl;
    moves.emplace_back(movement);
    std::cout << "5" << std::endl;

    int org_changed_posn = (org_posn / 10) * 10 + (org_posn % 10);
    int new_changed_posn = (new_posn / 10) * 10 + (new_posn % 10);
    //Notify to the observers to display the board.
    bool gameEnd = false;
    if (status == "Checkmate! White wins!"){
        score->addToWhite(1);
        gameEnd = false;
    } else if (status == "Checkmate! Black wins!") {
        score->addToBlack(1);
        gameEnd = false;
    } else if (status == "Stalemate!") {
        score->addToWhite(0.5);
        score->addToBlack(0.5);
        gameEnd = false;
    }
    drawBoard(status, org_changed_posn, new_changed_posn, movement->getCell1(), movement->getCell2());
    return gameEnd;
}

// Observers call getPiece function to get the piece which is on the Position
char Chess::charAt(Position posn) const {
    return board->charAt(posn);
}


std::string Chess::checkTest() {
    std::string white = whiteInCheck();
    std::string black = blackInCheck();
    if (white == "" && black == "") {return "";}
    else if (black == "") {return white;}
    return black;
}

Chess::~Chess() {
    int length = moves.size();
    for(int i = 0; i < length; ++i) {
        moves.erase(moves.begin());
    }
}