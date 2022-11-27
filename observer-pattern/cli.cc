#include "cli.h"
#include <iostream>

void Cli::notify(std::string value) {
    char piece;
     for (int i = 0; i < 8; ++i) {
        for (int j = 0; j <8;  ++j) {
            int posn = i*10 + j;
            piece = chess->getPiece(Position(posn));
            std::cout << piece;
        }
        std::cout << std::endl;
    }
    if (value != "") {
        std::cout << value << std::endl;
    }
}

Cli::Cli(std::shared_ptr<Chess> chess): chess{chess} {
    notify("");
}

Cli::~Cli() {
    auto tmp = std::make_shared<Cli>{this};
    chess->detach(this);
}