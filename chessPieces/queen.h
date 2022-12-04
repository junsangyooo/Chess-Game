#ifndef _QUEEN_H_
#define _QUEEN_H_
#include "pieces.h"

class Queen : public Piece {
    char piece;
    bool promoted =false;
    int whenPromoted = -1;
public:
    Queen(char piece);
    ~Queen();
public:
    char getPiece() const override {return piece;}
    bool getPromoted() const override {return promoted;}
    void setPromoted(bool value) override {promoted = value;}
    void setWhenPromoted(int value) override {whenPromoted = value;}
    int getWhenPromoted() {return whenPromoted;}
};

#endif