#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <utility>
#include <stdexcept>
#include <vector>
#include "scoreboard.h"
#include "pieces.h"

void newGame() {}

void resign() {}

void setUp(Piece[8][8] *board) {

}

int main() {
    ScoreBoard sb{0, 0};
    bool inGame = false;
    std::string command;
    Piece* board[8][8];
    while (std::cin >> command) {
        if (command == "game"){
            newGame();
        } else if (command == "resign") {
            resign();
        } else if (command == "setup") {
            setUp(board);
        }
    }

    if (std::cin.eof()){
        std::cout << sb;
    }
}