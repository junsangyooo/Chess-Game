#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include "scoreboard.h"

ScoreBoard::ScoreBoard(int white, int black): white(white), black(black) {}
ScoreBoard::~ScoreBoard() {}
std::ostream& ScoreBoard::operator<<(std::ostream &out) {
    out << "Final Score:" << std::endl;
    out << "White: " << white << std::endl;
    out << "Black: " << black << std::endl;
}

void ScoreBoard::addToWhite(int value) {
    white += value;
}
void ScoreBoard::addToBlack(int value) {
    black += value;
}
