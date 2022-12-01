#ifndef _LEVEL_TWO_H_
#define _LEVEL_TWO_H_
#include <string>
#include <utility>
#include <memory>
#include "computer.h"

class LevelTwo {
    std::shared_ptr<Chess> chess;
    std::shared_ptr<Computer> computer;
    std::string whitePlayer;
    std::string blackPlayer;
public:
    LevelTwo(std::shared_ptr<Chess> chess, std::shared_ptr<Computer> computer, std::string whitePlayer, std::string blackPlayer);
    void play();
};


};

#endif