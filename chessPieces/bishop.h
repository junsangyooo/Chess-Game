#ifndef _BISHOP_H_
#define _BISHOP_H_
#include "pieces.h"

class Bishop : public Piece {
    char piece;
    bool promoted = false;
    int whenPromoted;
public:
    Bishop(char piece);
    ~Bishop();
public:
    char getPiece() const override {return piece;}
    bool getPromoted() const override {return promoted;}
    void setPromoted(bool value) override {promoted = value;}
    void setWhenPromoted(int value) override {whenPromoted = value;}
    int getWhenPromoted() {return whenPromoted;}
};

#endif