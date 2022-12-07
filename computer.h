#ifndef _COMPUTER_H_
#define _COMPUTER_H_
#include <string>
#include <utility>
#include <memory>
#include "chess.h"

class Computer {
public:
    virtual ~Computer();
    virtual bool makeMove() = 0;
};


#endif
