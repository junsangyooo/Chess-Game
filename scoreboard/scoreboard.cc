#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include "scoreboard.h"

ScoreBoard::ScoreBoard(float white, float black): white(white), black(black) {}
ScoreBoard::~ScoreBoard() {}

float ScoreBoard::getWhite() {
    return white;
}
float ScoreBoard::getBlack() {
    return black;
}

void ScoreBoard::addToWhite(float value) {
    white += value;
}
void ScoreBoard::addToBlack(float value) {
    black += value;
}

std::ostream& operator<<(std::ostream &out, const ScoreBoard& sb) {
    out << "Final Score:" << std::endl;
    out << "White: " << sb.white << std::endl;
    out << "Black: " << sb.black << std::endl;
    return out;
}
