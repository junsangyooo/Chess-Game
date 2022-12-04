#ifndef _LEVEL_ONE_H_
#define _LEVEL_ONE_H_
#include <string>
#include <utility>
#include <memory>
#include <random>
#include "computer.h"

class LevelOne {
    std::shared_ptr<Chess> chess;
    std::shared_ptr<Computer> computer;
    std::string whitePlayer;
    std::string blackPlayer;
public:
    LevelOne(std::shared_ptr<Chess> chess);
    ~LevelOne();
};

#endif