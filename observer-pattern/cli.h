#ifndef _CLI_H_
#define _CLI_H_
#include "observer.h"
#include "chess.h"
#include "position.h"

enum Position;

class Cli: public Observer {
    std::shared_ptr<Chess> chess;
public:
    Cli(std::shared_ptr<Chess> chess);
    void drawBoard(Position posn1 = Position(-1), char c1 = NULL, Position posn2 = Position(-1), char c2 = NULL, Position posn3 = Position(-1), char c3 = NULL, Position posn4 = Position(-1), char c4 = NULL) override;
    void notify(std::string value) override;
    ~Cli();
};

#endif