#include "level4.h"

LevelFour::LevelFour(std::shared_ptr<Chess> chess, bool side, std::shared_ptr<Board> bd): chess{chess}, whiteSide{side}, board{bd} {}

LevelFour::~LevelFour() {
    chess = nullptr;
    board = nullptr;
}

bool LevelFour::makeMove() {
    return false;
}
