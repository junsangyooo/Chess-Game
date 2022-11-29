#ifndef _PAWN_H_
#define _PAWN_H_
#include "pieces.h"

class Pawn : public Piece {
    char piece;
    std::string colour;
    bool firstMove = true;
    bool en_passant = false;
public:
    Pawn(char piece, std::string colour);
    ~Pawn();
public:
    char getPiece() const override {return piece;}
    std::string getColour() const override{return colour;}
    bool getFirstMove() const override {return firstMove;}
    void setFirstMove(bool value) override {firstMove = value;}
    bool getIsChecked() const override {return false;}
    void setIsChecked(bool value) override {}
    bool getEnPassant() const override {return en_passant;}
    void setEnPassant(bool value) override {en_passant = value;}
    bool getCastling() const override {}
    void setCastling(bool value) override {}
};

#endif