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
};


#endif