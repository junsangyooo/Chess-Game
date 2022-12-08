#include "level2.h"

LevelTwo::LevelTwo(std::shared_ptr<Chess> chess, bool side, std::shared_ptr<Board> bd): chess{chess}, whiteSide{side}, board{bd} {}

LevelTwo::~LevelTwo() {
    chess = nullptr;
    board = nullptr;
}


bool LevelTwo::promotionCheck(std::shared_ptr<Move> move, char promote, bool captured) {
    Position org_posn = move->getOrg();
    if (captured) {
        move->setCaptured(board->getPiece(Position(org_posn - (whiteSide* 9) +(whiteSide * 9))));
    }
    move->setPromoted(board->getPiece(org_posn));
    if ((whiteSide && chess->blackInCheck() != "") || (!whiteSide && chess->whiteInCheck() != "")) {
        board->undoPromoted(move);
        if (captured) {move->setCaptured(nullptr);}
        move->setPromoted(nullptr);
        return true;
    }
    return false;
}

bool LevelTwo::makeMove() {
    std::vector<Position> positions;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; ++j) {
            char piece  = board->charAt(Position(10*i + j));
            if (whiteSide && 'A' <= piece && piece <= 'Z') {
                positions.emplace_back(Position(10*i + j));
            } else if (!whiteSide && 'a' <= piece && piece <= 'z') {
                positions.emplace_back(Position(10*i + j));
            }
        }
    }
    
    std::shared_ptr<Move> move;
    // Find to way to check first
    for (Position org_posn : positions) {
        char piece = board->charAt(org_posn);
        if ((piece == 'p' && 60 <= org_posn && org_posn <= 67) || (piece == 'P' && 10 <= org_posn && org_posn <= 17)) {
            char promote;
            move = std::make_shared<Move> (org_posn, Position(org_posn - (whiteSide* 9) +(whiteSide * 9)));
            if (chess->validMove(move, whiteSide, 'q')) {
                if(piece == 'p') {promote = 'q';}
                else {promote = 'Q';}
                if (promotionCheck(move, promote, true)) {
                    return chess->movePiece(move,whiteSide,promote);
                }
                if(piece == 'p') {promote = 'n';}
                else {promote = 'N';}
                if (promotionCheck(move, promote, true)) {
                    return chess->movePiece(move, whiteSide, promote);
                }
            }
            move = std::make_shared<Move> (org_posn, Position(org_posn - (whiteSide* 10) +(whiteSide * 10)));
            if (chess->validMove(move, whiteSide, 'q')) {
                if(piece == 'p') {promote = 'q';}
                else {promote = 'Q';}
                if (promotionCheck(move, promote, false)) {
                    return chess->movePiece(move,whiteSide,promote);
                }
                if(piece == 'p') {promote = 'n';}
                else {promote = 'N';}
                if (promotionCheck(move, promote, false)) {
                    return chess->movePiece(move, whiteSide, promote);
                }
            }
            move = std::make_shared<Move> (org_posn, Position(org_posn - (whiteSide* 11) +(whiteSide * 11)));
            if (chess->validMove(move, whiteSide, 'q')) {
                if(piece == 'p') {promote = 'q';}
                else {promote = 'Q';}
                if (promotionCheck(move, promote, true)) {
                    return chess->movePiece(move,whiteSide,promote);
                }
                if(piece == 'p') {promote = 'n';}
                else {promote = 'N';}
                if (promotionCheck(move, promote, true)) {
                    return chess->movePiece(move, whiteSide, promote);
                }
            }
        } else {
            for (int i = 0; i < 8; ++i) {
                for (int j = 0; j < 8; ++j) {
                    Position new_posn = Position(i*10 + j);
                    char tmp = board->charAt(new_posn);
                    move = std::make_shared<Move> (org_posn, new_posn);
                    if (whiteSide && 'A' <= tmp && tmp <= 'Z') {continue;}
                    else if (!whiteSide && 'a' <= tmp && tmp <= 'z') {continue;}
                    else if (!chess->validMove(move, whiteSide)) {
                        continue;
                    }
                    else if (tmp == ' ' || tmp == '-') {
                        if ((piece == 'p' || piece == 'P')) {
                            if (org_posn  - (whiteSide * 11) + (!whiteSide * 11) == new_posn || org_posn  - (whiteSide * 9) + (!whiteSide * 9) == new_posn) {
                                move->setCaptured(board->getPiece(Position(((org_posn / 10) * 10) + (new_posn % 10))));
                                board->enPassant(move);
                                if ((whiteSide && chess->blackInCheck() != "") || (!whiteSide && chess->whiteInCheck() != "")) {
                                    board->undoEnPassant(move);
                                    move->setCaptured(nullptr);
                                    return chess->movePiece(move, whiteSide);
                                } else {
                                    board->undoEnPassant(move);
                                    move->setCaptured(nullptr);
                                }
                            } else {
                                board->move(move);
                                if ((whiteSide && chess->blackInCheck() != "") || (!whiteSide && chess->whiteInCheck() != "")) {
                                    board->undo(move);
                                    return chess->movePiece(move, whiteSide);
                                } else {
                                    board->undo(move);
                                }
                            }
                        } else if ((piece == 'k' || piece == 'K') && (new_posn + 2 == org_posn || new_posn - 2 == org_posn)) {
                            board->castling(move);
                            if ((whiteSide && chess->blackInCheck() != "") || (!whiteSide && chess->whiteInCheck() != "")) {
                                board->undoCastling(move);
                                return chess->movePiece(move, whiteSide);
                            } else {
                                board->undoCastling(move);
                            }
                        } else {
                            board->move(move);
                            if ((whiteSide && chess->blackInCheck() != "") || (!whiteSide && chess->whiteInCheck() != "")) {
                                board->undo(move);
                                return chess->movePiece(move, whiteSide);
                            } else {board->undo(move);}
                        }
                    } else {
                        if ((whiteSide && 'a' <= tmp && tmp <= 'z') || (!whiteSide && 'A' <= tmp && tmp <= 'Z')) {
                            move->setCaptured(board->getPiece(new_posn));
                        }
                        board->move(move);
                        if ((whiteSide && chess->blackInCheck() != "") || (!whiteSide && chess->whiteInCheck() != "")) {
                            board->undo(move);
                            if ((whiteSide && 'a' <= tmp && tmp <= 'z') || (!whiteSide && 'A' <= tmp && tmp <= 'Z')) {
                                move->setCaptured(nullptr);
                            }
                            return chess->movePiece(move, whiteSide);
                        } else {
                            board->undo(move);
                            if ((whiteSide && 'a' <= tmp && tmp <= 'z') || (!whiteSide && 'A' <= tmp && tmp <= 'Z')) {
                                move->setCaptured(nullptr);
                            }
                        }
                    }
                }
            }
        }
    }

    //Noe we find capturing move
    for (Position org_posn: positions) {
        char piece = board->charAt(org_posn);
        if ((piece == 'p' && 60 <= org_posn && org_posn <= 67) || (piece == 'P' && 10 <= org_posn && org_posn <= 17)) {
            if (piece == 'p') {
                move = std::make_shared<Move>(org_posn, Position(org_posn + 9));
                if (chess->validMove(move, whiteSide, 'q')) {
                    return chess->movePiece(move, whiteSide, 'q');
                }
                move = std::make_shared<Move>(org_posn, Position(org_posn + 11));
                if (chess->validMove(move, whiteSide, 'q')) {
                    return chess->movePiece(move, whiteSide, 'q');
                }
            } else {
                move = std::make_shared<Move>(org_posn, Position(org_posn - 9));
                if (chess->validMove(move, whiteSide, 'Q')) {
                    return chess->movePiece(move, whiteSide, 'Q');
                }
                move = std::make_shared<Move>(org_posn, Position(org_posn - 11));
                if (chess->validMove(move, whiteSide, 'Q')) {
                    return chess->movePiece(move, whiteSide, 'Q');
                }
            }
        } else {
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    Position new_posn = Position(i*10 + j);
                    char tmp = board->charAt(new_posn);
                    move = std::make_shared<Move>(org_posn, new_posn);
                    if ((whiteSide && 'a' <= tmp && tmp <= 'z') || (!whiteSide && 'A' <= tmp && tmp <= 'Z')) {
                        if (chess->validMove(move, whiteSide)) {
                            return chess->movePiece(move, whiteSide);
                        }
                    } else if (tmp == ' ' || tmp == '-') {
                        if ((piece == 'p' || piece == 'P') && (org_posn  - (whiteSide * 11) + (!whiteSide * 11) == tmp || org_posn  - (whiteSide * 9) + (!whiteSide * 9) == tmp)) {
                            char captured = board->charAt(Position(((org_posn / 10) * 10) + (new_posn % 10)));
                            if ((whiteSide && captured == 'p') || (!whiteSide && captured == 'P')) {
                                if (chess->validMove(move, whiteSide)) {
                                    return chess->movePiece(move, whiteSide);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    int length = positions.size();
    bool found = false;
    //Just choose a random move
    while(!found) {
        std::random_device rd; // obtain a random number from hardware
        std::mt19937 gen(rd()); // seed the generator
        std::uniform_int_distribution<> distr(1, length); // define the range
        int random = distr(gen);

        Position org_posn = positions.at(random - 1);
        char piece = board->charAt(org_posn);
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                Position new_posn = Position(i*10 + j);
                char c = board->charAt(new_posn);
                move = std::make_shared<Move>(org_posn, new_posn);
                if (whiteSide && 'A' <= c && c <= 'Z') {continue;}
                else if (!whiteSide && 'a' <= c && c <= 'z') {continue;}
                else if (piece == 'p' || piece == 'P') {
                    if ( 70 - (whiteSide * 70) <= new_posn && new_posn <= 77 - (whiteSide * 70)) {
                        if (chess->validMove(move, whiteSide, 'q')) {
                            if (piece == 'p') {
                                return chess->movePiece(move, whiteSide, 'q');
                            }
                            return chess->movePiece(move, whiteSide, 'q');
                        }
                    } else if (chess->validMove(move, whiteSide)) {
                        found = true;
                        return chess->movePiece(move, whiteSide);
                    }
                } else {
                    if (chess->validMove(move, whiteSide)) {
                        found = true;
                        return chess->movePiece(move, whiteSide);
                    }
                }
            }
        }
    }
    return false;
}
