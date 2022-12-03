#ifndef _ROOK_H_
#define _ROOK_H_
#include "pieces.h"

class Rook : public Piece {
    char piece;
    bool firstMove = true;
    bool castling = false;
    bool promoted = false;
    int whenPromoted;
    int whenFirstMove;
public:
    Rook(char piece);
    ~Rook();
public:
    char getPiece() const override {return piece;}
    bool getFirstMove() {return firstMove;}
    void setFirstMove(bool value) override {firstMove = value;}
    bool getCastling() const override {return castling;}
    void setCastling(bool value) override {castling = value;}
    bool getPromoted() const override {return promoted;}
    void setPromoted(bool value) override {promoted = value;}
    void setWhenPromoted(int value) override {whenPromoted = value;}
    int getWhenPromoted() {return whenPromoted;}
    void setWhenFirstMove(int value) override {whenFirstMove = value;}
    int getWhenFirstMove() {return whenFirstMove;}
};

#endif