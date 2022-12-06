#include "level2.h"

LevelTwo::LevelTwo(std::shared_ptr<Chess> chess, bool side, std::shared_ptr<Board> bd): chess{chess}, whiteSide{side}, board{bd} {}

LevelTwo::~LevelTwo() {
    chess = nullptr;
    board = nullptr;    
}


bool LevelTwo::makeMove() {
    std::vector<Position> positions;
    Position oppoKing;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; ++j) {
            char piece  = board->charAt(Position(10*i + j));
            if (whiteSide && 'A' <= piece && piece <= 'Z') {
                positions.emplace_back(Position(10*i + j));
            } else if (!whiteSide && 'a' <= piece && piece <= 'z') {
                positions.emplace_back(Position(10*i + j));
            } else if (whiteSide && piece == 'k') {
                oppoKing = Position(10*i + j);
            } else if (!whiteSide && piece == 'K') {
                oppoKing = Position(10*i + j);
            }
        }
    }
    int length = positions.size();
    bool found = false;
    std::shared_ptr<Move> move;
    char promoteTo;
    bool promoted = false;
    
    while(!found) {
        std::random_device rd; // obtain a random number from hardware
        std::mt19937 gen(rd()); // seed the generator
        std::uniform_int_distribution<> distr(1, length); // define the range
        int random = distr(gen);

        Position org_posn = positions.at(random - 1);
        char piece = board->charAt(org_posn);
        // Find to way to check first
        if ((piece == 'p' && 60 <= org_posn && org_posn <= 67) && (piece == 'P' && 10 <= org_posn && org_posn <= 17)) {
            std::vector<char> promote;
            int index = 0;
            if (piece == 'p') {
                promote.emplace_back('q');
                promote.emplace_back('r');
                promote.emplace_back('b');
                promote.emplace_back('n');
                index = 9;

            } else {
                promote.emplace_back('Q');
                promote.emplace_back('R');
                promote.emplace_back('B');
                promote.emplace_back('N');
                index = -11;
            }
            for (int i = index; i <= index + 2; ++i) {
                Position tmp = Position(org_posn + i);
                move = std::make_shared<Move>(org_posn, tmp);
                if (!chess->validMove(move, whiteSide, 'q') && !chess->validMove(move, whiteSide, 'Q')) {
                    continue;
                }
                for (char c : promote) {
                    if (i != 10 && i != -10) {
                        move->setCaptured(board->getPiece(tmp));
                    }
                    move->setPromoted(board->getPiece(org_posn));
                    board->move(move, c);
                    if ((piece == 'p' && chess->whiteInCheck() != "") && (piece == 'P' && chess->blackInCheck() != "")) {
                        promoteTo = c;
                        //new_posn = tmp;
                        found = promoted = true;
                        board->undoPromoted(move);
                        move->setCaptured(nullptr);
                        move->setPromoted(nullptr);
                        break;
                    }
                }
                if (found) {break;}
            }
            if (found) {break;}
        } else {
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    Position tmp = Position(1*10 + j);
                    char captured = board->charAt(tmp);
                    move = std::make_shared<Move>(org_posn, tmp);
                    if (!chess->validMove(move, whiteSide)) {continue;}
                    if (captured == ' ' || captured == '-') {
                        if ((piece == 'p' || piece == 'P') && (org_posn  - (whiteSide * 11) + (!whiteSide * 11) == tmp || org_posn  - (whiteSide * 9) + (!whiteSide * 9) == tmp)) {
                            move->setCaptured(board->getPiece(Position((org_posn / 10) + (tmp % 10))));
                            board->enPassant(move);
                            if ((whiteSide && chess->whiteInCheck() != "") && (!whiteSide && chess->blackInCheck() != "")) {
                                found = true;
                                board->undoEnPassant(move);
                                move->setCaptured(nullptr);
                                break;
                            }
                        } else if ((piece == 'k' || piece == 'K') && (tmp + 2 == org_posn || tmp - 2 == org_posn)) {
                            board->castling(move);
                            if ((whiteSide && chess->whiteInCheck() != "") && (!whiteSide && chess->blackInCheck() != "")) {
                                found = true;
                                board->undoCastling(move);
                                break;
                            }
                        }
                    } else if ((whiteSide && 'a' <= captured && 'z' <= captured) || (!whiteSide && 'A'  <= captured && captured <= 'Z')) {
                        move->setCaptured(board->getPiece(tmp));
                        board->move(move);
                        if ((whiteSide && chess->whiteInCheck() != "") && (!whiteSide && chess->blackInCheck() != "")) {
                            found = true;
                            board->undo(move);
                            move->setCaptured(nullptr);
                            break;
                        }
                    }
                }
                if (found) {break;}
            }
            if (found) {break;}
        }

        //Noe we find capturing move
        if ((piece == 'p' && 60 <= org_posn && org_posn <= 67) && (piece == 'P' && 10 <= org_posn && org_posn <= 17)) {
            std::vector<char> promote;
            int index = 0;
            if (piece == 'p') {
                promote.emplace_back('q');
                promote.emplace_back('r');
                promote.emplace_back('b');
                promote.emplace_back('n');
                index = 9;

            } else {
                promote.emplace_back('Q');
                promote.emplace_back('R');
                promote.emplace_back('B');
                promote.emplace_back('N');
                index = -11;
            }
            for (int i = index; i <= index + 2; ++i) {
                if (i == 10 || i == -10) {
                    continue;
                }
                Position tmp = Position(org_posn + i);
                move = std::make_shared<Move>(org_posn, tmp);
                if (chess->validMove(move, whiteSide, 'q')) {
                    promoteTo = 'q';
                    //new_posn = tmp;
                    found = promoted = true;
                    break;
                } else if (chess->validMove(move, whiteSide, 'Q')) {
                    promoteTo = 'Q';
                    //new_posn = tmp;
                    found = promoted = true;
                    break;
                }
            }
            if (found) {break;}
        } else {
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    Position tmp = Position(1*10 + j);
                    char captured = board->charAt(tmp);
                    move = std::make_shared<Move>(org_posn, tmp);
                    if (!chess->validMove(move, whiteSide)) {continue;}
                    if (captured == ' ' || captured == '-') {
                        if ((piece == 'p' || piece == 'P') && (org_posn  - (whiteSide * 11) + (!whiteSide * 11) == tmp || org_posn  - (whiteSide * 9) + (!whiteSide * 9) == tmp)) {
                            found = true;
                            break;
                        }
                    } else if ((whiteSide && 'a' <= captured && 'z' <= captured) || (!whiteSide && 'A'  <= captured && captured <= 'Z')) {
                        found = true;
                        break;
                    }
                }
                if (found) {break;}
            }
            if (found) {break;}
        }

        //Just choose a random move
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
                            found = true;
                            promoted = true;
                            break;
                        }
                    } else if (chess->validMove(move, whiteSide)) {
                        found = true;
                        break;
                    }
                } else {
                    if (chess->validMove(move, whiteSide)) {
                        found = true;
                        break;
                    }
                }
            }
            if (found) {break;}
        }
        if (found) {break;}
    }
    if (found && promoted) {
        return chess->movePiece(move, whiteSide, promoteTo);
    } else if (found) {
        return chess->movePiece(move, whiteSide);
    }
    return false;
}