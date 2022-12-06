#include "level1.h"

LevelOne::LevelOne(std::shared_ptr<Chess> chess, bool side, std::shared_ptr<Board> bd): chess{chess}, whiteSide{side}, board{bd} {}

LevelOne::~LevelOne() {
    chess = nullptr;
    board = nullptr;    
}

bool LevelOne::makeMove() {
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
    bool found = false;
    std::shared_ptr<Move> move;
    int length = positions.size();
    bool promote =false;
    while(!found) {
        std::random_device rd; // obtain a random number from hardware
        std::mt19937 gen(rd()); // seed the generator
        std::uniform_int_distribution<> distr(1, length); // define the range
        int random = distr(gen);
        Position org_posn = positions.at(random-1);
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
                            found = true;
                            promote = true;
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
    }
    if (found && promote) {
        return chess->movePiece(move, whiteSide, 'q');
    } else {
        return chess->movePiece(move, whiteSide);
    }
}