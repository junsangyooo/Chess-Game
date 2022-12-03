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
    std::shared_ptr<Computer> computerWhite;
    std::shared_ptr<Computer> computerBlack;
    std::string whitePlayer;
    std::string blackPlayer;
public:
    Controller(std::shared_ptr<Chess> cs);
    ~Controller();
    void setPlayer1(std::string player) {whitePlayer = player;}
    void setPlayer2(std::string player) {blackPlayer = player;}
    void setComputerWhite(std::shared_ptr<Computer> comp) {computerWhite = comp;}
    void setComputerBlack(std::shared_ptr<Computer> comp) {computerBlack = comp;}
    bool check();
    void display();
    void resign();
    void undo();
    bool move(Position org_posn, Position new_posn, bool whiteTurn);
    bool pawnPromote(Position org_posn, Position new_posn, bool whiteTurn, char piece);
    bool computerMove(bool whiteTurn);
};

#endif