#include "level1.h"
#include "computer.h"
#include "pieces.h"
#include "board.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <utility>
#include <stdexcept>
#include <vector>

LevelOne::LevelOne(std::shared_ptr<Chess> chess): chess{chess} {}

vector<int> LevelOne::getMove() {
    string input;
    while (cin >> input) {
        if (input == "resign") {
            return {-1, -1, -1, -1};
        }
        if (input == "move") {
            string move;
            cin >> move;
            if (move.length() != 4) {
                cout << "Invalid move" << endl;
                continue;
            }
            int x1 = move[0] - letter_off_set;
            int y1 = move[1] - '0';
            int x2 = move[2] - letter_off_set;
            int y2 = move[3] - '0';
            if (x1 < 1 || x1 > 8 || x2 < 1 || x2 > 8 || y1 < 1 || y1 > 8 || y2 < 1 || y2 > 8) {
                cout << "Invalid move" << endl;
                continue;
            }
            if (chess->getBoard()->getPiece(x1, y1) == nullptr) {
                cout << "Invalid move" << endl;
                continue;
            }
            if (chess->getBoard()->getPiece(x1, y1)->getColour() != chess->getTurn()) {
                cout << "Invalid move" << endl;
                continue;
            }
            if (chess->getBoard()->getPiece(x1, y1)->validMove(x1, y1, x2, y2)) {
                return {x1, y1, x2, y2};
            }
            cout << "Invalid move" << endl;
        }
    }
}

LevelOne::~LevelOne() {}