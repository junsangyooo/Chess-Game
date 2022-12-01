#ifndef _LEVEL_FOUR_H_
#define _LEVEL_FOUR_H_
#include <string>
#include <utility>
#include <memory>
#include "computer.h"

class LevelFour {
    std::shared_ptr<Chess> chess;
    std::shared_ptr<Computer> computer;
    std::string whitePlayer;
    std::string blackPlayer;
public:
    LevelFour(std::shared_ptr<Chess> chess, std::shared_ptr<Computer> computer, std::string whitePlayer, std::string blackPlayer);
    void play();
};


};

#endif