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
    std::shared_ptr<Piece> captured = move->getCaptured();
    char piece = board->charAt(pre_new_posn);
    if (piece== 'q' || piece == 'Q' || piece == 'n' || piece == 'N' || piece == 'r' || piece == 'R' || piece == 'b' || piece == 'B') {
        if (board->getPromoted(pre_new_posn) && board->getWhenPromoted(pre_new_posn) == when) {
            board->undoPromoted(move);
        } else if ((piece == 'r' || piece == 'R') && board->getWhenFirstMove(pre_new_posn) == when) {
            board->undo(move);
            board->setFirstMove(pre_org_posn, true);
            board->setWhenFirstMove(pre_org_posn, -1);
        } else {
            board->undo(move);
        }
    } else if (piece == 'p' || piece == 'P') {
        std::cout << 11 << std::endl;
        if (captured != nullptr) {
            char tmp = captured->getPiece();
            if ((tmp == 'p' || tmp == 'P') && captured->getEnPassant()) {
                board->undoEnPassant(move);
                board->setEnPassant(Position((pre_org_posn * 10) / 10 + (pre_new_posn % 10)), false);
            } else {board->undo(move);}
        } else {board->undo(move);}
        std::cout << 33 << std::endl;
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
    char captured = board->charAt(pre_new_posn);
    if ((whiteTurn && captured != 'p') && (!whiteTurn && captured != 'P')) {return false;}
    if (pre_new_posn != Position((org_posn / 10) * 10+ (new_posn % 10))) {
        return false;
    }
    if (pre_org_posn != Position(pre_new_posn - (whiteTurn * 20) + (!whiteTurn * 20))) {
        return false;
    }

    movement->setCaptured(board->getPiece(pre_new_posn));
    board->enPassant(movement);
    if ((whiteTurn && whiteInCheck() != "") || (!whiteTurn && blackInCheck() != "")) {
        board->undoEnPassant(movement);
        return false;
    }
    board->undoEnPassant(movement);
    return true;
}

bool Chess::castling(std::shared_ptr<Move> movement, bool whiteTurn) {
    Position org_posn = movement->getOrg();
    Position new_posn = movement->getNew();
    char king = board->charAt(org_posn);
    if (org_posn != 4 && org_posn != 74) {
        return false;
    } else if (king != 'k' && king != 'K') {
        return false;
    } else if ((king == 'k' && org_posn == 74) || (king == 'K' && org_posn == 4)) {
        return false;
    } else if (!board->getFirstMove(org_posn)) {return false;}
    else if (whiteTurn && whiteInCheck() != "") {return false;}
    else if (!whiteTurn && blackInCheck() != "") {return false;}
    int index;
    if (new_posn + 2 == org_posn) {
        char rook = board->charAt(Position(new_posn - 2));
        if (rook != 'r' && rook != 'R') {return false;}
        if ((king  == 'k' && rook == 'R') || (king == 'K' && rook == 'r')) {return false;}
        if (!board->getFirstMove(Position(new_posn - 2))) {return false;}
        if (board->charAt(Position(new_posn - 1)) != ' ' && board->charAt(Position(new_posn - 1)) != '-') {return false;}
        index = -1;
    } else {
        char rook = board->charAt(Position(new_posn + 1));
        if (rook != 'r' && rook != 'R') {return false;}
        if ((king  == 'k' && rook == 'R') || (king == 'K' && rook == 'r')) {return false;}
        if (!board->getFirstMove(Position(new_posn + 1))) {return false;}
        index = 1;
    }
    int i = org_posn + index;
    bool valid = true;
    while(true) {
        char tmp_piece = board->charAt(Position(i));
        if (tmp_piece != ' ' && tmp_piece != '-') {return false;}
        auto tmp_move = std::make_shared<Move>(org_posn, Position(i));
        board->move(tmp_move);
        if ((whiteTurn && whiteInCheck() != "") || (!whiteTurn && blackInCheck() != "")) {
            valid = false;
        }
        tmp_move = std::make_shared<Move>(Position(i), org_posn);
        board->move(tmp_move);
        if (!valid) {return valid;}
        if (i == new_posn) {break;}
        i += index;
    }
    return valid;
}

