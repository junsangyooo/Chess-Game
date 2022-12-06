#ifndef _MOVE_H_
#define _MOVE_H_
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <utility>
#include <stdexcept>
#include <vector>
#include <memory>
#include "pieces.h"

class Move {
    Position org_posn, new_posn;
    std::shared_ptr<Piece> captured = nullptr;
    std::shared_ptr<Piece> promoted;
    std::string status = "";
    int changed_cell1 = -1;
    int changed_cell2 = -1;
public:
    Move(Position org_posn, Position new_posn);
    ~Move();
public:
    Position getOrg(){return org_posn;}
    Position getNew(){return new_posn;}
    void setCaptured(std::shared_ptr<Piece> piece);
    std::shared_ptr<Piece> getCaptured() {return captured;}
    void setPromoted(std::shared_ptr<Piece> piece);
    std::shared_ptr<Piece> getPromoted() {return promoted;}
    void setStatus(std::string comment) {status = comment;}
    std::string getStatus() {return status;}
    void setCell1(int value) {changed_cell1 = value;}
    void setCell2(int value) {changed_cell2 = value;}
    int getCell1() {return changed_cell1;}
    int getCell2() {return changed_cell2;}
};


#endif