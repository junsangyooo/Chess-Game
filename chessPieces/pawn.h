#ifndef _PAWN_H_
#define _PAWN_H_
#include "pieces.h"

class Pawn : public Piece {
    char piece;
    bool firstMove = true;
    bool en_passant = false;
    bool promoted = false;
    int whenPromoted;
    int whenFirstMove;
public:
    Pawn(char piece);
    ~Pawn();
public:
    char getPiece() const override {return piece;}
    bool getFirstMove() const override {return firstMove;}
    void setFirstMove(bool value) override {firstMove = value;}
    bool getEnPassant() const override {return en_passant;}
    void setEnPassant(bool value) override {en_passant = value;}
    bool getPromoted() const override {return promoted;}
    void setPromoted(bool value) override {promoted = value;}
    void setWhenPromoted(int value) override {whenPromoted = value;}
    int getWhenPromoted() {return whenPromoted;}
    void setWhenFirstMove(int value) override {whenFirstMove = value;}
    int getWhenFirstMove() {return whenFirstMove;}
};

#endif