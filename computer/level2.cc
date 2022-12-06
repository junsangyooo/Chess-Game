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
    
    while(!found) {
        std::random_device rd; // obtain a random number from hardware
        std::mt19937 gen(rd()); // seed the generator
        std::uniform_int_distribution<> distr(1, length); // define the range
        int random = distr(gen);
        Position org_posn = positions.at(random);

        char piece = board->charAt(org_posn);
        char promoteTo;
        Position new_posn;
        bool promotion = false;
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
                        found = true;
                        board->undoPromoted(move);
                        break;
                    }
                }
                if (found) {break;}
            }
            auto move = std::make_shared<Move>(org_posn, Position(org_posn + 9));
            if (chess->validMove(move, whiteSide, 'q')) {
                char c;
                Position tmp = Position(org_posn + 9);
                for (int i = 0; i <4; ++i) {
                    c = promote.at(i);
                    move->setCaptured(board->getPiece(tmp));
                    board->move(move, c);
                    if (chess->whiteInCheck() != "") {
                        promoteTo = c;
                        new_posn = tmp;
                        found = true;
                        board->undoPromoted
                        break;
                    }
                }
            move = std::make_shared<Move>(org_posn, Position(org_posn + 10));
            bool poss2 = chess->validMove(move, whiteSide, 'q');
            move = std::make_shared<Move>(org_posn, Position(org_posn + 11));
            bool poss3 = chess->validMove(move, whiteSide, 'q');

        } else if (piece == 'P' && 10 <= org_posn && org_posn <= 17) {
            //pawnPromotion = true;
        }

        auto move = std::make_shared<Move>(org_posn, oppoKing);
        bool validCheck = chess->validMove(move, whiteSide);
        for (int i = 0; i <8; ++i) {
            for (int j = 0; j < 8; ++j) {

            }
        }
    }
}