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
    Position new_posn;
    // Find to way to check first
    while(!found) {
        std::random_device rd; // obtain a random number from hardware
        std::mt19937 gen(rd()); // seed the generator
        std::uniform_int_distribution<> distr(1, length); // define the range
        int random = distr(gen);

        Position org_posn = positions.at(random - 1);
        char piece = board->charAt(org_posn);
        bool promoted = false;
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
                if (!chess->validMove(move, whiteSide)) {
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
                        new_posn = tmp;
                        found = promotion = true;
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
                    if (captured == )
                }
            }
        }
    }


    Position new_posn;
    bool promotion = false;
    while(!found) {
        std::random_device rd; // obtain a random number from hardware
        std::mt19937 gen(rd()); // seed the generator
        std::uniform_int_distribution<> distr(1, length); // define the range
        int random = distr(gen);
        Position org_posn = positions.at(random);

        char piece = board->charAt(org_posn);
        Position store;
        char promoteStore;
        bool stored = false;
        if (piece == 'p' && 60 <= org_posn && org_posn <= 67) {
            std::vector<char> promote{'q', 'r', 'b', 'n'};
            for (int i = 9; i <= 11; ++i) {
                Position tmp = Position(org_posn + i);
                move = std::make_shared<Move>(org_posn, tmp);
                if (!chess->validMove(move, whiteSide, 'q')) {
                    continue;
                }
                for (char c : promote) {
                    move->setCaptured(board->getPiece(tmp));
                    move->setPromoted(board->getPiece(org_posn));
                    board->move(move, c);
                    if (chess->whiteInCheck() != "") {
                        promoteTo = c;
                        new_posn = tmp;
                        found = promotion = true;
                        board->undoPromoted(move);
                        move->setCaptured(nullptr);
                        move->setPromoted(nullptr);
                        break;
                    } else if (i == 9 || i == 11){
                        promoteStore = c;
                        store = tmp;
                        stored = promotion = true;
                        board->undoPromoted(move);
                        move->setCaptured(nullptr);
                        move->setPromoted(nullptr);
                    } else { continue;}
                }
                if (found) {break;}
            }
            if(found) {break;}
            if (stored) {
                move = std::make_shared<Move>(org_posn, store);
                promoteTo = promoteStore;
                break;
            }
        } else if (piece == 'P' && 10 <= org_posn && org_posn <= 17) {
            std::vector<char> promote{'Q', 'R', 'B', 'N'};
            for (int i = 9; i <= 11; ++i) {
                Position tmp = Position(org_posn - i);
                move = std::make_shared<Move>(org_posn, tmp);
                if (!chess->validMove(move, whiteSide, 'Q')) {
                    continue;
                }
                for (char c : promote) {
                    move->setCaptured(board->getPiece(tmp));
                    move->setPromoted(board->getPiece(org_posn));
                    board->move(move, c);
                    if (chess->blackInCheck() != "") {
                        promoteTo = c;
                        new_posn = tmp;
                        found = promotion = true;
                        board->undoPromoted(move);
                        move->setCaptured(nullptr);
                        move->setPromoted(nullptr);
                        break;
                    } else if (i == 9 || i == 11){
                        promoteStore = c;
                        store = tmp;
                        stored = promotion = true;
                        board->undoPromoted(move);
                        move->setCaptured(nullptr);
                        move->setPromoted(nullptr);
                    } else { continue;}
                }
                if (found) {break;}
            }
            if(found) {break;}
            if (stored) {
                move = std::make_shared<Move>(org_posn, store);
                promoteTo = promoteStore;
                break;
            }
        } else {
            for (int i = 0; i <8; ++i) {
                for (int j = 0; j < 8; ++j) {
                    Position tmp = Position(i*10 + j);
                    move = std::make_shared<Move>(org_posn, tmp);
                    char c = board->charAt(tmp);
                    if (whiteSide && 'A' <= c && c <= 'Z') {continue;}
                    else if (!whiteSide && 'a' <= c && c <= 'z') {continue;}
                    else if (!chess->validMove(move, whiteSide)) {continue;}
                    else if (c == ' ' || c == '-') {
                        if ((piece == 'k' || piece == 'K') && (tmp + 2 == org_posn || tmp - 2 == org_posn)) {
                            board->castling(move);
                            if (piece == 'k' && chess->whiteInCheck() != "") {
                                found = true;
                                board->undoCastling(move);
                                break;
                            } else if (piece == 'K' && chess->blackInCheck() != "") {
                                found = true;
                                board->undoCastling(move);
                                break;
                            }
                        } else if (piece == 'p' || piece == 'P') {
                            if ((org_posn  - (whiteSide * 11) + (!whiteSide * 11) == new_posn) || (org_posn  - (whiteSide * 9) + (!whiteSide* 9) == new_posn)) {
                                move->setCaptured(board->getPiece(Position(new_posn + (whiteSide * 10) - (!whiteSide * 10))));
                                board->enPassant()
                            }
                        } else {
                            board->move(move);
                            if (whiteSide && chess->blackInCheck() != "") {
                                found = true;
                                board->undo(move);
                                break;
                            } else if (!whiteSide && chess->whiteInCheck() != "") {
                                found = true;
                                board->undo(move);
                                break;
                            }
                        }
                    } else if (piece =)
                }
                if (found) {break;}
            }
        }

        auto move = std::make_shared<Move>(org_posn, oppoKing);
        bool validCheck = chess->validMove(move, whiteSide);
        for (int i = 0; i <8; ++i) {
            for (int j = 0; j < 8; ++j) {

            }
        }
    }
    if (found && promotion) {
        return chess->movePiece(move, whiteSide, promoteTo);
    } else if (found) {
        return chess->movePiece(move, whiteSide);
    }

}