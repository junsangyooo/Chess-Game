#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <utility>
#include <stdexcept>
#include <vector>

newGame();




int main() {
    bool inGame = false;
    std::string command;
    char board[8][8];
    while (std::cin >> command) {
        if (command == "game"){
            for (int i = 0; i < 8; i ++) {
                for (int j = 0; j < 8; j++) {
                    board[i][j] = '-';
                }
            }
            newGame();
        } else if (command == "resign") {
            resign();
        } else if (command == "setup") {
            setUp();
        }
    }
}