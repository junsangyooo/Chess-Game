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
    void drawBoard() override;
    void notify(std::string value) override;
    ~Cli();
};

#endif