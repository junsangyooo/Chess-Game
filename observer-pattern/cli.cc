#include "cli.h"
#include <iostream>

void Cli::drawBoard(std::string value, int posn1, int posn2, int posn3, int posn4) {
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

void Cli::notify() {
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
}

Cli::Cli(std::shared_ptr<Chess> chess): chess{chess} {
    notify();
}

Cli::~Cli() {
    chess = nullptr;
    chess->detach("Cli");
}