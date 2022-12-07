#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <utility>
#include <stdexcept>
#include <vector>
#include <memory>
#include "chess.h"
#include "move.h"
#include "computer.h"

class Controller {
    std::shared_ptr<Chess> chess;
    std::shared_ptr<Computer> computerWhite;
    std::shared_ptr<Computer> computerBlack;
public:
    Controller(std::shared_ptr<Chess> cs);
    ~Controller();
    void setComputerWhite(std::shared_ptr<Computer> comp) {computerWhite = comp;}
    void setComputerBlack(std::shared_ptr<Computer> comp) {computerBlack = comp;}
    bool check();
    void display(int posn = -1);
    void undo();
    bool move(Position org_posn, Position new_posn, bool whiteTurn);
    bool pawnPromote(Position org_posn, Position new_posn, bool whiteTurn, char piece);
    bool computerMove(bool whiteTurn);
    void resign(bool whiteTurn);
};

#endif
