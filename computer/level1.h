#ifndef _LEVEL_ONE_H_
#define _LEVEL_ONE_H_
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


class LevelOne : public Computer{
    std::shared_ptr<Chess> chess;
    std::shared_ptr<Board> board;
    bool whiteSide;
public:
    LevelOne(std::shared_ptr<Chess> chess, bool side, std::shared_ptr<Board> bd);
    ~LevelOne();
    bool makeMove() override;
};

#endif