bool Chess::validBishop(std::shared_ptr<Move> movement, bool whiteTurn) {
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
    char captured = board->charAt(new_posn);
    if (captured != ' ' && captured != '-') {
        movement->setCaptured(board->getPiece(new_posn));
        
    }
    moves.emplace_back(movement);
    board->move(movement);
    if ((whiteTurn && whiteInCheck() != "") || (!whiteTurn && blackInCheck() != "")) {
        undo();
        return false;
    }
    undo();
    return true;
}

bool Chess::validKing(std::shared_ptr<Move> movement, bool whiteTurn) {
    Position org_posn = movement->getOrg();
    Position new_posn = movement->getNew();
    bool valid = false;
    if (new_posn + 1 == org_posn || new_posn - 1 == org_posn) {
        valid = true;
    } else if (org_posn - 11 <= new_posn && new_posn <= org_posn - 9) {
        valid = true;
    } else if (org_posn + 9 <= new_posn && new_posn <= org_posn + 11) {
        valid = true;
    } else if (new_posn + 2 == org_posn || new_posn - 2 == org_posn) {
        return castling(movement, whiteTurn);
    }
    if (!valid) {return false;}

    char captured = board->charAt(new_posn);
    if (captured != ' ' && captured != '-') {
        movement->setCaptured(board->getPiece(new_posn));
    }
    moves.emplace_back(movement);
    board->move(movement);
    if ((whiteTurn && whiteInCheck() != "") || (!whiteTurn && blackInCheck() != "")) {
        undo();
        return false;
    }
    undo();
    return true;
}

bool Chess::validQueen(std::shared_ptr<Move> movement, bool whiteTurn) {
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
    
    char captured = board->charAt(new_posn);
    if (captured != ' ' && captured != '-') {
        movement->setCaptured(board->getPiece(new_posn));
        
    }
    moves.emplace_back(movement);
    board->move(movement);
    if ((whiteTurn && whiteInCheck() != "") || (!whiteTurn && blackInCheck() != "")) {
        undo();
        return false;
    }
    undo();
    return true;
}

bool Chess::validRook(std::shared_ptr<Move> movement, bool whiteTurn) {
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
    
    char captured = board->charAt(new_posn);
    if (captured != ' ' && captured != '-') {
        movement->setCaptured(board->getPiece(new_posn));
        
    }
    moves.emplace_back(movement);
    board->move(movement);
    if ((whiteTurn && whiteInCheck() != "") || (!whiteTurn && blackInCheck() != "")) {
        undo();
        return false;
    }
    undo();
    return true;
}

bool Chess::validKnight(std::shared_ptr<Move> movement, bool whiteTurn) {
    Position org_posn = movement->getOrg();
    Position new_posn = movement->getNew();
    if (new_posn != Position(org_posn - 21) && new_posn != Position(org_posn - 19) && new_posn != Position(org_posn - 12) && new_posn != Position(org_posn - 8) && new_posn != Position(org_posn + 8) && new_posn != Position(org_posn + 12) && new_posn != Position(org_posn + 19) && new_posn != Position(org_posn + 21)) {
        return false;
    }

    char captured = board->charAt(new_posn);
    if (captured != ' ' && captured != '-') {
        movement->setCaptured(board->getPiece(new_posn));
    }
    moves.emplace_back(movement);
    board->move(movement);
    if ((whiteTurn && whiteInCheck() != "") || (!whiteTurn && blackInCheck() != "")) {
        undo();
        return false;
    }
    undo();
    return true;
}

