#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_
#include <string>
#include <utility>
#include <memory>
#include "chess.h"
#include "move.h"

class Controller {
    std::shared_ptr<Chess> chess;
public:
    Controller(std::shared_ptr<Chess> cs);
    bool move(std::string org_posn, std::string new_posn);
    void computerMove();
};

#endif