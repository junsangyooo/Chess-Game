#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_
#include <string>
#include <utility>
#include "chess.h"

class Controller {
    auto chess = std::make_shared<Chess>();
public:
    void move(std::string org_posn, std::string new_posn);
    void computerMove();
};

#endif