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

LevelOne::~LevelOne() {}