bool Chess::validPawn(std::shared_ptr<Move> movement, bool whiteTurn, char promote) {
    Position org_posn = movement->getOrg();
    Position new_posn = movement->getNew();
    char captured = board->charAt(new_posn);
    char piece = board->charAt(org_posn);
    bool firstMove;
    bool atTheEdge;
    if (piece == 'p') {
        if (10 <= org_posn && org_posn <= 17) {
            firstMove = true;
        } else if (60 <= org_posn && org_posn <= 67) {
            atTheEdge = true;
        } else {
            firstMove = false;
            atTheEdge = false;
        }
    } else {
        if (10 <= org_posn && org_posn <= 17) {
            atTheEdge = true;
        } else if (60 <= org_posn && org_posn <= 67) {
            firstMove = true;
        } else {
            firstMove = false;
            atTheEdge = false;
        }
    }
    if (promote != '.' && !atTheEdge) {return false;}
    if (Position(org_posn  - (whiteTurn * 11) + (!whiteTurn * 11)) == new_posn || Position(org_posn  - (whiteTurn * 9) + (!whiteTurn * 9)) == new_posn) {
        if (captured == ' ' || captured == '-') {
            if (Position(40  - (whiteTurn * 10)) <= org_posn || org_posn <= Position(47 - (whiteTurn * 10))) {
                return enPassant(movement, whiteTurn);
            } else {
                return false;
            }
        }
        movement->setCaptured(board->getPiece(new_posn));
    } else if (Position(org_posn - (whiteTurn*10) + (!whiteTurn*10)) == new_posn) {
        if (captured != ' ' && captured != '-') {
            return false;
        }
    } else if (firstMove && Position(org_posn - (whiteTurn*20) + (!whiteTurn*20)) == new_posn) {
        char between = board->charAt(Position(org_posn - (whiteTurn*10) + (!whiteTurn*10)));
        if (between != ' ' && between != '-') {
            return false;
        }
    } else {return false;}

    std::cout << "one" << std::endl;
    moves.emplace_back(movement);
    std::cout << "two" << std::endl;
    board->move(movement);
    std::cout << "three" << std::endl;
    if ((whiteTurn && whiteInCheck() != "") || (!whiteTurn && blackInCheck() != "")) {
        std::cout << "four" << std::endl;
        undo();
        std::cout << "five" << std::endl;
        return false;
    }
    std::cout << "four" << std::endl;
    undo();
    std::cout << "five" << std::endl;
    return true;
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
        if (!validQueen(movement, whiteTurn)) {return false;}
    }
    else if (piece == 'b' || piece == 'B') {    //Check Bishop move
        if (!validBishop(movement, whiteTurn)) {return false;}
    }
    else if (piece == 'n' || piece == 'N') {    //Check Knight move
        if (!validKnight(movement, whiteTurn)) {return false;}
    }
    else if (piece == 'r' || piece == 'R') {    //Check Rook move
        if (!validRook(movement, whiteTurn)) {return false;}
    }
    else if (piece == 'p' || piece == 'P') { //Check Pawn move
        if (!validPawn(movement, whiteTurn, promote)) {return false;}
    } else {
        return false;
    }
    return true;
}

std::string Chess::stalemateTest(bool whiteTurn) {
    std::vector<Position> pieces;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Position posn = Position(i*10 + j);
            char piece = board->charAt(posn);
            if (whiteTurn && 'A' <= piece && piece <= 'Z') {
                for (int row = 0; row < 8; row++) {
                    for (int col = 0; col < 8; col++) {
                        Position tmp = Position(row*10 + col);
                        char toPiece = board->charAt(tmp);
                        if ('A' <= toPiece && toPiece <= 'Z') {continue;}
                        auto move = std::make_shared<Move>(posn, tmp);
                        if (validMove(move, whiteTurn)) {
                            return "";
                        }
                    }
                }
            } else if (!whiteTurn && 'a' <= piece && piece <= 'z') {
                for (int row = 0; row < 8; row++) {
                    for (int col = 0; col < 8; col++) {
                        Position tmp = Position(row*10 + col);
                        char toPiece = board->charAt(tmp);
                        if ('a' <= toPiece && toPiece <= 'z') {continue;}
                        auto move = std::make_shared<Move>(posn, tmp);
                        if (validMove(move, whiteTurn)) {
                            return "";
                        }
                    }
                }
            }
        }
    }
    return "Stalemate!";
    /*for (int i = 0; i < 8; ++i) {
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
        std::cout << board->getFirstMove(org_posn) << std::endl;
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
                    std::cout << int(org_posn) << " -> " << posn_index << std::endl;
                    auto move = std::make_shared<Move>(org_posn, new_posn);
                    if (validMove(move, whiteTurn)) {
                        return "";
                    }
                }
            }
        }
    }
    return "Stalemate!";*/
}

std::string Chess::checkmateTest(bool whiteTurn) {
    std::cout << "checkmate test stalemate" << std::endl;
    std::string stalemate = stalemateTest(whiteTurn);
    std::cout << "done" << std::endl;
    if (stalemate != "" && whiteTurn) {
        return "Checkmate! Black wins!";
    } else if (stalemate != "") {
        return "Checkmate! White wins!";
    }
    return "";
}

