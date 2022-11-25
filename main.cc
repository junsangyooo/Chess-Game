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
#include "board.h"

enum Position{
    a8 = 0, b8, c8, d8, e8, f8, g8, h8,
    a7 = 10, b7, c7, d7, e7, f7, g7, h7,
    a6 = 20, b6, c6, d6, e6, f6, g6, h6,
    a5 = 30, b5, c5, d5, e5, f5, g5, h5,
    a4 = 40, b4, c4, d4, e4, f4, g4, h4,
    a3 = 50, b3, c3, d3, e3, f3, g3, h3,
    a2 = 60, b2, c2, d2, e2, f2, g2, h2,
    a1 = 70, b1, c1, d1, e1, f1, g1, h1};

void newGame(std::shared_ptr<Board> &board) {

}

void resign() {}

void replace(std::shared_ptr<Board> &board) {
    char piece;
    std::string posn;
    
}

int main() {
    ScoreBoard sb{0, 0};
    bool inGame = false;
    std::string command;
    auto board = std::make_shared<Board>();
    
    while (std::cin >> command) {
        if (command == "exit") {
            std::cout << sb;
            break;
        } else if (command == "game"){
            newGame(board);
        } else if (command == "resign") {
            resign();
        } else if (command == "setup") {
            std::string set;
            while(std::cin >> set) {
                if (set == "+"){
                    replace(board);
                }
            }
        }
    }
    if (std::cin.eof()){
        std::cout << sb;
    }
}