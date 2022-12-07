#ifndef _CLI_H_
#define _CLI_H_
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <utility>
#include <stdexcept>
#include <vector>
#include <memory>
#include "observer.h"
#include "chess.h"
//#include "position.h"

enum Position;

class Cli: public Observer {
    std::shared_ptr<Chess> chess;
public:
    Cli(std::shared_ptr<Chess> chess);
    void drawBoard(std::string value = "", int posn1 = -1, int posn2 = -1, int posn3 = -1, int posn4 = -1) override;
    void notify() override;
    ~Cli();
};

#endif