std::string Chess::blackInCheck() {
    Position blackKing;
    bool found = false;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Position posn = Position(i*10 + j);
            if (board->charAt(posn) == 'k') {
                blackKing = posn;
                found = true;
                break;
            }
        }
        if (found) {break;}
    }
    std::cout << found << std::endl;

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Position posn = Position(i*10 + j);
            char piece = board->charAt(posn);
            if ('A' <= piece && piece <= 'Z') {
                auto move = std::make_shared<Move>(posn, blackKing);
                if (validMove(move, true)) {return "Black is in check.";}
            }
        }
    }
    return "";
}

std::string Chess::whiteInCheck() {
    Position whiteKing;
    bool found = false;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Position tmp = Position(i*10 + j);
            if (board->charAt(tmp) == 'K') {
                whiteKing = tmp;
                found = true;
                break;
            }
        }
        if(found) {break;}
    }
    
    for(int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            char piece = board->charAt(Position(i*10 + j));
            if ('a' <= piece && piece <= 'z') {
                Position tmp = Position(i*10 + j);
                auto move = std::make_shared<Move>(tmp, whiteKing);
                if (validMove(move, false)) {return "White is in check.";}
            }
        }
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
    std::cout << 1 << std::endl;
    bool valid = validMove(movement, whiteTurn, promote);
    std::cout << 2 << std::endl;
    if (!valid) {
        throw std::out_of_range {"Invalid move!"};
    } else if ((piece == 'k' || piece == 'K') && (new_posn + 2 == org_posn || new_posn - 2 == org_posn)) {
        board->setFirstMove(org_posn, false);
        board->setWhenFirstMove(org_posn, when);
        if (new_posn + 2 == org_posn) {
            board->setWhenFirstMove(Position(new_posn - 2), when);
            board->setFirstMove(Position(new_posn - 2), false);
            movement->setCell1(((new_posn + 1) / 10) * 10 + ((new_posn + 1) % 10));
            movement->setCell2(((new_posn - 2) / 10) * 10 + ((new_posn - 2) % 10));
        } else {
            board->setWhenFirstMove(Position(new_posn + 1), when);
            board->setFirstMove(Position(new_posn + 1), false);
            movement->setCell1(((new_posn - 1) / 10) * 10 + ((new_posn - 1) % 10));
            movement->setCell2(((new_posn + 1) / 10) * 10 + ((new_posn + 1) % 10));
        }
        board->castling(movement);
    } else if (piece == 'k' || piece == 'K' || piece == 'r' || piece == 'R') {
        if (board->getFirstMove(org_posn)) {
            board->setFirstMove(org_posn, false);
            board->setWhenFirstMove(org_posn, when);
        }
        board->move(movement);
    } else if (piece == 'p' || piece == 'P') {
        if (promote != '.') {
            movement->setPromoted(board->getPiece(org_posn));
            board->move(movement, promote);
            board->setPromoted(new_posn, true);
            board->setWhenPromoted(new_posn, when);
        } else if (Position(org_posn  - (whiteTurn * 11) + (!whiteTurn * 11)) == new_posn || Position(org_posn  - (whiteTurn * 9) + (!whiteTurn * 9)) == new_posn) {
            if (captured == ' ' || captured == '-') {
                board->setEnPassant(Position((org_posn / 10) + (new_posn % 10)), true);
                //board->setEnPassant(org_posn, true);
                movement->setCell1(((org_posn / 10)*10) + (new_posn % 10));
                board->enPassant(movement);
            } else {
                board->move(movement);
            }
        } else {
            board->move(movement);
        }
    } else {
        board->move(movement);
    }
    std::cout << 3 << std::endl;

    //Now, we check it's check, checkmate or stalemate
    bool gameEnd = false;;
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
            gameEnd = true;
            if (whiteTurn) {
                score->addToWhite(1);
            } else {
                score->addToBlack(1);
            }
        }
    } else {
        status = stalemateTest(!whiteTurn);
        if (status != "") {
            score->addToWhite(0.5);
            score->addToBlack(0.5);
            gameEnd = true;
        }
    }

    movement->setStatus(status);
    moves.emplace_back(movement);

    int org_changed_posn = (org_posn / 10) * 10 + (org_posn % 10);
    int new_changed_posn = (new_posn / 10) * 10 + (new_posn % 10);
    //Notify to the observers to display the board.
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