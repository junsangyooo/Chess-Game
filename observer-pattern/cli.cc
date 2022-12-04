#include "cli.h"
#include <iostream>

void Cli::drawBoard(std::string value = "", int posn1 = -1, int posn2 = -1, int posn3 = -1, int posn4 = -1) {
    char piece;
     for (int i = 0; i < 8; ++i) {
        std::cout << 8 - i << " ";
        for (int j = 0; j <8;  ++j) {
            int posn = i*10 + j;
            piece = chess->getPiece(Position(posn));
            std::cout << piece;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << "  abcdefgh" << std::endl;
    if (value != "") {
        std::cout << value << std::endl;
    }
}

Cli::Cli(std::shared_ptr<Chess> chess): chess{chess} {
    drawBoard();
}

Cli::~Cli() {
    chess = nullptr;
    chess->detach("Cli");
}