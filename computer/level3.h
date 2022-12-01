#ifndef _LEVEL_THREE_H_
#define _LEVEL_THREE_H_
#include <string>
#include <utility>
#include <memory>
#include "computer.h"

class LevelThree {
    std::shared_ptr<Chess> chess;
    std::shared_ptr<Computer> computer;
    std::string whitePlayer;
    std::string blackPlayer;
public:
    LevelThree(std::shared_ptr<Chess> chess, std::shared_ptr<Computer> computer, std::string whitePlayer, std::string blackPlayer);
    void play();
};


};

#endif