#ifndef _MOVE_H_
#define _MOVE_H_
#include "position.h"
#include "pieces.h"

enum Position;

class Move {
    Position org_posn, new_posn;
    std::shared_ptr<Piece> captured;
    std::shared_ptr<Piece> promoted;
    std::string checked;
    int changed_cell1 = -1;
    int changed_cell2 = -1;
public:
    Move(Position org_posn, Position new_posn);
    ~Move();
public:
    Position getOrg();
    Position getNew();
    void setCaptured(std::shared_ptr<Piece> piece);
    std::shared_ptr<Piece> getCaptured() {return captured;}
    void setPromoted(std::shared_ptr<Piece> piece);
    std::shared_ptr<Piece> getPromoted() {return promoted;}
    void setChecked(std::string comment) {checked = comment;}
    std::string getChecked() {return checked;}
    void setCell1(int value) {changed_cell1 = value;}
    void setCell2(int value) {changed_cell2 = value;}
    int getCell1() {return changed_cell1;}
    int getCell2() {return changed_cell2;}
};


#endif