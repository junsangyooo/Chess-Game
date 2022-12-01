#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_
#include <string>
#include <utility>
#include <memory>
#include "chess.h"
#include "move.h"
#include "position.h"
#include "computer.h"

class Controller {
    std::shared_ptr<Chess> chess;
    std::shared_ptr<Computer> computer;
    std::string whitePlayer;
    std::string blackPlayer;
public:
    Controller(std::shared_ptr<Chess> cs);
    void setPlayer1(std::string player) {whitePlayer = player;}
    void setPlayer2(std::string player) {blackPlayer = player;}
    void setComputer(std::shared_ptr<Computer> comp) {computer = comp;}
    bool whiteCheck();
    bool blackCheck();
    void display();
    void resign();
    bool move(std::string org_posn, std::string new_posn, bool whiteTurn);
    void computerMove();

};

#endif