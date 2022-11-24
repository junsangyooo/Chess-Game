#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include "scoreboard.h"

ScoreBoard::ScoreBoard(int white, int black): white(white), black(black) {}
ScoreBoard::~ScoreBoard() {}

int ScoreBoard::getWhite() {
    return white;
}
int ScoreBoard::getBlack() {
    return black;
}

void ScoreBoard::addToWhite(int value) {
    white += value;
}
void ScoreBoard::addToBlack(int value) {
    black += value;
}

std::ostream& operator<<(std::ostream &out, const ScoreBoard& sb) {
    out << "Final Score:" << std::endl;
    out << "White: " << sb.white << std::endl;
    out << "Black: " << sb.black << std::endl;
}
