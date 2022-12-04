#ifndef _COMPUTER_H_
#define _COMPUTER_H_
#include <string>
#include <utility>
#include <memory>
#include "chess.h"

class Computer {
    std::shared_ptr<Chess> chess;
    std::shared_ptr<Computer> computer;
    std::string whitePlayer;
    std::string blackPlayer;
public:
    Computer(std::shared_ptr<Chess> chess);
    ~Computer();
};


#endif