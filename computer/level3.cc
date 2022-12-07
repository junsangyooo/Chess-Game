#include "level3.h"

LevelThree::LevelThree(std::shared_ptr<Chess> chess, bool side, std::shared_ptr<Board> bd): chess{chess}, whiteSide{side}, board{bd} {}
LevelThree::~LevelThree() {
    chess = nullptr;
    board = nullptr;  
}

bool LevelThree::makeMove() {
    return false;
}