#ifndef _LEVEL_TWO_H_
#define _LEVEL_TWO_H_
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <utility>
#include <stdexcept>
#include <vector>
#include <memory>
#include <random>
#include <stdlib.h>
#include "computer.h"
#include "pieces.h"
#include "board.h"
#include "position.h"
#include "move.h"


class LevelTwo : public Computer{
    std::shared_ptr<Chess> chess;
    bool whiteSide;
    std::shared_ptr<Board> board;
public:
    LevelTwo(std::shared_ptr<Chess> chess, bool side, std::shared_ptr<Board> bd);
    ~LevelTwo();
    bool makeMove() override;
};

#endif