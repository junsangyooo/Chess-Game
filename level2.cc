#include "level2.h"

LevelTwo::LevelTwo(std::shared_ptr<Chess> chess, bool side, std::shared_ptr<Board> bd): chess{chess}, whiteSide{side}, board{bd} {}

LevelTwo::~LevelTwo() {
    chess = nullptr;
    board = nullptr;
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
    int length = positions.size();
    std::shared_ptr<Move> move;
    // Find to way to check first
    for (Position org_posn : positions) {
        char piece = board->charAt(org_posn);
        if ((piece == 'p' && 60 <= org_posn && org_posn <= 67) || (piece == 'P' && 10 <= org_posn && org_posn <= 17)) {
            int index = 0;
            if (piece == 'p') {
                index = 9;
            } else {
                index = -11;
            }
            for (int i = index; i <= index + 2; ++i) {
                Position tmp = Position(org_posn + i);
                move = std::make_shared<Move>(org_posn, tmp);
                if ((piece == 'p' && !chess->validMove(move, whiteSide, 'q')) || (piece == 'P' && !chess->validMove(move, whiteSide, 'Q'))) {
                    continue;
                }
                if (i != 10 &&i != -10) {
                    move->setCaptured(board->getPiece(tmp));
                }
                bool check = false;
                if (piece == 'p'){
                    move->setPromoted(board->getPiece(org_posn));
                    board->move(move, 'q');
                    if (chess->whiteInCheck() != "") {
                        check = true;
                    }
                    board->undoPromoted(move);
                    if (check) {return chess->movePiece(move, whiteSide, 'q');}
                    board->move(move, 'n');
                    if (chess->whiteInCheck() != "") {
                        check = true;
                    }
                    board->undoPromoted(move);
                    move->setCaptured(nullptr);
                    move->setPromoted(nullptr);
                    if (check) {return chess->movePiece(move, whiteSide, 'n');}
                } else {
                    move->setPromoted(board->getPiece(org_posn));
                    board->move(move, 'Q');
                    if (chess->blackInCheck() != "") {
                        check = true;
                    }
                    board->undoPromoted(move);
                    if (check) {return chess->movePiece(move, whiteSide, 'Q');}
                    board->move(move, 'N');
                    if (chess->blackInCheck() != "") {
                        check = true;
                    }
                    board->undoPromoted(move);
                    move->setCaptured(nullptr);
                    move->setPromoted(nullptr);
                    if (check) {return chess->movePiece(move, whiteSide, 'n');}
                }
            }
        } else {
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    Position tmp = Position(1*10 + j);
                    char captured = board->charAt(tmp);
                    move = std::make_shared<Move>(org_posn, tmp);
                    bool valid = false;
                    if ((whiteSide && 'a' <= captured && captured <= 'z') || (!whiteSide && 'A' <= captured && captured <= 'Z')) {
                        if (chess->validMove(move, whiteSide)) {
                            move->setCaptured(board->getPiece(tmp));
                            board->move(move);
                            if ((whiteSide && chess->blackInCheck() != "") || (!whiteSide && chess->whiteInCheck() != "")) {valid = true;}
                            board->undo(move);
                            move->setCaptured(nullptr);
                            if (valid) {return chess->movePiece(move, whiteSide);}
                        }
                    } else if (captured == ' ' || captured == '-') {
                        if ((piece == 'p' || piece == 'P') && (org_posn  - (whiteSide * 11) + (!whiteSide * 11) == tmp || org_posn  - (whiteSide * 9) + (!whiteSide * 9) == tmp)) {
                            if (chess->validMove(move, whiteSide)) {
                                move->setCaptured(board->getPiece(Position((org_posn / 10) + (tmp % 10))));
                                board->enPassant(move);
                                if ((whiteSide && chess->blackInCheck() != "") || (!whiteSide && chess->whiteInCheck() != "")) {valid = true;}
                                board->undoEnPassant(move);
                                move->setCaptured(nullptr);
                                if (valid) {return chess->movePiece(move, whiteSide);}
                            }
                        } else if ((piece == 'k' || piece == 'K') && (tmp + 2 == org_posn || tmp - 2 == org_posn)) {
                            if (chess->validMove(move, whiteSide)) {
                                board->castling(move);
                                if ((whiteSide && chess->blackInCheck() != "") || (!whiteSide && chess->whiteInCheck() != "")) {valid = true;}
                                board->undoCastling(move);
                                if (valid) {return chess->movePiece(move, whiteSide);}
                            }
                        } else if (chess->validMove(move, whiteSide)) {
                            board->move(move);
                            if ((whiteSide && chess->blackInCheck() != "") || (!whiteSide && chess->whiteInCheck() != "")) {valid = true;}
                            board->undo(move);
                            if (valid) {return chess->movePiece(move, whiteSide);}
                        }
                    } else if (chess->validMove(move, whiteSide)) {
                        board->move(move);
                        if ((whiteSide && chess->blackInCheck() != "") || (!whiteSide && chess->whiteInCheck() != "")) {valid = true;}
                        board->undo(move);
                        if (valid) {return chess->movePiece(move, whiteSide);}
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
                    Position tmp = Position(1*10 + j);
                    char captured = board->charAt(tmp);
                    move = std::make_shared<Move>(org_posn, tmp);
                    if (!chess->validMove(move, whiteSide)) {continue;}
                    if ((whiteSide && 'a' <= captured && captured <= 'z') || (!whiteSide && 'A' <= captured && captured <= 'Z')) {
                        return chess->movePiece(move, whiteSide);
                    } else if (captured == ' ' || captured == '-') {
                        if ((piece == 'p' || piece == 'P') && (org_posn  - (whiteSide * 11) + (!whiteSide * 11) == tmp || org_posn  - (whiteSide * 9) + (!whiteSide * 9) == tmp)) {
                            return chess->movePiece(move, whiteSide);
                        }
                    }
                }
            }
        }
    }
    
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
                            //found = true;
                            //promoted = true;
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
