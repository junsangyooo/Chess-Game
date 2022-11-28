#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <utility>
#include <stdexcept>
#include <vector>
#include <memory>
#include "scoreboard.h"
#include "pieces.h"
#include "board.h"

enum Position;

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