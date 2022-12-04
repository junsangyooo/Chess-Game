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
    void drawBoard(int posn1 = -1, int posn2 = -1, int posn3 = -1, int posn4 = -1) override;
    void notify(std::string value) override;
    ~Cli();
};

#endif