#ifndef _LEVEL_THREE_H_
#define _LEVEL_THREE_H_
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


class LevelThree : public Computer{
    std::shared_ptr<Chess> chess;
    bool whiteSide;
    std::shared_ptr<Board> board;
public:
    LevelThree(std::shared_ptr<Chess> chess, bool side, std::shared_ptr<Board> bd);
    ~LevelThree();
    bool makeMove() override;
    bool underAttack(Position avoiding);
};

#endif
